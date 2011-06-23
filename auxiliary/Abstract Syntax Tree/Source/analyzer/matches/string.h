#pragma once
#include <string>
#include <vector>
#include "../match.h"


class StringMatch : public Match {
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
	
private:
	const std::string needle;
	std::vector<Diff> diffs;
	
public:
	const std::string & getNeedle();
	const std::vector<Diff> & getDiffs();
	
	StringMatch(const std::string & needle);
	virtual ~StringMatch() {}
	
	virtual void compare(Token * token);
};
