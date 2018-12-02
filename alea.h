#ifndef __ALEA_H__
#define __ALEA_H__

#include <climits>
#include <cinttypes>

class Alea {

public:

private:

    //kiss    
    uint32_t kiss_x; //= 1;
    uint32_t kiss_y; //= 2;
    uint32_t kiss_z; //= 4;
    uint32_t kiss_w; //= 8;
    uint32_t kiss_carry = 0;
    uint32_t kiss_k;
    uint32_t kiss_m;

public:

    Alea();
    double alea_rand(double , double);

private:

    void seed_rand_kiss();
    uint32_t rand_kiss();
    
};

#endif
