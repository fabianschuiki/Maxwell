/* Copyright (c) 2014 Fabian Schuiki */
#include "Packager.hpp"
#include <iostream>
using namespace backendc;


Packager::Packager(sqlite3* db): db(db)
{
}

Packager::~Packager()
{
}

void Packager::run(const std::string& name)
{
	std::cout << "packaging " << name << '\n';
}
