#include "solution.h"

Solution::Solution() {


}

Solution::Solution(Parameter parameter) {

    this->parameter = parameter;
    this->localFitness = INT_MAX;

}

Solution::~Solution() {


}

void Solution::setDimension(int D) {
    
    dimension = D;
    allocation = vector<double>(dimension, 0.0);
    localBest = vector<double>(dimension, 0.0);
    velocity = vector<double>(dimension, 0.0);

}

void Solution::setRange(vector<double> &UL, vector<double> &LL) {

    this->UL = UL;
    this->LL = LL;
    
    
    //TODO 
    this->range = UL[0] - LL[0];

}

void Solution::initLocation() {


    for(int i = 0; i < dimension; ++i) {
    
        genAllocation(i);

    }

}

void Solution::genAllocation(int idx) {
    
    allocation[idx] = alea.alea_rand(LL[0], UL[0]);
    

}

void Solution::initVelocity() {

    for(int i = 0; i < dimension; ++i) {
    
        velocity[i] = alea.alea_rand(LL[0] - allocation[i], UL[0] - allocation[i]);
    
    }

}

void Solution::updateVelocity(const vector<double> &V1, const vector<double> &V2) {

    //double w = (parameter.Wmax - parameter.Wmin) * itr;

    double w = 1. / (2 * log ((double) 2));
    

    for(int i = 0; i < dimension; ++i) {
    
        velocity[i] = w * velocity[i];
        
        //cout << velocity[i] << " " << V1[i] << " " << V2[i] << endl;
        //fgetc(stdin);
        
        //velocity[i] = velocity[i] + V1[i] + V2[i];
        velocity[i] = velocity[i] + V1[i] + V2[i];
    
    }

}

void Solution::updateAllocation() {

    for(int i = 0; i < dimension; ++i) {
    
        allocation[i] += velocity[i];
    
        if(checkAllocation(i)) {
 /*       
            if(allocation[i] <= LL[0]) {
            
                allocation[i] = LL[0];
                velocity[i] = (-0.5) * velocity[i];
                //cout << velocity[i] << endl;
                
            } else if(allocation[i] >= UL[0]) {
            
                allocation[i] = UL[0];
                velocity[i] = (-0.5) * velocity[i];
                //cout << velocity[i] << endl;
            
            }
*/
        
            genAllocation(i);
            velocity[i] = alea.alea_rand(LL[0] - allocation[i], UL[0] - allocation[i]);
            //initVelocity();
        }
           
            
    }

}

void Solution::updateLocalBest() {

    if(localFitness > fitness) {
        
        localBest = allocation;
        localFitness = fitness;
    
    }

}

double Solution::RAND() {

    return (double) rand() / RAND_MAX;

}

bool Solution::checkAllocation(int idx) {

    if(allocation[idx] > UL[idx] || allocation[idx] < LL[idx])
        return true;
        
    return false;

}

void Solution::printData() {

    for(int i = 0; i < dimension; ++i) {
    
        cout << allocation[i] << " " ; 
    
    }
    
    cout << endl;

}

void Solution::calFitness() {

    fitness = 0;
    
    //cout << parameter.FUNC_NUM << endl;
    
    switch(parameter.FUNC_NUM) {
            
         case 0:
            
            //fitness += 25;
            
            for(int i = 0; i < dimension; ++i)
                fitness += allocation[i] * allocation[i];
            
            //fitness = abs(fitness);
            break;
            
        case 1:
            
            fitness += 25;
            
            for(int i = 0; i < dimension; ++i)
                fitness += ceil(allocation[i]);
            
            //fitness = abs(fitness);
            break;
        case 2:         
            
            for(int i = 0; i < dimension; ++i)
                fitness += pow(floor(allocation[i] + 0.5), 2);
            
            break;
        case 16:         
            
            for(int i = 0; i < dimension - 1; ++i)
                fitness += 100 * pow(allocation[i + 1] - pow(allocation[i], 2), 2) + pow(allocation[i] - 1, 2);
            
            break;
        case 22:
            fitness += 10 * dimension;
            
            for(int i = 0; i < dimension; ++i)
                fitness += pow(allocation[i], 2) - 10 * cos(2 * M_PI * allocation[i]);// + 10;
            
            break;
        case 23:
            //fitness += 418.9829 * dimension;
            
            for(int i = 0; i < dimension; ++i)
                fitness -= (allocation[i] * sin(pow(abs(allocation[i]), 0.5)));
            
            break;
        case 28:
         
            fitness = 4 * pow(allocation[0], 2) - 2.1 * pow(allocation[0], 4) + (1.0 / 3.0) * pow(allocation[0], 6) + allocation[0] * allocation[1] - 4 * pow(allocation[1], 2) + 4 * pow(allocation[1], 4);
            
            //fitness = abs(1.03163 + fitness);
            break;
        case 41:
        {
            fitness += 1;
            
            double sum = 0;
            
            for(int i = 1; i < dimension + 1; ++i)
                sum += pow(allocation[i - 1], 2);
        
            sum = sum / 4000;
        
            double product = 1;
            
            for(int i = 1; i < dimension + 1; ++i)
                product *= cos(allocation[i - 1] / pow(i, 0.5));
        
            fitness += sum - product;

            break;
        }
            
        case 101:
         
            //fitness += - 450;
            
            for(int i = 0; i < dimension; ++i)
                fitness += pow(allocation[i], 2) ;
            
            //fitness = abs(1.03163 + fitness);
            break;
            
        case 202:
         
            fitness += -1.300E+03;
            
            for(int i = 0; i < dimension; ++i)
                fitness += pow(pow(10, 6), ((i - 1) / (dimension - 1))) * pow(allocation[i], 2);
            
            //fitness = abs(1.03163 + fitness);
            break;
            
        default:
            cout << "unknown function" << endl;
            break;
    }

}


//SPSO2011
