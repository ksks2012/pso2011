#ifndef __SOLUTION_H__
#define __SOLUTION_H__

#include <vector>
#include <climits>
#include <cmath>
#include "parameter.h"
#include "alea.h"

using namespace std;

class Solution {

public:

    Parameter parameter;

    vector<double> allocation;
    
    vector<double> localBest;
    
    vector<double> velocity;
    
    
    vector<double> UL;
    vector<double> LL;
    
    Alea alea;
    
    double range;
    
    double fitness;
    
    double localFitness;
    
    int dimension;

public:

    Solution();
    Solution(Parameter);
    ~Solution();
    
    void setDimension(int);
    void setRange(vector<double> &, vector<double> &);
    
    void initLocation();
    void genAllocation(int);
    void initVelocity();
    
    void updateLocalBest();

    void updateVelocity(const vector<double> &, const vector<double> &);
    void updateAllocation();
    
    void calFitness();
    
    double RAND();
    
    bool checkAllocation(int);
    
    void printData();

};

#endif
