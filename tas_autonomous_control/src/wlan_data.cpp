#include "wlan_data.h"
#include <sstream>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::ostringstream;
using std::stringstream;

string wlan_data::wlan_address(string& line)
{
  string address ("Address: ");
  string address_data;
  int begin = line.find(address);
  int offset = address.size();
  int end = line.size();
  address_data = line.substr(begin+offset,end);
  return address_data;
}

string wlan_data::wlan_signal(string& line)
{
  string signal ("  Signal level=");
  string signal_data;
  int begin = line.find(signal);
  int offset = signal.size();
  int end = 3;
  signal_data = line.substr(begin+offset,end);
  return signal_data;
}

string wlan_data::wlan_essid(string& line)
{
  string essid ("ESSID:");
  string essid_data;
  int begin = line.find(essid);
  int offset = essid.size();
  int end = line.size() - (begin + offset + 2);
  essid_data = line.substr(begin+offset+1, end);
  return essid_data;
}

string wlan_data::wlan_quality(string& line)
{
  string quality ("Quality=");
  string quality_data;
  int begin = line.find(quality);
  int offset = quality.size();
  int end = 2;
  quality_data = line.substr(begin+offset,end);
  return quality_data;
}

void wlan_data_write(float x_coord, float y_coord,vector<float> cov_vec, vector<float> orient_vec)
{
  // Convert cov_vec from type vector to type string
  stringstream ss;
  string cov_string;
  ss << '[';
  for (vector<float>::size_type i = 0; i != cov_vec.size(); i++)
    {
      ss << cov_vec[i];
      if ( i != cov_vec.size() - 1)
	{
	  ss << ',';
	}
    }
  ss << ']';
  ss.str().c_str();
  cov_string = ss.str();

  ss.str("");

  // Convert orient_vec from type vector to type string
  stringstream ss;
  string orient_string;
  ss << '[';
  for (vector<float>::size_type i = 0; i != orient_vec.size(); i++)
    {
      ss << orient_vec[i];
      if ( i != orient_vec.size() - 1)
	{
	  ss << ',';
	}
    }
  ss << ']';
  ss.str().c_str();
  orient_string = ss.str();
  
  // Retrieve real-time wlan data from process and save to text file
  popen("iwlist wlan3 scan | grep -e Address -e Signal -e ESSID > wlan_sources_raw.txt","r");
  
  // Open text file in program in preparation for processing
  std::ifstream myfile("wlan_sources_raw.txt");

  // Definitions for reading in the data
  int number_of_lines = 0;
  std::string line;
  vector<string> wlan_data_vec;

  // Reading each line of text file into a vector of type string
  while (std::getline(myfile, line))
    {
      ++number_of_lines;
      wlan_data_vec.push_back(line);
    }

  // Definitions for writing data
  int index = 0;
  string output;
  std::ostringstream x_string;
  x_string << x_coord;
  std::ostringstream y_string;
  y_string << y_coord;

  // Preparing database text file.  Each time wlan_data_write() is called,
  // new readings will be appended.
  std::ofstream log("wlan_sources_database.txt", std::ios_base::app | std::ios_base::out);

  // The execution of writing manipulated data
  while (index != number_of_lines)
    {
      // The output variable is a semi-colon separated concatenation of the results of the functions found within
      // the self-defined namespace wlan_data.  Each function extracts information
      // from the vector wlan_data_vec.  output is then appended to the end of the wlan_sources_database.txt
      // file.
      output = x_string.str() + ";" + y_string.str() + ";" + cov_string + ";"+ orient_string + ";" + wlan_data::wlan_address(wlan_data_vec[index]) + ";" +
    wlan_data::wlan_signal(wlan_data_vec[index+2]) +
    ";" + wlan_data::wlan_essid(wlan_data_vec[index+1]);
      cout << output << endl;
      index = index + 3;
      log <<  output << "\n";
    }
}
