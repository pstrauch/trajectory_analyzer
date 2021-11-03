#pragma once
#include <iostream>
#include <fstream>
#include <vector>


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


//PRE:  given a vector containing column data vectors, 
//      an empty vector containing 'number_of_columns' column data vectors
//POST: extracts 'aufeinanderfolgende' rows and columns from the raw data 
//      (specified by start and number of *) and writes them into the 
//      column data vectors
template <typename T>
void extract_data_from_col_vec(  
                    const std::vector<std::vector<T>>& raw_data,
                    std::vector<std::vector<T>>& processed_data,
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