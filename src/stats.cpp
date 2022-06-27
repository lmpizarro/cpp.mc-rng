#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <functional>
#include "stats.hpp"

// See http://miltomiltiadou.blogspot.com/2017/01/statistics-in-c-mean-median-and.html

Statistics getMeanMedianStd(
        const std::vector<  double > &i_vector
        )
{
   Statistics stats;
   std::vector <  double  > vector(i_vector);
   std::sort(vector.begin(),vector.end());
   double sumD = std::accumulate(vector.begin(),vector.end(),0.0);
   stats.mean = sumD/double(vector.size());
   std::vector < double  > Diff(vector.size());
   std::transform(vector.begin(),vector.end(),Diff.begin(),
                  std::bind2nd(std::minus< double  > (),stats.mean));
   stats.stdev  = std::inner_product(Diff.begin(),Diff.end(),
                                      Diff.begin(),0.0);
   stats.median = vector[std::floor(double(vector.size())/2.0)];
   stats.stdev = std::sqrt(stats.stdev/vector.size());
   return stats;
}