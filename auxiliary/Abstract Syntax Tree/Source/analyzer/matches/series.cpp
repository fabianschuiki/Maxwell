#include "series.h"
#include <iostream>


void SeriesMatch::prepareCompare()
{
	Match::prepareCompare();
	position = 0;
	submatchAdvanced = true;
}

bool SeriesMatch::compareNext()
{
	//If there's no token to be compared or we're done, return true.
	if (!token || position >= submatches.size()) {
		isDone = true;
		return true;
	}
	
	//Fetch the current submatch.
	Match * m = submatches[position];
	
	//If we have just arrived at this submatch, set its start token.
	if (submatchAdvanced) {
		m->setStartToken(token);
		submatchAdvanced = false;
	}
	
	//Compare the submatch, advancing if it is complete.
	if (m->compare()) {
		position++;
		submatchAdvanced = true;
		token = m->getNextToken();
	}
	
	//Calculate the overall match.
	match = 0;
	for (std::vector<Match *>::iterator sm = submatches.begin(); sm != submatches.end(); sm++)
		match += (*sm)->getMatch();
	match /= submatches.size();
	
	//Return whether we've reached the end of the submatches.
	isDone = (position >= submatches.size());
	return isDone;
}



std::vector<std::string> SeriesMatch::toStrings()
{
	std::vector<std::string> s;
	s.push_back("");
	
	//Iterate through all the submatches.
	for (std::vector<Match *>::iterator m = submatches.begin(); m != submatches.end(); m++) {
		
		//Ask each for its strings representation.
		std::vector<std::string> strings = (*m)->toStrings();
		
		//Duplicate the strings we already have and clear the final list.
		std::vector<std::string> offset = s;
		s.clear();
		
		//Append every string we received from the submatches to each entry of strings we already
		//have.
		for (std::vector<std::string>::iterator ns = strings.begin(); ns != strings.end(); ns++) {
			for (std::vector<std::string>::iterator os = offset.begin(); os != offset.end(); os++) {
				std::string cat = (*os);
				if (cat.size()) cat += " ";
				cat += (*ns);
				s.push_back(cat);
			}
		}
	}
	return s;
}
