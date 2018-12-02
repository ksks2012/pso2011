#include "alea.h"
#include <iostream>
using namespace std;

const uint32_t RAND_MAX_KISS= 4294967295;

Alea::Alea() {
    
    kiss_carry = 0;
    seed_rand_kiss();

}

double Alea::alea_rand(double a, double b) {

    double r;
    
    r = (double)rand_kiss() / RAND_MAX_KISS;
    //cout << rand_kiss() << " " << r << endl;
    
    r = a + r * (b - a);
    
    return r;

}

void Alea::seed_rand_kiss() {

    uint32_t seed = 1294404794;

	kiss_x = seed | 1;
	kiss_y = seed | 2;
	kiss_z = seed | 4;
	kiss_w = seed | 8;
	kiss_carry = 0;

}

uint32_t Alea::rand_kiss() 
{
	kiss_x = kiss_x * 69069 + 1;
	kiss_y ^= kiss_y << 13;
	kiss_y ^= kiss_y >> 17;
	kiss_y ^= kiss_y << 5;
	kiss_k = (kiss_z >> 2) + (kiss_w >> 3) + (kiss_carry >> 2);
	kiss_m = kiss_w + kiss_w + kiss_z + kiss_carry;
	kiss_z = kiss_w;
	kiss_w = kiss_m;
	kiss_carry = kiss_k >> 30;

	return kiss_x + kiss_y + kiss_w;
	
}
