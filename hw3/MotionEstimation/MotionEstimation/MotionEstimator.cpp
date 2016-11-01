#include "MotionEstimator.h"
#include "DiamondSearchMethod.h"
#include "FullSearchMethod.h"

MontionEstimator::MontionEstimator()
{
}

MontionEstimator::~MontionEstimator()
{
}

Mat MontionEstimator::Estimate(Mat reference, Mat target, EstimateType type, int searchRegionMin, int searchRegionMax)
{
	Mat result(Size(target.cols, target.rows), CV_8UC1);
	for (int i = 0; i < result.rows; i += BLOCK_HEIGHT)
	{
		for (int j = 0; j < result.cols; j += BLOCK_WIDTH)
		{
			Mat targetBlack(target, Rect(j, i, BLOCK_WIDTH, BLOCK_HEIGHT));
			Mat resultBlock(result, Rect(j, i, BLOCK_WIDTH, BLOCK_HEIGHT));

			SearchMethod *method = NULL;
			if (type == EstimateType::DiamondSearch)
			{
				method = new DiamondSearchMethod(searchRegionMin, searchRegionMax);
			}
			else
			{
				method = new FullSearchMethod(searchRegionMin, searchRegionMax);
			}
			method->FindMostSimilarBlock(reference, targetBlack, j, i).copyTo(resultBlock);
			delete method;
		}
	}
	return result;
}