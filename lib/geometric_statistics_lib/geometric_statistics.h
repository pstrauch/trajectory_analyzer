#pragma once

#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>


//PRE:  Two points (x1, x2),(x2,y2)
//POST: Returns the distance between the two points
double distance(const double x1, 
                const double y1, 
                const double x2, 
                const double y2);


//PRE:  given discretized set of a trajectory (in column vector format)
//      and a point (x0,y0)
//POST: returns the minimal distance of (x0,y0) to the (discretized) trajectory
double min_distance_point_disc( 
    const std::vector<std::vector<double>>& discretization,
    const double x0,
    const double y0);


//PRE:  given a discretized set of the trajectory, 
//      discrete data points and an empty distances vector
//      (in the column vector format)
//POST: computes the minimal distances of all data points to the circle and 
//      writes them in the distances vector
void min_distances_data_disc(
    const std::vector<std::vector<double>>& discretization,
    const std::vector<std::vector<double>>& data,
    std::vector<double>& distances);


//PRE:  given a discretized set of the trajectory and discrete data points,
//      both in column vector format
//POST: computes the root mean square error, where the error is measured as the 
//      closest distance from the data points to the (discretized) trajectory
double compute_rmse(const std::vector<std::vector<double>>& discretization,
                    const std::vector<std::vector<double>>& data);


//TODO: PRE/POST
double compute_mean(const std::vector<std::vector<double>>& discretization,
                    const std::vector<std::vector<double>>& data);