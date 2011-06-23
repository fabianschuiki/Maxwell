#pragma once
#include "series.h"


class ClassMatch : public SeriesMatch {
protected:
	virtual void prepareCompare();
	virtual void prepareMatches();
	
public:
	virtual void childNotification(int tag, Match * child);
};
