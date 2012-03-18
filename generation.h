#include <vector>
#include "individual.h"

using namespace std;

class Generation
{
public:
	Generation(vector<Individual*> &ind_points, int ind_num);
	~Generation();

	vector<Individual*> ind_points;

	double get_max_fitness();//也是generation里的，应为get maxfitness
	double get_variance_fitness();
//	double rank;//rank，应该是属于generation
	double get_std_fitness();//generation
	double get_avg_fitness();//generation

    int produce(Generation* &p_next_gen);
private:
    unsigned int ind_num;

	static bool smaller(Individual* p_a, Individual* p_b) {return p_a->get_fitness() < p_b->get_fitness();}

};
