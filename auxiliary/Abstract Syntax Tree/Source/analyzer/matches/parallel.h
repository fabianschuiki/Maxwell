#pragma once
#include "../match.h"


class ParallelMatch : public Match {
public:
	
	virtual void compare(Token * token);
};
