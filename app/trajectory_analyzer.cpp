#include <iostream>
#include <vector>
#include <limits>
#define _USE_MATH_DEFINES

#include "csv_helper.h"
#include "discretization.h"
#include "geometric_statistics.h"


int main()
{   
    //show full precision with cout
    typedef std::numeric_limits<double> dbl;
    std::cout.precision(dbl::max_digits10);

    std::cout << "--Loading Data--" << std::endl;

    //extraction needed
    bool extract_data = false;
    //path to data
    // std::string path = "./log/27_10_circle_delay_5ms.csv";
    // std::string path = "./log/26_10_circle_delay_1ms.csv";
    std::string path = "./log/test/testdata.csv";

    //define data vectors
    std::vector<double> vec;    //helper
    //raw_data: time, x, y, z, roll, pitch, yaw
    // std::vector<std::vector<double>> raw_data{vec, vec, vec, vec, 
    //                                                 vec, vec, vec};
    std::vector<std::vector<double>> raw_data{vec, vec};
    std::vector<std::vector<double>> data_points{vec, vec};
    std::vector<std::vector<double>> discretization{vec, vec};

    //read raw data
    double factor = 1000;
    read_csv_to_col_vec(raw_data, path, factor);
    std::cout   << " *Data length: " 
                    << raw_data.at(1).size() 
                    << std::endl;

    if(extract_data)
    {
        std::cout << "--Extracting Data--" << std::endl;

        // extract_data(raw_data, data_points, 1, 2, 750, 1000);
        extract_data_from_col_vec(raw_data, data_points, 1, 2, 1600, 2000);

        std::cout   << " *Extracted data length: " 
                    << data_points.at(0).size() 
                    << std::endl;
    }

    std::cout << "--Discretizing Trajectory--" << std::endl;

    //discretize trajectory
    /* discretize_circle(  discretization,
                        2000,
                        0,
                        2*M_PI,
                        1500,
                        500,
                        -500); */
    discretize_line(discretization,
                    2000,
                    0,
                    10,
                    0,
                    10);
    
    std::cout   << " *Discretization Grid Size: " 
                << discretization.at(0).size() 
                << std::endl;

    std::cout << "--Computing Root Mean Square Error--" << std::endl;

    //compute rmse
    double rmse = compute_rmse(discretization, data_points);
    std::cout << " *Root Mean Square Error [mm]: " << rmse << std::endl;

    return 0;
}