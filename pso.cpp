#include "parameter.h"
#include "pso_algo.h"


int main(int argc, char** argv) {

    const int RUN_TIME = atoi(argv[1]);

    const int ITERATION = atoi(argv[2]);

    Parameter parameter;
    
    parameter.setPopultion(atoi(argv[3]));
    
    parameter.setFuncNum(atoi(argv[4]));
    
    parameter.setWmax(atoi(argv[5]));  
    parameter.setWmin(atoi(argv[6]));
    
    parameter.setC1(atoi(argv[7]));    
    parameter.setC2(atoi(argv[8]));
    
    int run = 0;

    while(run < RUN_TIME) {
    
        int itr = 0;
        
        pso_algo pso(parameter);
        
        pso.setBF();

        pso.initial();
        
        pso.checkInit();
    
        while(itr < ITERATION) {
        
            pso.candidate(itr / ITERATION);
                
            ++itr;
            cout << setprecision(32) << itr << " " << pso.bestSol.fitness << endl;
        
        }
        
        //cout << setprecision(16) << pso.bestSol.fitness << endl;
        pso.bestSol.printData();
    
        ++run;
    
    }
    
}
