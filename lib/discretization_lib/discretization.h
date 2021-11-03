#pragma once
#include <vector>


//PRE:  vector with two empty column vectors for x and y points
//POST: computes a discrete set of points for a circle of radius and midpoint, 
//      which is written to the columns data vectors
void discretize_circle( std::vector<std::vector<double>>& discretization,
                        const int grid_size,
                        const double para_start,
                        const double para_end,
                        const double radius,
                        const double midpoint_x,
                        const double midpoint_y);


//PRE:  vector with two empty column vectors for x and y points
//POST: computes a discrete set of points for a line specified by x=my+q,
//      which is written to the columns data vectors
void discretize_line(   std::vector<std::vector<double>>& discretization,
                        const int grid_size,
                        const double para_start,
                        const double para_end,
                        const double m,
                        const double q);