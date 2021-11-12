#pragma once

#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>


/**
 * Computes the distance between two points in 2D
 * 
 * @param[in] x1 x coordinate of the first point
 * @param[in] y1 y coordinate of the first point
 * @param[in] x2 x coordinate of the second point
 * @param[in] y2 y coordinate of the second point
 * @returns Distance between the two points
 **/
double distance2d(  const double x1, 
                    const double y1, 
                    const double x2, 
                    const double y2);


double distance3d(  const double x1,
                    const double y1,
                    const double z1,
                    const double x2,
                    const double y2,
                    const double z3);


/**
 * Computes the minimal distance between a point and a discrete set of points
 * 
 * @param[in] discretization vector containing a discrete set of points in 
 * column vector format
 * @param[in] x0 x coordinate of the point
 * @param[in] y y coordinate of the point
 * @returns Minimal distance between the point and the discrete set of points
 **/
double min_distance2d_point_disc( 
    const std::vector<std::vector<double>>& discretization,
    const double x0,
    const double y0);


//PRE:  given a discretized set of the trajectory, 
//      discrete data points and an empty distances vector
//      (in the column vector format)
//POST: computes the minimal distances of all data points to the circle and 
//      writes them in the distances vector
void min_distances2d_data_disc(
    const std::vector<std::vector<double>>& discretization,
    const std::vector<std::vector<double>>& data,
    std::vector<double>& distances);


//PRE:  given a discretized set of the trajectory and discrete data points,
//      both in column vector format
//POST: computes the root mean square error, where the error is measured as the 
//      closest distance from the data points to the (discretized) trajectory
double compute_rmse_2d(const std::vector<std::vector<double>>& discretization,
                    const std::vector<std::vector<double>>& data);


//TODO: PRE/POST
double compute_mean(const std::vector<std::vector<double>>& discretization,
                    const std::vector<std::vector<double>>& data);