#include <cstdlib>
#include <cmath>
#include <cassert>
#include "binary.h"

using namespace std;

Binary::Binary(double double_value, double min, double max, int bits)
{
	this->double_value = double_value;
	this->min = min;
	this->max = max;
	this->bits = bits;

	int decimal_value = static_cast<int>((double_value - min) / (max - min) * pow(2.0, bits));

	for (int i = 0; i < bits; i++)
	{
		binary_value.push_back(decimal_value % 2);
		decimal_value /= 2;
	}
}

Binary::Binary(vector<int> binary_value, double min, double max, int bits)
{
	this->binary_value = binary_value;
	this->min = min;
	this->max = max;
	this->bits = bits;

	int decimal_value = 0;
	for (unsigned int i = 0; i < binary_value.size(); i++)
	{
		decimal_value += static_cast<int>((binary_value[i] * pow(2.0, (int)i)));
	}

	double_value = decimal_value / pow(2.0, bits) * (max - min) + min;
}

Binary::Binary(const Binary &another_binary)
{
    double_value = another_binary.double_value;
    binary_value = another_binary.binary_value;
    min = another_binary.min;
    max = another_binary.max;
    bits = another_binary.bits;
}

Binary::~Binary()
{
}

int Binary::cross(unsigned int p, Binary* &p_spouse, Binary* &p_son, Binary* &p_daughter)
{
	assert (p <= binary_value.size());//avoid error: p exceeds the size; p is the digit gene become change
	vector<int> son, dau;
	for (unsigned int i = 0; i < p; i++)
	{
		son.push_back(binary_value[i]);
		dau.push_back(p_spouse->binary_value[i]);
	}
	for (unsigned int i = p; i < binary_value.size(); i++)
	{
		son.push_back(p_spouse->binary_value[i]);
		dau.push_back(binary_value[i]);
	}
	p_son = new Binary(son, min, max, bits);
	p_daughter = new Binary(dau, min, max, bits);

	return 1;


}
