#include <random>
#include <iostream>
#include <vector>
#include "mc_ex.hpp"
#include "fmt.hpp"
#include "stats.hpp"

// see https://blogs.sas.com/content/iml/2016/03/14/monte-carlo-estimates-of-pi.html

const int nrolls = 1000;

int pibyarea(int iterations=10){

  std::vector<double> values;

  std::random_device rd;  // Will be used to obtain a seed for the random number engine
  std::mt19937 genx(rd()); // Standard mersenne_twister_engine seeded with rd()
  std::minstd_rand geny(rd()); // Standard mersenne_twister_engine seeded with rd()
  std::uniform_real_distribution<> dis(0.0, 1.0);

  float average = 0;
  for(int j=1; j<iterations;++j) {
    int inside = 0;
    for (int i=0; i<nrolls; ++i) {
      double x = dis(genx);
      double y = dis(geny);
      if((x*x + y*y) < 1) ++inside;
    }

    double pi = 4.0 * double(inside) / (double(nrolls));
    values.push_back(pi);
    average = (average * (j - 1) + pi) / j;
  }
  
  Statistics stats = getMeanMedianStd(values);
  std::cout << FMT("%11.6f") << average << " " << stats.mean << " " << stats.stdev << std::endl;
  return 0;
}

int pibyaverage(int iterations=10){
  double average;

  std::vector<double> values;

  std::random_device rd;  // Will be used to obtain a seed for the random number engine
  std::mt19937 genx(rd()); // Standard mersenne_twister_engine seeded with rd()
  std::uniform_real_distribution<> dis(0.0, 1.0);


  average = 0.0;
  for(int j=1; j<iterations;++j) {
    double average1 = 0;
    for (int i=1; i<nrolls; ++i) {
      double u1 = dis(genx);
      double u2 = 1 - u1;
      double x1 = std::pow(1-u1*u1, .5);
      double x2 = std::pow(1-u2*u2, .5);
      double ym = .5*(x1+x2);
      average1 = (average1 * (i - 1) + ym) / i;
    }

    values.push_back(average1);
    average = (average * (j - 1) + average1) / j;
  }
  double pi = 4.0 * double(average);

  Statistics stats = getMeanMedianStd(values);
  std::cout << FMT("%11.6f") << pi << " " << 4.0 * stats.mean << " " << stats.stdev << std::endl;
  return 0;
}
