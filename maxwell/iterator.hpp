/* Copyright (c) 2015 Fabian Schuiki */
#pragma once
#include <iterator>

/// \file
/// Extensions to the standard library's <iterator> header.

namespace maxwell {


/// \needsdoc
template<class Iterator, class Mapping>
class mapping_iterator : public Iterator {
public:
	typedef mapping_iterator self;
	typedef Iterator iterator_type;
	typedef Mapping mapping_type;
	typedef typename Mapping::result_type result_type;

	explicit mapping_iterator(Mapping m): mapping(m) {}
	explicit mapping_iterator(Iterator it): Iterator(it) {}
	mapping_iterator(Iterator it, Mapping m): Iterator(it), mapping(m) {}

	result_type operator*() const { return mapping(Iterator::operator*()); }
	result_type operator->() const { return mapping(Iterator::operator->()); }

private:
	mapping_type mapping;
};


/// \needsdoc
template<class T>
struct dereference {
	typedef T argument_type;
	typedef decltype(*T(nullptr)) result_type;

	result_type operator() (T const& x) const { return *x; }
};


/// \needsdoc
template<class Iterator>
using dereferencing_iterator = mapping_iterator<Iterator, dereference<
	typename std::remove_reference<decltype(*Iterator())>::type>
>;


} // namespace maxwell
