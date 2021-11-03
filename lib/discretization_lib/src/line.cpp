#include <vector>
#include <yaml-cpp/yaml.h>
#include "discretization.h"

void discretize_2d_line(   std::vector<std::vector<double>>& discretization)
{
    // x = t
    // y = mx + q

    ///////////////////////////////////////////////////////////// load yaml data
    //create node
    YAML::Node yaml_file = YAML::LoadFile(
        "app/parameters/trajectory_parameters.yaml");

    const int grid_size = yaml_file["grid_size"].as<int>();
    const double para_start = yaml_file["para_start"].as<double>();
    const double para_end = yaml_file["para_end"].as<double>();
    const double m = yaml_file["gradient"].as<double>();
    const double q = yaml_file["offset"].as<double>();
    //////////////////////////////////////////////////////////// *load yaml data

    double step = (para_end - para_start)/(grid_size);

    for(double t = para_start; t < para_end; t += step)
    {
        discretization.at(0).push_back(t);
        discretization.at(1).push_back(m*t + q);
    }

    //delete last element if gridsize is not met
    if(discretization.at(0).size() == grid_size+1)
    {
        discretization.at(0).pop_back();
        discretization.at(1).pop_back();
    }
}