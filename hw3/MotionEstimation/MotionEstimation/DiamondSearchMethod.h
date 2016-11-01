#ifndef DIAMOND_SEARCH_METHOD_H
#define DIAMOND_SEARCH_METHOD_H

#include "SearchMethod.h"

class DiamondSearchMethod : public SearchMethod
{
private:
	void FindByDiamondLayer(Mat &reference, Mat &targetBlock, int diamondLayer[][2], int diamondLayerQuantity, Point &startPoint);

public:
	DiamondSearchMethod(int searchRegionMin, int searchRegionMax);
	virtual ~DiamondSearchMethod();
	Mat FindMostSimilarBlock(Mat &reference, Mat &targetBlock, int x, int y);
};

#endif