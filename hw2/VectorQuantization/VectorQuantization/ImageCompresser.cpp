#include "ImageCompresser.h"

ImageCompresser::ImageCompresser()
{
}

ImageCompresser::~ImageCompresser()
{
}

Mat ImageCompresser::Compress(string fileName, vector<Mat>& codeTable)
{
	Mat img = imread(fileName, 0);
	for (int i = 0; i < img.rows; i += HEIGHT_DIMENSION)
	{
		for (int j = 0; j < img.cols; j += WIDTH_DIMENSION)
		{
			Mat block(img, Rect(j, i, WIDTH_DIMENSION, HEIGHT_DIMENSION));
			int region = -1;
			float minMSE = numeric_limits<float>::max();
			for (int k = 0; k < codeTable.size(); k++)
			{
				float currentMSE = Utility::CalculateMSE(block, codeTable[k]);
				if (currentMSE < minMSE)
				{
					minMSE = currentMSE;
					region = k;
				}
			}
			codeTable[region].copyTo(block);
		}
	}
	return img;
}