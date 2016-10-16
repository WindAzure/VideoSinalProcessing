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
	// �]�� EncodeSymbol ���פ����i�ศ�b
	// low < FIRST_QTR < HALF < high < THIRD_QTR �Ϊ�
	// FIRST_QTR < low < HALF < THIRD_QTR < high �Ϊ�
	// low < FIRST_QTR < THIRD_QTR < high
	_bitsToFollow++;
	if (_low < FIRST_QTR)
	{
		WriteOutputBits(result, 0);
	}
	else
	{
		WriteOutputBits(result, 1);
	}

	// ����Y�� encode �r�ꬰ�šA�h��X���� 16 bit ���ѵ� decode ��
	// �]�� STOP �ܤַ|�� 8 bit �H�W�A���� 16 bit�A�G�u�ݭn�ɨ� 8 �� bit �N�n
	// �γ\���i��Y�ǳ�@�r��b Encode �ɤѥʹN�|���� 16 bit�A�Ŧr��b�o��u�O�|��
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
		}
		else
		{
			// �פ����
			// low < FIRST_QTR < HALF < high < THIRD_QTR �Ϊ�
			// FIRST_QTR < low < HALF < THIRD_QTR < high �Ϊ�
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

		//�C����s�� bit �i�� decode�A�p�G�S�o��N�����N�s bit ���� 0
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