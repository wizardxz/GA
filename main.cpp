#include <iostream>
#include <cmath>
#include <ctime>
#include "ga.h"

using namespace std;

int before_produce(GA& ga)
{

    return 1;
}

int after_produce(GA& ga)
{
    Individual* p_best = ga.get_current_generation()->ind_points[0];
//    cout << p_best->get_fitness();
    vector<Binary*>* p_best_param_pointers = &(p_best->param_pointers);
    for (vector<Binary*>::iterator it = p_best_param_pointers->begin();
         it < p_best_param_pointers->end();
         it++)
    {
        cout << (*it)->get_double() << " ";
    }
    cout << endl;
    cout << ga.get_current_generation()->ind_points.size() << endl;
    return 1;
}

double fitness_func(Individual& ind)
{
    double fitness = 0;//calculate fitness, later fitness should equal maximum likelihood function

    for (vector<Binary*>::iterator it = ind.param_pointers.begin();
         it < ind.param_pointers.end();
         it++)
    {
        fitness += pow((*it)->get_double() - 5.0, 2.0);
    }

    return fitness;
}

int main()
{
    Individual* p_ind = Individual::create_individual(fitness_func);

    GA* p_ga = GA::create_ga(1000, 200, p_ind, before_produce, after_produce);
    p_ga->start();


    return 0;

}
