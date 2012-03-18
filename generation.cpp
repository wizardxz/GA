#include <cassert>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "generation.h"


Generation::Generation(vector<Individual*> &ind_points, int ind_num)
{
    this->ind_points = ind_points;
    this->ind_num = ind_num;
}

Generation::~Generation()
{
    for (unsigned int i = 0; i < ind_points.size(); i++)
    {
        delete ind_points[i];
    }
}

double Generation::get_max_fitness()
{
    assert(ind_points.size() > 0);
    double max, f;
    max = ind_points[0]->get_fitness();

    for (unsigned int i = 1; i < ind_points.size(); i++)
    {
        f = ind_points[i]->get_fitness();
        if (f > max)
        {
            max = f;
        }
    }
    return f;
}

double Generation::get_avg_fitness()
{
    assert(ind_points.size() > 0);
    double total = 0.0;
    for (unsigned int i = 0; i < ind_points.size(); i++)
    {
        total += ind_points[i]->get_fitness();
    }
    return total / ind_points.size();
}

double Generation::get_variance_fitness()
{
    assert(ind_points.size() > 1);
    double sum_variance = 0;
    double avg = get_avg_fitness();
    for (unsigned int i = 0; i < ind_points.size(); i++)
    {
        sum_variance += pow(ind_points[i]->get_fitness() - avg, 2.0);
    }
    return sum_variance / (ind_points.size() - 1);

}

double Generation::get_std_fitness()
{
    return pow(get_variance_fitness(), .5);
}

int Generation::produce(Generation* &p_next_gen)
{
    unsigned int full_size = ind_num * 2;

    vector<Individual*> p_new_inds;
    Individual* p_ind = new Individual(*ind_points[0]);

    p_new_inds.push_back(p_ind);
    while (p_new_inds.size() < full_size)
    {
        Individual* p_dad = ind_points[rand() % ind_points.size()];
        Individual* p_mom = ind_points[rand() % ind_points.size()];
        Individual* p_son;
        Individual* p_daughter;
        p_dad->crossover(p_mom, p_son, p_daughter);
        p_son->mutate();
        p_daughter->mutate();
        p_new_inds.push_back(p_son);
        p_new_inds.push_back(p_daughter);

    }
    sort(p_new_inds.begin(), p_new_inds.end(), Generation::smaller);
    while (p_new_inds.size() > ind_num)
    {
        p_new_inds.pop_back();
    }


    p_next_gen = new Generation(p_new_inds, ind_num);

    return 1;

}
