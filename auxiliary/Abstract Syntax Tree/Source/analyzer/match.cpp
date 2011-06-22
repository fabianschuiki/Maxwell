#include "match.h"
#include <iostream>


void Match::compare(Token * token)
{
	std::string needle("automatically");
	
	//Allocate a map for all possible characters in the string and set all counts to zero.
	int characters[256];
	memset(characters, 0, sizeof(*characters) * 256);
	
	//Iterate over both strings counting characters in the token positively and in the needle neg-
	//atively.
	for (std::string::const_iterator c = needle.begin(); c != needle.end(); c++)
		characters[*c]--;
	for (std::string::const_iterator c = token->text.begin(); c != token->text.end(); c++)
		characters[*c]++;
	
	//Create a buffer for each of the three output lines.
	std::stringstream lchars, lmarks, linserts;
	
	//Create two iterators for each of the two strings.
	std::string::const_iterator n = needle.begin();
	std::string::const_iterator t = token->text.begin();
	int nl = needle.size();
	int tl = token->text.size();
	int inserts = 0, removes = 0;
	
	//Iterate through the needle and try to fix the token into the right form.
	int iterations = 0;
	while (n != needle.end() || t != token->text.end()) {
		iterations++;
		
		//If both characters are equal, skip ahead.
		if (*n == *t) {
			lchars << *n;
			lmarks << ' ';
			linserts << ' ';
			n++; t++;
			nl--; tl--;
			continue;
		}
		
		//Check if the character map states that there are any characters left.
		bool anyLeft = (characters[*n] < 0 || characters[*t] > 0);
		
		//If the character map states that the token is missing the current character in the needle,
		//insert it.
		if (characters[*n] < 0 || (!anyLeft && tl == 0)) {
			lchars << ' ';
			lmarks << '^';
			linserts << *n;
			characters[*n]++;
			n++;
			nl--;
			inserts++;
		}
		
		//Otherwise treat the character as an excessive token character and mark it to be removed.
		else /*if (characters[*t] > 0 || )*/ {
			lchars << *t;
			lmarks << '~';
			linserts << ' ';
			characters[*t]--;
			t++;
			tl--;
			removes++;
		}
	}
	
	//Calculate the match which is basically the ratio of the total text length to the number of
	//inserts and removes.
	match = 1 - (double)(inserts + removes) / /*(needle.size() + token->text.size())*/iterations;
	
	//Dump the match.
	std::stringstream aux;
	aux << "match " << match * 100 << "%" << std::endl;
	
	//Assemble the output from the three buffers.
	temp = lchars.str() + "\n" + lmarks.str() + "\n" + linserts.str() + "\n" + aux.str();
}
