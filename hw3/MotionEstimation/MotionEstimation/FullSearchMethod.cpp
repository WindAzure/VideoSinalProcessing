#include "FullSearchMethod.h"
#include <limits>

FullSearchMethod::FullSearchMethod(int searchRegionMin, int searchRegionMax) : SearchMethod(searchRegionMin, searchRegionMax)
{
}

FullSearchMethod::~FullSearchMethod()
{
}

Mat FullSearchMethod::FindMostSimilarBlock(Mat &reference, Mat &targetBlock, int x, int y)
{
	Mat minBlock;
	float minScore = numeric_limits<float>::max();
	for (int i = y + SEARCH_REGION_MIN; i <= y + SEARCH_REGION_MAX; i++)
	{
		for (int j = x + SEARCH_REGION_MIN; j <= x + SEARCH_REGION_MAX; j++)
		{
			if (0 <= i && i+BLOCK_HEIGHT < reference.rows && 0 <= j && j+BLOCK_WIDTH < reference.cols)
			{
				Mat block(reference, Rect(j, i, BLOCK_WIDTH, BLOCK_HEIGHT));
				float score = MadCalculation(block, targetBlock);
				if (score < minScore)
				{
					minScore = score;
					minBlock = block.clone();
				}
			}
		}
	}
	return minBlock;
}