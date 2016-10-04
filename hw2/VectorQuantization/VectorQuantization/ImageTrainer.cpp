#include "ImageTrainer.h"
#include <limits>
#include <time.h>

ImageTrainer::ImageTrainer()
{
	srand(time(NULL));
}

ImageTrainer::~ImageTrainer()
{
}

void ImageTrainer::InitializeCodeTable(float codeRate, vector<Mat> &blockList)
{
	_codeTable.resize(pow(2, codeRate*WIDTH_DIMENSION*HEIGHT_DIMENSION));
	vector<bool> isSelected(blockList.size());
	fill(isSelected.begin(), isSelected.end(), false);
	for (int i = 0; i < _codeTable.size(); i++)
	{
		int index = rand() % blockList.size();
		while (isSelected[index])
		{
			index = rand() % blockList.size();
		}
		_codeTable[i] = blockList[index];
		isSelected[index] = true;
	}
}

void ImageTrainer::ClassifyPartitions(vector<Mat> &blockList, vector<vector<Mat>> &partitions)
{
	for (int i = 0; i < blockList.size(); i++)
	{
		int region = -1;
		float minMSE = numeric_limits<float>::max();
		for (int j = 0; j < _codeTable.size(); j++)
		{
			float currentMSE = Utility::CalculateMSE(blockList[i], _codeTable[j]);
			if (currentMSE < minMSE)
			{
				minMSE = currentMSE;
				region = j;
			}
		}
		partitions[region].push_back(blockList[i]);
	}
}

void ImageTrainer::CentroidOptimalCodeTable(vector<vector<Mat>> &partitions)
{
	for (int i = 0; i < HEIGHT_DIMENSION; i++)
	{
		for (int j = 0; j < WIDTH_DIMENSION; j++)
		{
			for (int k = 0; k < partitions.size(); k++)
			{
				int pixelSum = 0;
				for (int l = 0; l < partitions[k].size(); l++)
				{
					pixelSum += partitions[k][l].at<uchar>(i, j);
				}
				if (pixelSum != 0)
				{
					_codeTable[k].at<uchar>(i, j) = pixelSum / partitions[k].size();
				}
			}
		}
	}
}

void ImageTrainer::Start(string fileName, float codeRate)
{
	_codeTable.clear();
	Mat img = imread(fileName, 0);
	vector<Mat> blockList;
	Utility::CutBlocks(img, blockList);
	InitializeCodeTable(codeRate, blockList);
	for (int i = 0; i < 10; i++)
	{
		vector<vector<Mat>> partitions(_codeTable.size());
		ClassifyPartitions(blockList, partitions);
		CentroidOptimalCodeTable(partitions);
	}
}

vector<Mat> ImageTrainer::GetCodeTable()
{
	return _codeTable;
}