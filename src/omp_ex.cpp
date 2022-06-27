#include <omp.h>
#include <iostream>
#include "omp_ex.hpp"
#include "rvgs.hpp"
#include "rngs.hpp"

double area_pi(int N, int seed) {
    
    double x, y, d, pi__;
    int local_counter;
    int counter = 0;

    
    omp_set_dynamic(0); 
    omp_set_num_threads(THREAD_NUM); // set number of threads in "parallel" blocks
    #pragma omp parallel private(x,y,d, local_counter) shared(counter, seed)
    {
        if (omp_get_num_threads() != THREAD_NUM){
            std::cout << "num threads " << omp_get_num_threads() << std::endl;
            abort();
        }
        PutSeed(omp_get_thread_num()+1+seed);
        local_counter = 0;
        #pragma omp parallel for
        for (int i = 0; i < N; i++) {

            x = Uniform(0,1);
            y = Uniform(0,1);
            d = x*x + y*y;
            if (d <=1) {
                    local_counter++;                 
            }        
        }

        #pragma omp critical
        {
            counter += local_counter;

        }
        #pragma omp barrier
        {
            pi__ = 4 * double(counter) / (THREAD_NUM * double(N));
        }
   }
 
    return pi__;
}

/*
https://tildesites.bowdoin.edu/~ltoma/teaching/cs3225-GIS/fall17/Lectures/openmp.html
https://docs.microsoft.com/en-us/cpp/parallel/openmp/a-examples?view=msvc-170
https://web.stanford.edu/class/cs315b/lectures/lecture13.pdf
https://curc.readthedocs.io/en/latest/programming/OpenMP-C.html
https://docs.microsoft.com/de-de/previous-versions/fw509c3b(v=vs.120)?redirectedfrom=MSDN
https://github.com/gabime/spdlog
*/

int test_01(void){
    double sum = 0.0;
    double average;
    int N = 10000;

    for(int i=0; i < N; i ++){
        sum += area_pi(200000, i);

    }

    average = sum / N;

    std::cout << "PI " << average << std::endl; 
    return 0;
}

int simple_omp(void)
{
    int sum, local_sum;
    sum = 0;
    #pragma omp parallel private(local_sum) shared(sum) num_threads(8)
    {
        #pragma omp parallel for
        for(int i = 0; i < 4; i++ ) {
            local_sum = local_sum + i;
        }
        #pragma omp critical 
            sum += local_sum;
            std::cout << omp_get_thread_num() << std::endl;
    }

    std::cout << sum << " sum " << std::endl;
  return 0;
}