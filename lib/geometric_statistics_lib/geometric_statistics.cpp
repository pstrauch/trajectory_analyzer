#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

#include <geometric_statistics.h>


double distance2d(  const double x1, 
                    const double y1, 
                    const double x2, 
                    const double y2)
{
    //( (x2-x1)^2 + (y2-y1)^2 ) ^ (1/2)
    return sqrt(pow(x2 - x1 , 2) + pow(y2 - y1 , 2));
}


double distance3d(  const double x1, 
                    const double y1, 
                    const double z1,
                    const double x2, 
                    const double y2,
                    const double z2)
{
    //( (x2-x1)^2 + (y2-y1)^2 + (z2-z1)^2 ) ^ (1/2)
    return sqrt(pow(x2 - x1 , 2) + pow(y2 - y1 , 2) + pow(z2 - z1 , 2));
}


double min_distance2d_point_disc( 
    const std::vector<std::vector<double>>& discretization,
    const double x0,
    const double y0)
{
    std::vector<double> distances;

    for(auto i = 0; i < discretization.at(0).size(); i++)
    {
        double result = distance2d(
            x0, 
            y0, 
            discretization.at(0).at(i), 
            discretization.at(1).at(i));
        
        distances.push_back(result);
    }

    return *min_element(distances.begin(), distances.end());
}


double min_distance3d_point_disc( 
    const std::vector<std::vector<double>>& discretization,
    const double x0,
    const double y0,
    const double z0)
{
    std::vector<double> distances;

    for(auto i = 0; i < discretization.at(0).size(); i++)
    {
        double result = distance3d(
            x0, 
            y0, 
            z0,
            discretization.at(0).at(i), 
            discretization.at(1).at(i),
            discretization.at(2).at(i));
        
        distances.push_back(result);
    }

    return *min_element(distances.begin(), distances.end());
}


/**
 * Computes the minimal distance from each data point to a discrete set
 * of points
 * 
 * @param[in] discretization vector containing a discrete set of points in 
 * column vector format
 * @param[in] data vector containing the data points in column vector format
 * @param[out] distances vector containing the minimal distance of each
 * data point to the discrete set of points
 **/
void min_distances2d_data_disc(
    const std::vector<std::vector<double>>& discretization,
    const std::vector<std::vector<double>>& data,
    std::vector<double>& distances)
{
    for(auto i = 0; i < data.at(0).size(); i++)
    {
        double result = min_distance2d_point_disc(
            discretization, 
            data.at(0).at(i), 
            data.at(1).at(i));
        
        distances.push_back(result);
        if(result >= 200)
            std::cout   << "Distance of [" 
                        << data.at(0).at(i) 
                        << "," 
                        << data.at(1).at(i) 
                        << "]: " 
                        << result 
                        << std::endl;
    }
}


void min_distances3d_data_disc(
    const std::vector<std::vector<double>>& discretization,
    const std::vector<std::vector<double>>& data,
    std::vector<double>& distances)
{
    for(auto i = 0; i < data.at(0).size(); i++)
    {
        double result = min_distance3d_point_disc(
            discretization, 
            data.at(0).at(i), 
            data.at(1).at(i),
            data.at(2).at(i));
        
        distances.push_back(result);
        if(result >= 200)
            std::cout   << "Distance of [" 
                        << data.at(0).at(i) 
                        << "," 
                        << data.at(1).at(i) 
                        << "," 
                        << data.at(2).at(i) 
                        << "]: " 
                        << result 
                        << std::endl;
    }
}


/**
 * Computes the root mean squared error, where the error is measured as the
 * closest 2D distance (x,y) from the data points to a discrete set of points
 * 
 * @param[in] discretization vector containing a discrete set of points in 
 * column vector format
 * @param[in] data vector containing the data points in column vector format
 * @returns the 2d root mean squared error
 **/
double compute_rmse_2d(const std::vector<std::vector<double>>& discretization,
                    const std::vector<std::vector<double>>& data)
{
    std::vector<double> errors;
    min_distances2d_data_disc(discretization, data, errors);

    double sum = 0;
    for(double i : errors)
        sum += pow(i,2);
    
    return sqrt(sum/(data.at(0).size()) );
}


double compute_rmse_3d(const std::vector<std::vector<double>>& discretization,
                    const std::vector<std::vector<double>>& data)
{
    std::vector<double> errors;
    min_distances3d_data_disc(discretization, data, errors);

    double sum = 0;
    for(double i : errors)
        sum += pow(i,2);
    
    return sqrt(sum/(data.at(0).size()) );
}


double compute_mean(const std::vector<std::vector<double>>& discretization,
                    const std::vector<std::vector<double>>& data)
{
    std::vector<double> errors;
    min_distances2d_data_disc(discretization, data, errors);

    double sum = 0;
    for(double i : errors)
        sum += i;
    
    return sum/(data.at(0).size());
}