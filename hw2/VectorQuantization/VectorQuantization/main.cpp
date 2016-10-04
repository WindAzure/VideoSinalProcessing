#include "ImageTrainer.h"
#include "ImageCompresser.h"

int main()
{
	ImageTrainer trainer;
	trainer.Start("pepper.bmp", 0.5);

	vector<Mat> codeTable = trainer.GetCodeTable();

	ImageCompresser compresser;
	Mat result = compresser.Compress("lena.bmp", codeTable);
	imshow("result", result);
	waitKey();
	return 0;
}