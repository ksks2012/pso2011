#include "gammafunc.h"

double GammaFunc::lower(double p, double a) {

    if(a < SMALLEST_FLOAT32) {
    
        return NaN;
    
    } 
    
    if(p > 1 || p < 0) {
    
        return NaN;
        
    } else if(p == 0) {
    
        return 0;
    
    } else if(p == 1) {
    
        return INF;
    
    }
    
    return compute(a, p, 1 - p);

}


double GammaFunc::upper(double p, double a) {

    if(a < SMALLEST_FLOAT32) {
    
        return NaN;
    
    } 
    
    if(p > 1 || p < 0) {
    
        return NaN;
        
    } else if(p == 0) {
    
        return INF;
    
    } else if(p == 1) {
    
        return 0;
    
    }
    
    return compute(a, 1 - p, p);
    
}

double GammaFunc::compute(double a, double p, double q) {

    bool pcase;
    double porq;
    double s;

    if(p < 0.5) {
    
        pcase = true;
        porq = p;
        s = -1;
    
    } else {
    
        pcase = false;
        porq = q;
        s = 1;
    
    }
    
    int k = 0;
    int m = 0;
    
    double x0 = 0;
    
    double xr;
    
    if(abs(a - 1) < 1e-4) {
    
        if(pcase) {
        
            if(p < 1e-3) {
            
                double pArray[5];
                
                pArray[0] = p;
                
                for(int i = 1; i < 5; ++i) {
                
                    pArray[i] = pArray[i - 1] * p;
                               
                }
            
                x0 = p + pArray[1] * 0.5 + pArray[2] * (1/3) + pArray[3] * 0.25 + pArray[4] * 0.2 + pArray[5] * (1/6);
            
            } else {
            
                x0 = -1 * log(1 - p);
            
            }
        
        } else {
        
            x0 = -1 * log(q);
        
        }
        
        
        if ( a == 1 ) {
        
			k = 2;
			xr = x0;
			
		} else {
		
			//lgamma = gamma.log( a );
			k = 1;
			
		}
    
    }
    

    return 0.0;

}


