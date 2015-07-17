/* Copyright (c) 2015 Fabian Schuiki */
#include "maxwell/diagnostic/SourceLayout.hpp"
#include "maxwell/repository/Source.hpp"
#include <iostream>

namespace maxwell {


/// \needsdoc
SourceLayout SourceLayout::analyze(Source* source) {
	SourceLayout result(source);
	range<Byte*> content = source->getContent();

	Line current_line;
	bool count_indent = true;
	auto line_start = content.begin();

	for (auto it = content.begin(); it != content.end();) {
		auto c = *it;
		++it;

		if (c == '\n') {
			current_line.length = std::distance(line_start, it);
			result.lines.push_back(current_line);

			line_start = it;
			current_line.offset += current_line.length;
			current_line.indent.spaces = 0;
			current_line.indent.tabs = 0;
			current_line.empty = true;
			count_indent = true;

		} else if (count_indent) {
			if (c == '\t') {
				++current_line.indent.tabs;
			} else if (c == ' ') {
				++current_line.indent.spaces;
			} else {
				count_indent = false;
				current_line.empty = false;
			}
		}
	}

	if (line_start != content.end()) {
		current_line.length = std::distance(line_start, content.end());
		current_line.includes_newline = false;
		result.lines.push_back(current_line);
	}

	return result;
}


/// \needsdoc
unsigned SourceLayout::findLineIndexAtOffset(unsigned offset) const {
	auto it = std::lower_bound(
		lines.begin(),
		lines.end(),
		offset,
		[&](Line const& line, unsigned offset){
			return line.offset + line.length <= offset;
		}
	);
	return std::distance(lines.begin(), it);
}


/// \needsdoc
SourceLayout::Line const& SourceLayout::getLine(unsigned index) const {
	assert(index < lines.size());
	return lines[index];
}


/// \needsdoc
PerceivedLocation SourceLayout::lookup(SourceLocation const& l) const {
	assert(l.getSourceId() == source->getId());
	unsigned idx = findLineIndexAtOffset(l.getOffset());
	return PerceivedLocation(
		l.getSourceId(), idx, l.getOffset() - lines[idx].offset
	);
}


/// \needsdoc
PerceivedRange SourceLayout::lookup(SourceRange const& r) const {
	assert(r.getSourceId() == source->getId());
	unsigned idx_start = findLineIndexAtOffset(r.getOffset());
	unsigned idx_end   = findLineIndexAtOffset(r.getOffset() + r.getLength());
	return PerceivedRange(
		r.getSourceId(),
		idx_start, r.getOffset() - lines[idx_start].offset,
		idx_end, r.getOffset() + r.getLength() - lines[idx_end].offset
	);
}


} // namespace maxwell
