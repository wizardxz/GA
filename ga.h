#include "generation.h"

class GA
{
public:

    static GA* create_ga(int gen_num, int ind_num, Individual* &p_ind,
                         int (*before_produce)(GA&) = NULL,
                         int (*after_produce)(GA&) = NULL);

	GA(vector<Generation*> &gen_pointers, int gen_num,
       int (*before_produce)(GA&),
       int (*after_produce)(GA&));
	virtual ~GA();

	vector<Generation*> gen_pointers;
	Generation* get_current_generation() {return gen_pointers[current_generation];}

	int start();

private:
	static Generation* create_init_gen(int ind_num, Individual* &p_ind);

	int current_generation;
	int gen_num;
	int (*before_produce)(GA&);
	int (*after_produce)(GA&);
};
