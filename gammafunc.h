#ifndef __GAMMA_FUNC_H__
#define __GAMMA_FUNC_H__

#include <cmath>
#include <climits>
#include <algorithm>
#include <cfloat>

const float SMALLEST_FLOAT32 = 1.1754943508222875e-38;
const double INF = DBL_MAX;
const double NaN = 0.0 / 0.0;

class GammaFunc {

public:

    double lower(double, double);
    double upper(double, double);
    
    double compute(double, double, double);

private:


};

#endif
