#include "ArithmeticCodingFactory.h"
#include <iostream>

ArithmeticCodingFactory::ArithmeticCodingFactory()
{
	int f[TOTAL_SYMBOLS_QUANTITY + 1] =
	{
		0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 124, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1236, 1, 21, 9, 3, 1, 25, 15, 2, 2, 2, 1, 79, 19, 60, 1,
		15, 15, 8, 5, 4, 7, 5, 4, 4, 6, 3, 2, 1, 1, 1, 1,
		1, 24, 15, 22, 12, 15, 10, 9, 16, 16, 8, 6, 12, 23, 13, 11,
		14, 1, 14, 28, 29, 6, 3, 11, 1, 3, 1, 1, 1, 1, 1, 3,
		1, 491, 85, 173, 232, 744, 127, 110, 293, 418, 6, 39, 250, 139, 429, 446,
		111, 5, 388, 375, 531, 152, 57, 97, 12, 101, 5, 2, 1, 2, 3, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1
	};
	memcpy(_frequency, f, sizeof(f));
	memset(_cumulativeFrequency, 0, sizeof(_cumulativeFrequency));
	for (int i = TOTAL_SYMBOLS_QUANTITY; i > 0; i--)
	{
		_cumulativeFrequency[i - 1] = _cumulativeFrequency[i] + _frequency[i];
	}
	/*for (int i = 0; i <= TOTAL_SYMBOLS_QUANTITY; i++)
	{
		_frequency[i] = 1;
		_cumulativeFrequency[i] = TOTAL_SYMBOLS_QUANTITY - i;
	}
	_frequency[0] = 0;*/
}

ArithmeticCodingFactory::~ArithmeticCodingFactory()
{
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
		}
		else
		{
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

		//每次抓新的 bit 進來 decode，如果沒得抓就直接將新 b it 視為 0
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

void ArithmeticCodingFactory::UpdateModel()
{

}

void ArithmeticCodingFactory::FlushBits(string &result)
{
	_bitsToFollow++;
	if (_low < FIRST_QTR)
	{
		WriteOutputBits(result,0);
	}
	else
	{
		WriteOutputBits(result,1);
	}

	//防止若欲 encode 字串為空，則輸出不足 16 bit 提供給 decode 解
	//因為 STOP 至少會有 8 bit 以上，不足 16 bit，故只需要補足 8 個 bit 就好
	//或許有可能某些單一字串在 Encode 時天生就會不足 16 bit，空字串在這邊只是舉例
	int zeroBitQuantity = 8 - abs(_bitsToGo % 8);
	for (int i = 0; i < zeroBitQuantity; i++)
	{
		result = "0" + result;
	}
}

string ArithmeticCodingFactory::Encode(string alphabets)
{
	_low = 0;
	_high = TOP_VALUE;
	_bitsToFollow = 0;
	_bitsToGo = 8;
	string result = "";
	for (int i = 0; i < alphabets.size(); i++)
	{
		EncodeSymbol(alphabets[i] + 1, result);
		UpdateModel();
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
		UpdateModel();
	}
	return result;
}