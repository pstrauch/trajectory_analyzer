#include <iostream>
#include <fstream>
#include <vector>
#include "csv_helper.h"


//PRE:  given a vector containint empty column-data-vectors, a valid file path 
//      and a scaling_factor
//POST: reads data from the file specified by path, scales it by the
//      given factor, and writes it into the given column data vectors
template <typename T>
void read_csv_to_col_vec(   std::vector<std::vector<T>>& data, 
                            const std::string path, 
                            const T scaling_factor)
{
    //open file
    std::ifstream ifs;
    ifs.open(path);
    if(!ifs.is_open())
    {
        std::cerr << "Problem when opening file!" << std::endl;
        exit(1);
    }

    T element = 0;

    //iterate through rows
    while(true)
    {
        //iterate through columns
        for(auto& vec : data)
        {
            ifs >> element;

            vec.push_back(element*scaling_factor);
           
            ifs.ignore();  //ignore , or \n
        }
        if(ifs.eof()) //check for end of file
            break;
    }
    
    ifs.close();
}


//PRE:  given a vector containing column-data-vectors, a valid file path,
//      a separator charactor and a scaling_factor
//POST: creates and (over-)writes a file specified by path and writes the 
//      given data to that csv file
template <typename T>
void write_col_vec_to_csv(  const std::vector<std::vector<T>>& data,
                            const std::string path,
                            const char separator,
                            const T scaling_factor)
{
    //create file
    std::ofstream ofs;
    ofs.open(path, std::ofstream::trunc);
    if(!ofs.is_open())
    {
        std::cerr << "Problem when creating file!" << std::endl;
        exit(1);
    }
    
    //iterate through rows
    for(auto n = 0; n < data.at(0).size(); n++)
    {
        //iterate through columns
        for(auto m = 0; m < data.size(); m++)
        {
            ofs << data.at(m).at(n) << separator;
        }
        //only add endline if it's not the last row
        if(n < data.at(0).size()-1)
            ofs << std::endl;
    }
    ofs.close();
}