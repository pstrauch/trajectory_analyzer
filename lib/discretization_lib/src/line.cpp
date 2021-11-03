#include <vector>
#include "discretization.h"

void discretize_line(   std::vector<std::vector<double>>& discretization,
                        const int grid_size,
                        const double para_start,
                        const double para_end,
                        const double m,
                        const double q)
{
    // x = t
    // y = mx + q
    double step = (para_end - para_start)/(grid_size-1);

    for(double t = para_start; t < para_end; t += step)
    {
        discretization.at(0).push_back(t);
        discretization.at(1).push_back(m*t + q);
    }
}