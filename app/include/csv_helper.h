
#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>


/** 
 * Reads data of type T from a .csv file and stores it in a data-matrix using 
 * column-vectors
 * 
 * @param[out] data vector containing N empty column vectors (size 0), 
 * where N corresponds to the amount of columns in the .csv file
 * @param[in] path path to the .csv file the data is saved
 * @param[in] scaling_factor the factor by which the read data is multiplied with
 * @throws Error if the .csv cannot be opened
 * @throws Assertion if the column vectors are not of size 0
 * @throws Assertion if the number of columns in the data is not equal to the .csv file
 * @throws Assertion if more than 1e8 rows exist
 **/
template <typename T>
void read_csv_to_col_vec (  std::vector<std::vector<T>>& data, 
                            const std::string path, 
                            const T scaling_factor)
{
    /* ASSERT: column vectors are of size 0 */
    for (auto i = 0; i < data.size(); ++i)
        assert(data.at(i).size() == 0);
    
    /* open file */
    std::ifstream ifs;
    ifs.open(path);
    if (!ifs.is_open())
    {
        std::cerr << "Problem when opening file!" << std::endl;
        exit(1);
    }


    T element = 0;
    char separator;
    const unsigned int ROW_LIMIT = 1e8;
    
    //iterate through rows
    for (unsigned int i = 0; i < ROW_LIMIT; ++i)
    {
        // iterate through columns
        for (auto j = 0; j < data.size(); ++j)
        {
            // read element
            ifs >> element;

            //ASSERT: not end of file (valid data)
            assert(!ifs.eof());

            // scale and store element to data
            data.at(j).push_back(element*scaling_factor);

            // check for last column
            if (j == data.size()-1)
            {
                // ignore separation character
                ifs >> separator; 

                if(ifs.eof()) {
                    ifs.close();    //redundant?
                    return;         //file ended at end of line -> ok
                } else {
                    assert('\n' == separator);     // ASSERT: end of row
                }
            } else {    // not the last column
                // ignore separation character
                ifs >> separator; 

                // assertions
                assert(!ifs.eof());         //ASSERT: not end of file
                assert('\n' != separator);  //ASSERT: not end of row
            }
        }
    }

    // something's wrong
    assert(false);
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


/**
 * Extracts consecutive rows and columns from a data-matrix using column-vectors
 * 
 * @param[in] raw_data data vector containing column vectors
 * @param[out] processed_data vector containing N empty column vectors (size 0),
 * where N corresponds to the number of columns to be extracted
 * @param[in] start_column index of the first column to be extracted
 * @param[in] number_of_columns number of columns to be extracted, including
 * the start column
 * @param[in] start_row index of first row to be extracted
 * @param[in] number_of_rows number of rows to be extracted, including the
 * start row
 * 
 * @throws Assertion if number_of_columns does not correspond to the size
 * of the processed_data vector
 * @throws Assertion if last row / column to be extracted lies outside of the
 * raw_data
 */
template <typename T>
void extract_data_from_col_vec(  
                    const std::vector<std::vector<T>>& raw_data,
                    std::vector<std::vector<T>>& processed_data,
                    const int start_column,
                    const int number_of_columns,
                    const int start_row,
                    const int number_of_rows)
{
    //assert: number_of_columns matches size of processed_data
    assert(processed_data.size() == number_of_columns);

    //assert: last column / row to be extracted lies within the raw_data
    assert(start_column + number_of_columns - 1 <= raw_data.size());
    assert(start_row + number_of_rows - 1 <= raw_data.at(0).size());

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