#include <cstdlib>
#include <cmath>
#include <cassert>
#include "individual.h"


using namespace std;

Individual* Individual::create_individual(double (*fitness_func)(Individual&))
{
//This is a temporary method,later should be read from file or other ways
	int test_param_num = 4;
	vector<Binary*> param_pointers;

	for (int i = 0; i < test_param_num; i++)
	{
	    double double_value = (rand() % 100) / 10.0;
	    double min = 0;
	    double max = 10;
	    int bits = 10;
	    Binary * p_param = new Binary(double_value, min, max, bits);
	    param_pointers.push_back(p_param);
	}

	Individual* p_ind = new Individual(param_pointers, fitness_func);
	return p_ind;
}

Individual::Individual(vector<Binary*> param_pointers, double (*fitness_func)(Individual&))
{
	this->param_pointers = param_pointers;
	assigned = false;
	this->fitness_func = fitness_func;

}

Individual::~Individual()
{
    for (unsigned int i = 0; i < param_pointers.size(); i++)
    {
        delete param_pointers[i];
    }
}

Individual::Individual(const Individual& another_ind)
{
	this->param_pointers = another_ind.param_pointers;
	this->fitness_func = another_ind.fitness_func;
	assigned = another_ind.assigned;
	fitness = another_ind.fitness;
}

Individual* Individual::clone()
{
    vector<Binary*> p_new_params;
    for (unsigned int i = 0; i < param_pointers.size(); i++)
    {
        Binary* p_new_param = new Binary(*param_pointers[i]);
        p_new_params.push_back(p_new_param);
    }
    Individual* new_ind = new Individual(p_new_params, fitness_func);
    return new_ind;

}

int Individual::crossover(Individual* &p_spouse, Individual* &p_son, Individual* &p_daughter)
{

	int size = param_pointers.size();
	vector<Binary*> p_son_params;
	vector<Binary*> p_daughter_params;

	for (int i = 0; i < size; i++)
	{
	    Binary* p_dad = param_pointers[i];
	    Binary* p_mom = p_spouse->param_pointers[i];
	    Binary* p_son;
	    Binary* p_daughter;
	    p_dad->cross(5, p_mom, p_son, p_daughter);
	    p_son_params.push_back(p_son);
	    p_daughter_params.push_back(p_daughter);
	}

    p_son = new Individual(p_son_params, fitness_func);
    p_daughter = new Individual(p_daughter_params, fitness_func);

	return 1;
}

int Individual::mutate()
{
    for (unsigned int i = 0; i < param_pointers.size(); i++)
    {
        vector<int> bin = param_pointers[i]->get_binary();
        double min = param_pointers[i]->get_min();
        double max = param_pointers[i]->get_max();
        int bits = param_pointers[i]->get_bits();

        delete param_pointers[i];

        int mutate_bit = rand() % bin.size();
        bin[mutate_bit] = 1 - bin[mutate_bit];
        param_pointers[i] = new Binary(bin, min, max, bits);
    }

	return 1;
}

double Individual::get_fitness()
{
	if (!assigned)
	{
	    assert(fitness_func != NULL);
	    fitness = fitness_func(*this);
		assigned = true;
	}
	return fitness;
}
