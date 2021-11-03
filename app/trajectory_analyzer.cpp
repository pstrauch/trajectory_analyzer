#include <iostream>
#include <vector>
#include <limits>
#define _USE_MATH_DEFINES

#include "csv_helper.h"
#include "discretization.h"
#include "geometric_statistics.h"
#include <yaml-cpp/yaml.h>

int main()
{   
    //show full precision with cout
    typedef std::numeric_limits<double> dbl;
    std::cout.precision(dbl::max_digits10);

    ///////////////////////////////////////////////////////////// load yaml data
    //create node
    YAML::Node yaml_file = YAML::LoadFile(
        "app/parameters/parameters.yaml");
    
    //data parameters
    const std::string path = yaml_file["path"].as<std::string>();
    const int raw_data_columns = yaml_file["raw_data_columns"].as<int>();
    const double read_factor = yaml_file["factor"].as<double>();

    //extraction parameters
    const bool extract_data = yaml_file["extract_data"].as<bool>();
    
    //discretization parameters
    const int discretization_rule = yaml_file["discretization_rule"].as<int>();

    //general parameters
    const bool progress = yaml_file["progress_information"].as<bool>();

    //////////////////////////////////////////////////////////// *load yaml data

    if(progress)
        std::cout << "--Loading Data--" << std::endl;

    //define data vectors
    std::vector<double> vec;    //helper
    std::vector<std::vector<double>> raw_data;
    for(int i = 0; i < raw_data_columns; i++)
        raw_data.push_back(vec);    //fill raw_data vector with column vectors
    std::vector<std::vector<double>> data_points_2d{vec, vec};
    std::vector<std::vector<double>> discretization{vec, vec};

    //read raw data
    read_csv_to_col_vec(raw_data, path, read_factor);
    if(progress)
        std::cout   << " *Data length: " 
                        << raw_data.at(1).size() 
                        << std::endl;

    if(extract_data)
    {
        if(progress)
            std::cout << "--Extracting Data--" << std::endl;

        //load yaml parameters
        const int start_column = yaml_file["start_column"].as<int>();
        const int number_of_columns = yaml_file["number_of_columns"].as<int>();
        const int start_row = yaml_file["start_row"].as<int>();
        const int number_of_rows = yaml_file["number_of_rows"].as<int>();

        extract_data_from_col_vec(  raw_data, 
                                    data_points_2d, 
                                    start_column, 
                                    number_of_columns, 
                                    start_row, 
                                    number_of_rows);

        if(progress)
            std::cout   << " *Extracted data length: " 
                        << data_points_2d.at(0).size() 
                        << std::endl;
    }else
    {
        data_points_2d = raw_data;
    }

    if(progress)
        std::cout << "--Discretizing Trajectory--" << std::endl;

    //discretize trajectory
    switch (discretization_rule)
    {
    case 0:
        discretize_2d_line(discretization);
        break;

    case 1:
        discretize_2d_circle(discretization);
        break;
    
    default:
        std::cerr << "ERROR: Bad Discretization Rule" << std::endl;
        exit(1);
    }
    
    if(progress)
        std::cout   << " *Discretization Grid Size: " 
                    << discretization.at(0).size() 
                    << std::endl;

    if(progress)
        std::cout << "--Computing Root Mean Square Error--" << std::endl;

    //compute rmse
    double rmse = compute_rmse(discretization, data_points_2d);
    std::cout << " *Root Mean Square Error [mm]: " << rmse << std::endl;

    return 0;
}