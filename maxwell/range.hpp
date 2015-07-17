/* Copyright (c) 2015 Fabian Schuiki */
#pragma once
#include <iterator>

namespace maxwell {


/// A sequence of elements as defined by two iterators.
/// \needsdoc{members}
template<class Iterator>
class range {
public:
	typedef range self;
	typedef Iterator iterator_type;
	typedef typename std::iterator_traits<Iterator>::difference_type distance_type;

	range() {}
	range(iterator_type first, iterator_type last): first(first), last(last) {}

	iterator_type begin() const { return first; }
	iterator_type end() const { return last; }

	distance_type distance() {
		return std::distance(first,last);
	}

private:
	iterator_type first;
	iterator_type last;
};


/// Creates and returns a range from \a first until and excluding \a last.
template<class Iterator>
range<Iterator> make_range(Iterator first, Iterator last) {
	return range<Iterator>(first, last);
}


/// Creates and returns a range over the container \a c.
template<class Container>
auto make_range(Container& c) -> range<decltype(std::begin(c))> {
	return range<decltype(std::begin(c))>(std::begin(c), std::end(c));
}


} // namespace maxwell
