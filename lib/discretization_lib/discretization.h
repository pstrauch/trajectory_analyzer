#pragma once
#include <vector>


//PRE:  vector with two empty column vectors for x and y points
//POST: computes a discrete set of points for a line specified by x=my+q,
//      which is written to the columns data vectors
void discretize_2d_line(   std::vector<std::vector<double>>& discretization);


//PRE:  vector with two empty column vectors for x and y points
//POST: computes a discrete set of points for a circle of radius and midpoint, 
//      which is written to the columns data vectors
void discretize_2d_circle( std::vector<std::vector<double>>& discretization);