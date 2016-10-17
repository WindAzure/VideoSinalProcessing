#include "ArithmeticCodingFactory.h"

ArithmeticCodingFactory::ArithmeticCodingFactory()
{
}

ArithmeticCodingFactory::~ArithmeticCodingFactory()
{
}

void ArithmeticCodingFactory::InitializeModel()
{
	for (int i = 0; i <= TOTAL_SYMBOLS_QUANTITY; i++)
	{
		_frequency[i] = 1;
		_cumulativeFrequency[i] = TOTAL_SYMBOLS_QUANTITY - i;
	}
	_frequency[0] = 0;
}

void ArithmeticCodingFactory::UpdateModel(int symbol)
{
	if (_cumulativeFrequency[0] >= MAX_FREQUENCY)
	{
		int cum = 0;
		for (int i = TOTAL_SYMBOLS_QUANTITY; i >= 0; i--)
		{
			_frequency[i] = (_frequency[i] + 1) / 2;
			_cumulativeFrequency[i] = cum;
			cum += _frequency[i];
		}
	}
	_frequency[symbol]++;
	for (int i = symbol - 1; i >= 0; i--)
	{
		_cumulativeFrequency[i]++;
	}
}

void ArithmeticCodingFactory::WriteOutputBits(string &result, int bit)
{
	result = to_string(bit) + result;
	_bitsToGo--;
	while (_bitsToFollow > 0)
	{
		result = to_string(!bit) + result;
		_bitsToGo--;
		_bitsToFollow--;
	}
}

void ArithmeticCodingFactory::FlushBits(string &result)
{
	// 論文上提到，壓完 STOP 出去後，為了限制 low, high 的範圍落在
	// low < FIRST_QTR < HALF <= high or
	// low < HALF < THIRD_QTR <= high
	// 
	// 但在 Encode的 for (;;) 的 break 條件， low, high 可能的值如下
	// low < FIRST_QTR < HALF < high < THIRD_QTR 或者
	// FIRST_QTR < low < HALF < THIRD_QTR < high 或者
	// low < FIRST_QTR < THIRD_QTR < high
	// 
	// 估計此段程式碼是為了阻止 low < FIRST_QTR < THIRD_QTR < high 的情況
	// 不然迴圈跳出的時候數值就已經符合了，幹嘛又要再多做這一步
	// 但是此段程式碼是如何讓 low < FIRST_QTR < THIRD_QTR < high 能夠被限制成
	// low < FIRST_QTR < HALF <= high or
	// low < HALF < THIRD_QTR <= high
	// 的原因尚未知
	_bitsToFollow++;
	if (_low < FIRST_QTR)
	{
		WriteOutputBits(result, 0);
	}
	else
	{
		WriteOutputBits(result, 1);
	}

	// 防止若欲 encode 字串為空，則輸出不足 16 bit 提供給 decode 解
	// 因為 STOP 至少會有 8 bit 以上，不足 16 bit，故只需要補足 8 個 bit 就好
	// 或許有可能某些單一字串在 Encode 時天生就會不足 16 bit，空字串在這邊只是舉例
	int zeroBitQuantity = 8 - abs(_bitsToGo % 8);
	for (int i = 0; i < zeroBitQuantity; i++)
	{
		result = "0" + result;
	}
}

void ArithmeticCodingFactory::EncodeSymbol(int symbol, string &result)
{
	int range = _high - _low + 1;
	_high = _low + (range*_cumulativeFrequency[symbol - 1]) / _cumulativeFrequency[0] - 1;
	_low = _low + (range*_cumulativeFrequency[symbol]) / _cumulativeFrequency[0];
	for (;;)
	{
		if (_high < HALF)
		{
			WriteOutputBits(result, 0);
		}
		else if (_low >= HALF)
		{
			WriteOutputBits(result, 1);
			_low -= HALF;
			_high -= HALF;
		}
		else if (_low >= FIRST_QTR && _high < THIRD_QTR)
		{
			_bitsToFollow++;
			_low -= FIRST_QTR;
			_high -= FIRST_QTR;
			// 為何暫存的 bit 最後卻比下次的晚輸出問題尚未理解
		}
		else
		{
			// 終止條件為
			// low < FIRST_QTR < HALF < high < THIRD_QTR 或者
			// FIRST_QTR < low < HALF < THIRD_QTR < high 或者
			// low < FIRST_QTR < THIRD_QTR < high
			break;
		}
		_low = _low * 2;
		_high = _high * 2 + 1;
	}
}

int ArithmeticCodingFactory::DecodeSymbol(string &encodedText, int &currentBitIndex)
{
	int symbol;
	int range = _high - _low + 1;
	int cum = ((_value - _low + 1)*_cumulativeFrequency[0] - 1) / range;
	for (symbol = 1; _cumulativeFrequency[symbol]>cum; symbol++);
	_high = _low + (range*_cumulativeFrequency[symbol - 1]) / _cumulativeFrequency[0] - 1;
	_low = _low + (range*_cumulativeFrequency[symbol]) / _cumulativeFrequency[0];

	for (;;)
	{
		if (_high < HALF)
		{
		}
		else if (_low >= HALF)
		{
			_value -= HALF;
			_low -= HALF;
			_high -= HALF;
		}
		else if (_low >= FIRST_QTR && _high < THIRD_QTR)
		{
			_value -= FIRST_QTR;
			_low -= FIRST_QTR;
			_high -= FIRST_QTR;
		}
		else
		{
			break;
		}
		_low = _low * 2;
		_high = _high * 2 + 1;

		//每次抓新的 bit 進來 decode，如果沒得抓就直接將新 bit 視為 0
		if (currentBitIndex < 0)
		{
			_value = 2 * _value + 0;
		}
		else
		{
			_value = 2 * _value + (encodedText[currentBitIndex--] - '0');
		}
	}
	return symbol;
}

string ArithmeticCodingFactory::Encode(string alphabets)
{
	_low = 0;
	_high = TOP_VALUE;
	_bitsToFollow = 0;
	_bitsToGo = 8;
	string result = "";
	InitializeModel();

	for (int i = 0; i < alphabets.size(); i++)
	{
		EncodeSymbol(alphabets[i] + 1, result);
		UpdateModel(alphabets[i] + 1);
	}
	EncodeSymbol(TOTAL_SYMBOLS_QUANTITY, result);
	FlushBits(result);
	return result;
}

string ArithmeticCodingFactory::Decode(string encodedText)
{
	_low = 0;
	_high = TOP_VALUE;
	_value = 0;
	string result = "";
	InitializeModel();

	int currentBitIndex = encodedText.size() - 1;
	for (int i = 0; i < CODE_BITS; i++, currentBitIndex--)
	{
		_value = _value * 2 + (encodedText[currentBitIndex] - '0');
	}

	for (;;)
	{
		int symbol = DecodeSymbol(encodedText, currentBitIndex);
		if (symbol == TOTAL_SYMBOLS_QUANTITY)
		{
			break;
		}
		result += (char)(symbol - 1);
		UpdateModel(symbol);
	}
	return result;
}