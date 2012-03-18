#include <vector>
#include "binary.h"

using namespace std;

class Individual
{
public:
	static Individual* create_individual(double (*fitness_func)(Individual&));// better encapsule property; independent with object

	Individual(vector<Binary*> param_pointers, double (*fitness_func)(Individual&));
	~Individual();
	Individual(const Individual &another_ind);
    Individual* clone();

	vector<Binary*> param_pointers;// param_value; ;later can also have a schema, or in GA class

	int crossover(Individual* &spouse, Individual* &p_son, Individual* &p_daughter);
	int mutate();

	double get_fitness();


private:
    double (*fitness_func)(Individual&);
	double fitness;
	bool assigned;



};
