#pragma once
#include <string>
#include <vector>


class StringDiff {
public:
	/* A diff encapsulates one difference of the two compared strings, namely its offset, action
	 * to overcome the issue and character of interest. */
	struct Diff {
		int offset;
		enum Action {
			kInsert,
			kRemove
		} action;
		int character;
	};
	typedef std::vector<Diff> Diffs;
	
private:
	Diffs diffs;
	float match;
	
public:
	StringDiff(const std::string & base, const std::string & subject);
	
	const Diffs & getDifferences();
	float getMatch();
};
