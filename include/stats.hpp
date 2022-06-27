#if !defined( _STATS_ )
#define _STATS_
#include <vector>

typedef struct Statistics {
   double mean;
   double median;
   double stdev;
} Statistics;

Statistics getMeanMedianStd(
        const std::vector<  double > &i_vector
);

#endif