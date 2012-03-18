#include <vector>

using namespace std;

class Binary
{
public:
	Binary(double double_value, double min, double max, int bits);
	Binary(vector<int> binary_value, double min, double max, int bits);
	Binary(const Binary &another_binary);
	~Binary();

	double get_double() {return double_value;}
	vector<int> get_binary() {return binary_value;}
	double get_min() {return min;}
	double get_max() {return max;}
	int get_bits() {return bits;}

	int cross(unsigned int p, Binary* &p_spouse, Binary* &p_son, Binary* &p_daughter);
private:
	double double_value;
	vector<int> binary_value;
	double min;
	double max;
	int bits;

};
