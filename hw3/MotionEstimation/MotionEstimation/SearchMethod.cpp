#include "SearchMethod.h"

SearchMethod::SearchMethod(int searchRegionMin, int searchRegionMax) : SEARCH_REGION_MIN(searchRegionMin), SEARCH_REGION_MAX(searchRegionMax)
{
}

SearchMethod::~SearchMethod()
{
}

float SearchMethod::MadCalculation(Mat &block1, Mat &block2)
{
	float sum = 0;
	for (int i = 0; i < block1.rows; i++)
	{
		for (int j = 0; j < block1.cols; j++)
		{
			int value = block1.at<uchar>(i, j) - block2.at<uchar>(i, j);
			sum += abs(value);
		}
	}
	return sum / (block1.rows*block1.cols);
}