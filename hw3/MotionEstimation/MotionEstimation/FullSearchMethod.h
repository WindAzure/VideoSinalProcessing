#ifndef FULL_SEARCH_METHOD_H
#define FULL_SEARCH_METHOD_H

#include "SearchMethod.h"

class FullSearchMethod : public SearchMethod
{
private:

public:
	FullSearchMethod(int searchRegionMin , int searchRegionMax);
	virtual ~FullSearchMethod();
	Mat FindMostSimilarBlock(Mat &reference, Mat &targetBlock, int x, int y);
};

#endif