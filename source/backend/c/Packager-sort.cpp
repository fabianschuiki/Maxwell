/* Copyright (c) 2014 Fabian Schuiki */
#include "Packager.hpp"
#include "Packager-detail.hpp"
#include <iostream>
#include <queue>
using namespace backendc;


/** Iterates over the fragment's dependencies. If a dependency is strict, i.e.
 * the fragment needs to be ordered after its dependency, adjusts the
 * dependency's ordering and recurs. */
static void sortRecursively(Fragment* frag, std::set<Fragment*>& visited)
{
	// it.
	int minOrder = frag->order+1;
	for (std::vector<Dependency>::iterator i = frag->deps.begin(); i != frag->deps.end(); i++) {
		if (i->after && i->frag->order < minOrder) {
			i->frag->order = minOrder;
			if (visited.count(i->frag))
				throw std::runtime_error("Dependency cycle detected, " + i->frag->name + " depends on itself");
			visited.insert(i->frag);
			sortRecursively(i->frag, visited);
			visited.erase(i->frag);
		}
	}
}

/** Assigns an order to all %fragments where a fragment has a strictly lower
 * ordering value than its dependencies flagged as 'after'. Sorting the
 * fragments in descending order ensures that a fragment always occurs after
 * its dependencies. */
void Packager::sort()
{
	// Start by assigning all fragments order 0.
	for (std::map<std::string,Fragment*>::iterator i = fragments.begin(); i != fragments.end(); i++) {
		i->second->order = 0;
	}

	// Recursively sort each fragment, which eventually walks over the entire
	// graph of fragments, assigning fragments a lower order values than their
	// dependencies.
	for (std::map<std::string,Fragment*>::iterator i = fragments.begin(); i != fragments.end(); i++) {
		std::set<Fragment*> visited;
		sortRecursively(i->second, visited);
	}
}
