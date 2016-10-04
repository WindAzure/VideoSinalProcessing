#include "ImageTrainer.h"
#include "ImageCompresser.h"

int main()
{
	ImageTrainer trainer;
	float codeRate = 0.25;
	trainer.Start("pepper.bmp", codeRate);

	vector<Mat> codeTable = trainer.GetCodeTable();

	ImageCompresser compresser;
	Mat result = compresser.Compress("lena.bmp", codeTable);
	imshow("code rate = " + to_string(codeRate), result);

	for (int i = 0; i < codeTable.size(); i++)
	{
		imwrite(to_string(i) + ".bmp", codeTable[i]);
	}

	waitKey();
	return 0;
}