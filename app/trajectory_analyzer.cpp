#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#define _USE_MATH_DEFINES
#include <cmath>

#include "csv_helper.h"


//PRE:  Two points (x1, x2),(x2,y2)
//POST: Returns the distance between the two points
double distance(const double x1, 
                const double y1, 
                const double x2, 
                const double y2)
{
    return sqrt(pow(x2 - x1 , 2) + pow(y2 - y1 , 2));
    //( (x2-x1)^2 + (y2-y1)^2 ) ^ (1/2)
}


//PRE:  data vector containing two vectors for x and y positions and other 
        // parameters
//POST: computes a discrete set of points for a circle of radius and midpoint, 
        // which is written to data vectors
void discretize_circle( std::vector<std::vector<double>>& discretization,
                        int grid_size,
                        double para_start, 
                        double para_end, 
                        double radius,
                        double midpoint_x,
                        double midpoint_y)
{
    //x = r*cos(t)
    //y = r*sin(t)
    //r = [0,2*pi]
    double step = (para_end - para_start)/(grid_size-1);

    for(double t = para_start; t < para_end; t += step)
    {
        discretization.at(0).push_back(midpoint_x + radius*cos(t));
        discretization.at(1).push_back(midpoint_y + radius*sin(t));
    }
}


//PRE:  given discretized set of a trajectory and a point (x0,y0)
//POST: returns the minimal distance of (x0,y0) to the (discretized) trajectory
double min_distance_point_disc( 
    const std::vector<std::vector<double>>& discretization,
    const double x0,
    const double y0)
{
    std::vector<double> distances;

    for(auto i = 0; i < discretization.at(0).size(); i++)
    {
        double result = distance(
            x0, 
            y0, 
            discretization.at(0).at(i), 
            discretization.at(1).at(i));
        
        distances.push_back(result);
    }

    return *min_element(distances.begin(), distances.end());
}


//PRE:  given a discretized set of the trajectory, 
//      discrete data points and an empty distances vector
//POST: computes the minimal distances of all data points to the circle and 
//      writes them in the distances vector
void min_distances_data_disc(
    const std::vector<std::vector<double>>& discretization,
    const std::vector<std::vector<double>>& data,
    std::vector<double>& distances)
{
    for(auto i = 0; i < data.at(0).size(); i++)
    {
        double result = min_distance_point_disc(
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


//PRE:  given a discretized set of the trajectory and discrete data points
//POST: computes the root mean square error, where the error is measured as the 
//      closest distance from the data points to the (discretized) trajectory
double compute_rmse(const std::vector<std::vector<double>>& discretization,
                    const std::vector<std::vector<double>>& data)
{
    std::vector<double> errors;
    min_distances_data_disc(discretization, data, errors);

    double sum = 0;
    for(double i : errors)
        sum += pow(i,2);
    
    return sqrt(sum/(data.at(0).size()) );
}

double compute_mean(const std::vector<std::vector<double>>& discretization,
                    const std::vector<std::vector<double>>& data)
{
    std::vector<double> errors;
    min_distances_data_disc(discretization, data, errors);

    double sum = 0;
    for(double i : errors)
        sum += i;
    
    return sum/(data.at(0).size());
}


void extract_data(  const std::vector<std::vector<double>>& raw_data,
                    std::vector<std::vector<double>>& processed_data,
                    const int start_column,
                    const int number_of_columns,
                    const int start_row,
                    const int number_of_rows)
{
    //iterate through rows
    for(int m = 0; m < number_of_rows; m++ )
    {
        //iterate through columns
        for(int n = 0; n < number_of_columns; n++)
        {
            processed_data.at(n).push_back(
                raw_data.at(n+start_column).at(m+start_row));
        }
    }
}


int main()
{   
    //show full precision with cout
    typedef std::numeric_limits<double> dbl;
    std::cout.precision(dbl::max_digits10);

    //path to data
    // std::string path = "./log/27_10_circle_delay_5ms.csv";
    std::string path = "./log/26_10_circle_delay_1ms.csv";

    //data vectors
    std::vector<double> vec;
    std::vector<std::vector<double>> raw_data{vec, vec, vec, vec, 
                                                    vec, vec, vec};   
    //time, x, y, z, roll, pitch, yaw

    //read raw data
    double factor = 1000;
    read_csv_to_col_vec(raw_data, path, factor);

    //process data
    std::vector<std::vector<double>> data_points{vec, vec};
    // extract_data(raw_data, data_points, 1, 2, 750, 1000);
    extract_data(raw_data, data_points, 1, 2, 1600, 2000);
    std::cout << "extracted data length: " << data_points.at(0).size() << std::endl;

    //discretization data vector
    std::vector<std::vector<double>> discretization{vec, vec};

    //discretize trajectory
    discretize_circle(discretization,
                        2000,
                        0,
                        2*M_PI,
                        1500,
                        500,
                        -500);

    std::cout << "disc size: " << discretization.at(0).size() << std::endl;

    double rmse = compute_rmse(discretization, data_points);

    std::cout << "Root Mean Square Error: " << rmse << std::endl;

    // double distance = min_distance_point_disc(discretization, 500, 1100);
    // std::cout << "Distance of (500,1100) to circle: " << distance << std::endl;

    return 0;
}