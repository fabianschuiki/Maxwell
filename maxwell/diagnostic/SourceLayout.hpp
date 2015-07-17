/* Copyright (c) 2015 Fabian Schuiki */
#pragma once
#include "maxwell/location.hpp"
#include <vector>

namespace maxwell {

namespace repository {
	class Source;
}


/// \needsdoc
class SourceLayout {
public:
	typedef maxwell::repository::Source Source;

	struct Line {
		unsigned offset = 0;
		unsigned length = 0;
		struct {
			unsigned spaces = 0;
			unsigned tabs   = 0;
		} indent;
		bool includes_newline = true;
		bool empty = true;
	};

	static SourceLayout analyze(Source* source);
	unsigned findLineIndexAtOffset(unsigned offset) const;
	Line const& getLine(unsigned index) const;
	std::vector<Line> const& getLines() const { return lines; }

	PerceivedLocation lookup(SourceLocation const& l) const;
	PerceivedRange lookup(SourceRange const& r) const;

private:
	Source const* source;
	std::vector<Line> lines;

	SourceLayout(Source* source) : source(source) {}
};


} // namespace maxwell
