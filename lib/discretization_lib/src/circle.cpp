#include <cmath>
#include <vector>
#include <yaml-cpp/yaml.h>
#include <discretization.h>


void discretize_2d_circle( std::vector<std::vector<double>>& discretization)
{
    //x = r*cos(t)
    //y = r*sin(t)

    ///////////////////////////////////////////////////////////// load yaml data
    //create node
    YAML::Node yaml_file = YAML::LoadFile(
        "app/parameters/trajectory_parameters.yaml");

    const int grid_size = yaml_file["grid_size"].as<int>();
    const double para_start = yaml_file["para_start"].as<double>();
    const double para_end = yaml_file["para_end"].as<double>();
    const double radius = yaml_file["radius"].as<double>();
    const double midpoint_x = yaml_file["midpoint_x"].as<double>();
    const double midpoint_y = yaml_file["midpoint_y"].as<double>();
    //////////////////////////////////////////////////////////// *load yaml data

    double step = (para_end - para_start)/(grid_size);

    for(double t = para_start; t < para_end; t += step)
    {
        discretization.at(0).push_back(midpoint_x + radius*cos(t));
        discretization.at(1).push_back(midpoint_y + radius*sin(t));
    }

    //delete last element if gridsize is not met
    if(discretization.at(0).size() == grid_size+1)
    {
        discretization.at(0).pop_back();
        discretization.at(1).pop_back();
    }
}


void discretize_3d_circle( std::vector<std::vector<double>>& discretization)
{
    //x = r*cos(t)
    //y = r*sin(t)
    //z = const for now

    ///////////////////////////////////////////////////////////// load yaml data
    //create node
    YAML::Node yaml_file = YAML::LoadFile(
        "app/parameters/trajectory_parameters.yaml");

    const int grid_size = yaml_file["grid_size"].as<int>();
    const double para_start = yaml_file["para_start"].as<double>();
    const double para_end = yaml_file["para_end"].as<double>();
    const double radius = yaml_file["radius"].as<double>();
    const double midpoint_x = yaml_file["midpoint_x"].as<double>();
    const double midpoint_y = yaml_file["midpoint_y"].as<double>();
    const double height = yaml_file["height"].as<double>();
    //////////////////////////////////////////////////////////// *load yaml data

    double step = (para_end - para_start)/(grid_size);

    for(double t = para_start; t < para_end; t += step)
    {
        discretization.at(0).push_back(midpoint_x + radius*cos(t));
        discretization.at(1).push_back(midpoint_y + radius*sin(t));
        discretization.at(2).push_back(height);
    }

    //delete last element if gridsize is not met
    if(discretization.at(0).size() == grid_size+1)
    {
        discretization.at(0).pop_back();
        discretization.at(1).pop_back();
        discretization.at(2).pop_back();
    }
}