#ifndef SEARCH_METHOD_H
#define SEARCH_METHOD_H

#include "Parameters.h"

class SearchMethod
{
private:

protected:
	const int SEARCH_REGION_MIN;
	const int SEARCH_REGION_MAX;
	float MadCalculation(Mat &block1, Mat &block2);

public:
	SearchMethod(int searchRegionMin, int searchRegionMax);
	virtual ~SearchMethod();
	virtual Mat FindMostSimilarBlock(Mat &reference, Mat &targetBlock, int x, int y) = 0;
};

#endif