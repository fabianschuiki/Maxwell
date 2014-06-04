/* Copyright (c) 2014 Fabian Schuiki */
#include "Packager.hpp"
#include "Packager-detail.hpp"
#include <sqlite3.hpp>
#include <iostream>
#include <queue>
#include <set>
using namespace backendc;


Packager::Packager(sqlite3* db): db(db)
{
}

Packager::~Packager()
{
	for (std::map<std::string,Fragment*>::iterator i = fragments.begin(); i != fragments.end(); i++)
		delete i->second;
	fragments.clear();
}
