#ifndef __VS_ALGO_H__
#define __VS_ALGO_H__

#include <math.h>
#include <ctime>
#include <iomanip>
#include <cstdlib>
#include <climits>
#include "parameter.h"
#include "solution.h"

class pso_algo {

public:

    Solution bestSol;

private:

    Parameter parameter;
    
    // function lowerlimut upperlimut dimension
    
    vector <double> LL;
    vector <double> UL;
    
    //double LL;
    //double UL;
    int D;
    
    double range;
        
    double radius;
    
    //random
    Alea alea;  
    
    vector<vector<double>> identity;
    vector<vector<double>> variance;
    
    //double SD; 
    
    //solution

    vector<Solution> candidateSol;
    
    //SPSO2011
    vector<double> PX;
    vector<double> GX;
    vector<double> V1;
    vector<double> V2;
    Solution Gr;
    
    //int link[100][100] = 0;

    vector<vector<int>> infoLink; //info link topology

public:

    pso_algo();
    pso_algo(Parameter);
    ~pso_algo();

    void setBF();

    void initial();
    void candidate(double);

    void checkInit();

private:

    void initLink(double);

    void setPX(const Solution &);
    
    void setGX(const Solution &, const Solution &);
    
    void calGr(const Solution &, bool);
    void calV1(const Solution &);

    double distanceL(const Solution &);
    
    void sphere(double);

    double stable(double , double , double , double );

};

#endif
