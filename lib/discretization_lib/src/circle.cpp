#include <cmath>
#include <vector>
#include <discretization.h>


void discretize_circle( std::vector<std::vector<double>>& discretization,
                        const int grid_size,
                        const double para_start,
                        const double para_end,
                        const double radius,
                        const double midpoint_x,
                        const double midpoint_y)
{
    //x = r*cos(t)
    //y = r*sin(t)
    double step = (para_end - para_start)/(grid_size-1);

    for(double t = para_start; t < para_end; t += step)
    {
        discretization.at(0).push_back(midpoint_x + radius*cos(t));
        discretization.at(1).push_back(midpoint_y + radius*sin(t));
    }
}