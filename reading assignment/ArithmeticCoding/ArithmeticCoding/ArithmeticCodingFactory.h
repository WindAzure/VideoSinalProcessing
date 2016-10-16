#ifndef ARITHMETIC_CODING_FACTORY_H
#define ARITHMETIC_CODING_FACTORY_H

#include <string>

#define TOTAL_SYMBOLS_QUANTITY 257 // total 257 個符號, ascii code 為 256 個, 這邊多壓一個 EOF 代表 Encode 時所用的 STOP, 剛好以 ascii code = 257 下去看
#define MAX_FREQUENCY 16383        // 2^14-1 防止 Overflow, 在計算過程中 range*_cumlativeFrequency 為 2^16 x (2^14 - 1) 若乘超過 16383 則有可能 Overflow
#define CODE_BITS 16
#define TOP_VALUE  (((long)1<<CODE_BITS)-1)
#define FIRST_QTR (TOP_VALUE/4+1)
#define HALF (2*FIRST_QTR)
#define THIRD_QTR (3*FIRST_QTR)

using namespace std;

class ArithmeticCodingFactory
{
private:
	int _low;
	int _high;
	int _value;
	int _bitsToFollow;
	int _bitsToGo;
	int _frequency[TOTAL_SYMBOLS_QUANTITY + 1]; // 由於在程式內部符號編碼為 1-257，為求符號與其頻率直接對應故陣列多開一格，為 258
	int _cumulativeFrequency[TOTAL_SYMBOLS_QUANTITY + 1];

	void InitializeModel();
	void UpdateModel(int symbol);
	void WriteOutputBits(string &result, int bit);
	void FlushBits(string &result);
	void EncodeSymbol(int symbol, string &result);
	int DecodeSymbol(string &encodedText, int &currentBitIndex);

public:
	ArithmeticCodingFactory();
	virtual ~ArithmeticCodingFactory();
	string Encode(string alphabets);
	string Decode(string arithmeticNumber);
};

#endif