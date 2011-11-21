#pragma once
#include <string>
#include <sstream>


class Location {
public:
	int line;
	int col;
	int offset;
	
	Location() { line = 0; col = 0; offset = 0; }
	operator std::string () const { std::stringstream s; s << line << "." << col; return s.str(); }
};

class Range {
public:
	Location start;
	Location end;
	
	int getLength() const { return end.offset - start.offset; }
	operator std::string () const {
		std::stringstream s;
		s << (std::string)start << "-";
		if (start.line == end.line)
			s << end.col;
		else
			s << (std::string)end;
		return s.str();
	}
};
