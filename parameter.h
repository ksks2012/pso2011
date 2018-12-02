/** @brief   parameter
 *  @file    parameter.h
 *  @author  AnHong Zheng
 *  @date    2018.4.13.
 *  @note    
 */
 
#ifndef __PARAMETER_H__
#define __PARAMETER_H__

#include <iostream>
#include <string>

#define DEBUGLOG(str)\
//cout << "[In function " << __func__ << " of " << __FILE__ << ", line: " << __LINE__ << "] " << #str << endl;
//printf("[In function %s of %s, line: %d] statement: \""#str"\"\n", __func__, __FILE__, __LINE__);

using namespace std;

const double pi = 3.14159;

/** @brief   Parameter storage
 *  @file    parameter.h
 *  @class   Parameter
 *  @note    to store the user's set
 */ 
class Parameter {

public:
    
  
    int POPULATION;
    int FUNC_NUM;
    
    double Wmax;
    double Wmin;
    
    double C1;
    double C2;
    
    int topology = 0;
    /*
    double LB;
    double UB;
    
    int D;
    */
    
public:

    Parameter();
    ~Parameter();
    
    /* setter */
    
    void setPopultion(int);
    
    void setFuncNum(int);
    
    void setWmax(double);
    void setWmin(double);
    
    void setC1(double);
    void setC2(double);
    
    /*
    void setLB(double);
    
    void setUB(double);
    
    void setD(int);
    */
    
    //void testParameter();

};

#endif
