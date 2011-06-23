#include "parallel.h"


void ParallelMatch::prepareCompare()
{
	//Set the start token for all submatches.
	for (std::vector<Match *>::iterator m = submatches.begin(); m != submatches.end(); m++)
		(*m)->setStartToken(startToken);
}

bool ParallelMatch::compareNext()
{
	//Iterate through the submatches an ask each to compare one step if they're not done.
	int submatchesNotDone = 0;
	for (std::vector<Match *>::iterator m = submatches.begin(); m != submatches.end(); m++) {
		if (!(*m)->done()) {
			submatchesNotDone++;
			(*m)->compareNext();
		}
	}
	
	//Remember whether all submatches are done for outside access.
	isDone = (submatchesNotDone == 0);
	
	//If all submatches were done, choose the one that matched best.
	if (isDone) {
		//choose...
	}
	
	//Return whether all submatches were done.
	return isDone;
}
