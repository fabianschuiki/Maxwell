/* Copyright (c) 2015 Fabian Schuiki */
#include "maxwell/diagnostic/ConsoleDiagnosticPrinter.hpp"
#include "maxwell/console.hpp"
#include "maxwell/repository/SourceRepository.hpp"
#include "maxwell/repository/Source.hpp"
#include <algorithm>
#include <iostream>

using namespace maxwell;
using namespace maxwell::repository;
using maxwell::filesystem::Path;

void
ConsoleDiagnosticPrinter::consume(Diagnostic const& d) {
	unsigned msg_indent = 0;

	for (auto& msg : d.getMessages()) {
		std::cout << std::string(msg_indent, ' ');

		switch (msg.getSeverity()) {
			case kFatal:   std::cout << console::bold + console::fg.red     << "fatal: "   << console::fg.def; break;
			case kError:   std::cout << console::bold + console::fg.red     << "error: "   << console::fg.def; break;
			case kWarning: std::cout << console::bold + console::fg.yellow  << "warning: " << console::fg.def; break;
			case kInfo:    std::cout << console::bold + console::fg.magenta << "info: "    << console::fg.def; break;
			default: break;
		}
		std::cout << msg.getText() << console::reset << '\n';

		std::vector<SourceRange> ranges;
		if (auto mr = msg.getMainRange())
			ranges.push_back(mr);
		ranges.insert(ranges.end(), msg.getHighlitRanges().begin(), msg.getHighlitRanges().end());
		ranges.insert(ranges.end(), msg.getVisibleRanges().begin(), msg.getVisibleRanges().end());

		// std::cout << "ranges:\n";
		// for (auto& r : ranges)
		// 	std::cout << "  " << r << '\n';

		std::vector<PerceivedRange> perceived_ranges(ranges.size());
		std::transform(ranges.begin(), ranges.end(), perceived_ranges.begin(),
			[&](SourceRange const& rng){
				auto* source = sourceRepository.getSource(rng.getSourceId());
				auto source_layout = lookupSourceLayout(source);
				return source_layout.lookup(rng);
			}
		);

		// std::cout << "perceived_ranges:\n";
		// for (auto& r : perceived_ranges)
		// 	std::cout << "  " << r << '\n';

		struct LineRange {
			unsigned order;
			SourceId sid;
			unsigned offset;
			unsigned length;
		};
		unsigned i = 0;
		std::vector<LineRange> lines(perceived_ranges.size());
		std::transform(perceived_ranges.begin(), perceived_ranges.end(), lines.begin(),
			[&](PerceivedRange const& rng){
				return LineRange {
					i++,
					rng.getSourceId(),
					rng.getFirstLine(),
					rng.getLastLine() - rng.getFirstLine() + 1
				};
			}
		);

		// std::cout << "lines:\n";
		// for (auto& l : lines)
		// 	std::cout << "  " << l.order << ", " << l.sid << ", " << l.offset << ", " << l.length << '\n';

		std::sort(lines.begin(), lines.end(),
			[](LineRange const& a, LineRange const& b){
				return a.sid < b.sid || (a.sid == b.sid && a.offset < b.offset);
			}
		);

		// std::cout << "lines sorted:\n";
		// for (auto& l : lines)
		// 	std::cout << "  " << l.order << ", " << l.sid << ", " << l.offset << ", " << l.length << '\n';

		const unsigned LINE_MERGE_THRESHOLD = 3; // distance below which two line ranges are merged
		std::vector<LineRange> merged_lines;
		for (auto& b : lines) {
			if (merged_lines.empty()) {
				merged_lines.push_back(b);
				continue;
			}
			auto& a = merged_lines.back();

			if (a.sid != b.sid) {
				merged_lines.push_back(b);
				continue;
			}

			unsigned a0 = a.offset;
			unsigned a1 = a.offset + a.length;
			unsigned b0 = b.offset;
			unsigned b1 = b.offset + b.length;

			if (a1 > b0 || b0 - a1 < LINE_MERGE_THRESHOLD) {
				// std::cout << "-> merging in " << b.order << '\n';
				a.length = std::max(a.length, b1 - a0);
				a.order  = std::min(a.order, b.order);
			} else {
				// std::cout << "-> keeping " << b.order << '\n';
				merged_lines.push_back(b);
			}
		}

		// std::cout << "lines merged:\n";
		// for (auto& l : merged_lines)
		// 	std::cout << "  " << l.order << ", " << l.sid << ", " << l.offset << ", " << l.length << '\n';

		std::sort(merged_lines.begin(), merged_lines.end(),
			[](LineRange const& a, LineRange const& b){
				return a.order < b.order;
			}
		);

		// std::cout << "lines reordered:\n";
		// for (auto& l : merged_lines)
		// 	std::cout << "  " << l.order << ", " << l.sid << ", " << l.offset << ", " << l.length << '\n';

		for (auto& l : merged_lines) {
			assert(l.length > 0);

			Source* source = sourceRepository.getSource(l.sid);
			auto source_layout = lookupSourceLayout(source);

			std::cout << "    " << console::dim << source->getPath().native();
			std::cout << ' ' << l.offset+1;
			if (l.length > 1)
				std::cout << '-' << l.offset+l.length-1;
			std::cout << ':' << console::undim << '\n';

			auto common_indent = source_layout.getLine(l.offset).indent;
			for (unsigned i = 1; i < l.length; ++i) {
				auto& line = source_layout.getLine(l.offset+i);
				if (line.empty)
					continue;
				if (line.indent.spaces < common_indent.spaces)
					common_indent.spaces = line.indent.spaces;
				if (line.indent.tabs < common_indent.tabs)
					common_indent.tabs = line.indent.tabs;
			}

			// std::cout << "  " << common_indent.tabs << " common tabs, " << common_indent.spaces << " common spaces\n";

			range<Byte*> content = source->getContent();
			for (unsigned i = 0; i < l.length; ++i) {
				auto& line = source_layout.getLine(l.offset+i);

				unsigned first = line.offset;
				unsigned last = line.offset + line.length;
				if (!line.empty)
					first += common_indent.tabs + common_indent.spaces;
				if (line.includes_newline)
					--last;

				auto rng = make_range(
					content.begin() + first,
					content.begin() + last
				);

				std::cout << "    ";
				unsigned chars_written = 0;
				for (auto c : rng) {
					if (c == '\t') {
						std::cout << "    ";
						chars_written += 4;
					} else {
						std::cout << c;
						++chars_written;
					}
				}
				std::cout << '\n';

				std::vector<char> markers(chars_written+1, ' ');
				bool anything_marked = false;

				auto mark = [&](SourceRange const& r, char m){
					if (!r) return;

					auto a = r.getOffset();
					auto b = r.getOffset() + r.getLength();
					if (a >= last) return;
					if (b < first) return;

					auto ra = first < a ? a - first : 0;
					auto rb = b - first;
					auto l = std::min(last-first, rb-ra);
					if (l == 0) l = 1;

					std::replace(markers.begin()+ra, markers.begin()+rb, ' ', m);
					anything_marked = true;
				};

				mark(msg.getMainRange(), '^');
				for (auto& r : msg.getHighlitRanges())
					mark(r, '`');

				if (anything_marked) {
					std::cout << "    " << console::fg.green;
					auto ic = rng.begin();
					auto im = markers.begin();
					for (; ic != rng.end(); ++ic, ++im) {
						if (*ic == '\t')
							std::cout << std::string(4, *im);
						else
							std::cout << *im;
					}
					for (; im != markers.end(); ++im)
						std::cout << *im;
					std::cout << console::fg.def << '\n';
				}
			}

			std::cout << "\n";
		}

		msg_indent = 2;
	}

	std::cout << '\n';
}


Path
ConsoleDiagnosticPrinter::lookupSourcePath(SourceId id) {
	return sourceRepository.getPath(id);
}

SourceLayout const&
ConsoleDiagnosticPrinter::lookupSourceLayout(Source* source) {
	auto it = sourceLayoutCache.find(source);
	if (it == sourceLayoutCache.end()) {
		SourceLayout sl = SourceLayout::analyze(source);
		it = sourceLayoutCache.insert(
			std::make_pair(source, std::move(sl))).first;
	}
	return it->second;
}
