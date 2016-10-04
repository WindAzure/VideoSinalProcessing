#ifndef IMAGE_COMPRESSER_H
#define IMAGE_COMPRESSER_H

#include "Utility.h"

class ImageCompresser
{
private:

public:
	ImageCompresser();
	virtual ~ImageCompresser();
	Mat Compress(string fileName, vector<Mat>& codeTable);
};

#endif