#include "matrix_import.h"

using std::ifstream;
using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::stringstream;

// The function takes as its input a single paramter, the string of the
// of the text file to be imported and outputs a nxn matrix comprised of
// two vectors with elements of type float.  The text file has to be
// formatted such that the elements of a row are separated by commas
// and the rows are separated by new lines.

vector< vector<float> > matrix_import(string data_file)
{
  // Define variables to read and save each line of text file.
  vector<string> matrix_row_str;
  string temp_row;
  ifstream matrix_data;

  // Open file to be imported.
  matrix_data.open(data_file.c_str());

  // Reading each line of text file into a vector of type string
  while (std::getline(matrix_data, temp_row))
    {
      matrix_row_str.push_back(temp_row);
    }

  // Definition of variables to process imported data into a matrix
  vector< vector<float> > matrix;
  vector<float> matrix_row;
  vector<string>::iterator iter;

  // MATRIX PROCESSING. Separate string rows into individual elements 
  // separated by commas and save each element into the vector 
  // matrix_row.  Push the finished vector into the matrix vector.
  // Repeat until iterator reaches the end of the vector matrix_row_str.
  for (iter = matrix_row_str.begin() ; iter != matrix_row_str.end(); iter++)
    {
      // Read row from matrix_row_str into the stringstream variable iss.
      stringstream iss(*iter);

      while(iss.good()) 
	{
	  string element_str;
	  float element_fl;
	  getline(iss,element_str,',');
	  element_fl = atof(element_str.c_str());
	  matrix_row.push_back(element_fl);
	}
      matrix.push_back(matrix_row);
      matrix_row.clear();
    }

  return matrix;

}
