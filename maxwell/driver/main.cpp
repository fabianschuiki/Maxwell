/* Copyright (c) 2013 Fabian Schuiki */
#include "maxwell/driver/Driver.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
	driver::Driver driver;
	bool result = false;
	if (argc >= 2) {
		result = driver.parseFile(argv[1]);
	} else {
		result = driver.parseStream(std::cin, "standard input");
	}
	return result ? 0 : 1;
}
