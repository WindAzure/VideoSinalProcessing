#include "DiamondSearchMethod.h"
#include <map>

DiamondSearchMethod::DiamondSearchMethod(int searchRegionMin, int searchRegionMax) : SearchMethod(searchRegionMin, searchRegionMax)
{
}

DiamondSearchMethod::~DiamondSearchMethod()
{
}

void DiamondSearchMethod::FindByDiamondLayer(Mat &reference, Mat &targetBlock, int diamondLayer[][2], int diamondLayerQuantity, Point &startPoint)
{
	map<pair<int,int>, bool> shownedBlockList;

	float middleScore;
	float currentMinScore = numeric_limits<float>::max();
	do
	{
		Mat middleBlock(reference, Rect(startPoint.x, startPoint.y, BLOCK_WIDTH, BLOCK_HEIGHT));
		middleScore = MadCalculation(middleBlock, targetBlock);
		shownedBlockList[make_pair(startPoint.x,startPoint.y)] = true;

		int index = -1;
		for (int i = 0; i < diamondLayerQuantity; i++)
		{
			int newX = startPoint.x + diamondLayer[i][0];
			int newY = startPoint.y + diamondLayer[i][1];
			if (0 <= newY && newY + BLOCK_HEIGHT < reference.rows && 0 <= newX && newX + BLOCK_WIDTH < reference.cols && shownedBlockList.find(make_pair(newX, newY)) == shownedBlockList.end())
			{
				shownedBlockList[make_pair(newX, newY)] = true;
				Mat layer1Block(reference, Rect(newX, newY, BLOCK_WIDTH, BLOCK_HEIGHT));
				float score = MadCalculation(layer1Block, targetBlock);
				if (score < currentMinScore)
				{
					currentMinScore = score;
					index = i;
				}
			}
		}

		if (currentMinScore<middleScore)
		{
			startPoint.x = startPoint.x + diamondLayer[index][0];
			startPoint.y = startPoint.y + diamondLayer[index][1];
		}
	} while (middleScore > currentMinScore);
}

Mat DiamondSearchMethod::FindMostSimilarBlock(Mat &reference, Mat &targetBlock, int x, int y)
{
	int diamondLayer1[8][2] = { { -2, 0 }, { -1, -1 }, { 0, -2 }, { 1, -1 }, { 2, 0 }, { 1, 1 }, { 2, 0 }, { -1, 1 } };
	int diamondLayer2[4][2] = { { -1, 0 }, { 0, -1 }, { 1, 0 }, { 0, 1 } };

	Point startPoint(x,y);
	FindByDiamondLayer(reference, targetBlock, diamondLayer1, 8, startPoint);
	FindByDiamondLayer(reference, targetBlock, diamondLayer2, 4, startPoint);
	Mat result(reference, Rect(startPoint.x, startPoint.y, BLOCK_WIDTH, BLOCK_HEIGHT));
	return result.clone();;
}