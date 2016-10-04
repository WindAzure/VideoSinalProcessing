#ifndef IMAGE_TRAINER_H
#define IMAGE_TRAINER_H

#include "Utility.h"

class ImageTrainer
{
private:
	vector<Mat> _codeTable;
	void InitializeCodeTable(float codeRate, vector<Mat> &blockList);
	void ClassifyPartitions(vector<Mat> &blockList, vector<vector<Mat>> &partitions);
	void CentroidOptimalCodeTable(vector<vector<Mat>> &partitions);

public:
	ImageTrainer();
	virtual ~ImageTrainer();
	void Start(string fileName, float codeRate);
	vector<Mat> GetCodeTable();
};

#endif