#include <vector>
#include <iostream>
#include <iomanip>
#include "ga.h"

GA* GA::create_ga(int gen_num, int ind_num, Individual* &p_ind,
                  int (*before_produce)(GA&),
                  int (*after_produce)(GA&))
{
    vector<Generation*> gen_pointers;
    Generation* p_init_gen = create_init_gen(ind_num, p_ind);
    gen_pointers.push_back(p_init_gen);

    GA* ga = new GA(gen_pointers, gen_num, before_produce, after_produce);
    return ga;
}

Generation* GA::create_init_gen(int ind_num, Individual* &p_ind)
{
	vector<Individual*> ind_points;

	for (int i = 0; i < ind_num; i++)
	{
	    ind_points.push_back(p_ind->clone());
	}

	Generation* p_gen = new Generation(ind_points, ind_num);
	return p_gen;

}

GA::GA(vector<Generation*> &gen_pointers, int gen_num,
       int (*before_produce)(GA&),
       int (*after_produce)(GA&))
{
	this->gen_pointers = gen_pointers;
	current_generation = 0;
	this->gen_num = gen_num;
	this->before_produce = before_produce;
	this->after_produce = after_produce;
}

GA::~GA()
{
    for (unsigned int i = 0; i < gen_pointers.size(); i++)
    {
        delete gen_pointers[i];
    }
}

int GA::start()
{
    while(current_generation < gen_num)
    {
        if (before_produce)
            before_produce(*this);
        Generation * p_next_gen;
        get_current_generation()->produce(p_next_gen);
        gen_pointers.push_back(p_next_gen);

        if (after_produce)
            after_produce(*this);
        current_generation += 1;
    }

    return 1;
}

