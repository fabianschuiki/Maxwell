#include "string.h"
#include <iostream>


bool StringMatch::compareNext()
{
	//Ignore if we don't have a valid token.
	if (!token) {
		match = 0;
		return true;
	}
	
	//Allocate a map for all possible characters in the string and set all counts to zero.
	int characters[256];
	memset(characters, 0, sizeof(*characters) * 256);
	
	//Iterate over both strings counting characters in the token positively and in the needle neg-
	//atively.
	for (std::string::const_iterator c = needle.begin(); c != needle.end(); c++)
		characters[*c]--;
	for (std::string::const_iterator c = token->text.begin(); c != token->text.end(); c++)
		characters[*c]++;
	
	//Create two iterators for each of the two strings.
	std::string::const_iterator n = needle.begin();
	std::string::const_iterator t = token->text.begin();
	int nl = needle.size();
	int tl = token->text.size();
	int inserts = 0, removes = 0;
	
	//Clear the differences stored at the moment.
	diffs.clear();
	
	//Iterate through the needle and try to fix the token into the right form.
	int position = 0;
	while (n != needle.end() || t != token->text.end()) {
		position++;
		
		//If both characters are equal, skip ahead.
		if (*n == *t) {
			n++; t++;
			nl--; tl--;
			continue;
		}
		
		//Check if the character map states that there are any characters left.
		bool anyLeft = (characters[*n] < 0 || characters[*t] > 0);
		
		//If the character map states that the token is missing the current character in the needle,
		//insert it.
		if (characters[*n] < 0 || (!anyLeft && tl == 0)) {
			diffs.push_back((Diff){position, Diff::kInsert, *n});
			characters[*n]++;
			n++; nl--;
			inserts++;
		}
		
		//Otherwise treat the character as an excessive token character and mark it to be removed.
		else {
			diffs.push_back((Diff){position, Diff::kRemove, *t});
			characters[*t]--;
			t++; tl--;
			removes++;
		}
	}
	
	//Calculate the match which is basically the ratio of the total text length to the number of
	//inserts and removes.
	match = 1 - (double)(inserts + removes) / position;
	
	//Advance to the next token and return true to indicate that we don't need anymore tokens.
	token = token->next;
	isDone = true;
	return true;
}



StringMatch::StringMatch(const std::string & n) : Match(), needle(n)
{
}



std::vector<std::string> StringMatch::toStrings()
{
	std::vector<std::string> s;
	s.push_back(needle);
	return s;
}

StringMatch::operator std::string()
{
	return needle;
}