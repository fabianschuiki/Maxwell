#pragma once

#include <string>


namespace Maxwell {
	class Driver
	{
	public:
		std::string streamName;
		class Scanner * scanner;
		
		bool parse(std::istream & input, const std::string & name);
		bool parse(const std::string & filename);
		
		void error(const class location & l, const std::string & message);
		void error(const std::string & message);
	};
}
