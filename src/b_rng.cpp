#include <random>
#include "b_rng.hpp"

float frand(){

    const float max = float(RAND_MAX);

    return float(rand()) / max ;

}

double drand(){

    const double max = double(RAND_MAX);

    return double(rand()) / max ;

}

double drand2(){
    return double(rand() % (INTERVAL + 1)) / INTERVAL;
}
