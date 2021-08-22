#include <iostream>
#include <fstream>


#include "coordinates.hpp"
#include "trajectory_data.hpp"

#include "serializers_io_defs.hpp"


namespace SPH
{
namespace Serializers
{

class CSV
{
public:
	CSV(std::string filename);

	//Do not copy these objects. Pass the single one around by reference.
	CSV(const CSV&) = delete;
	CSV& operator=(CSV const&)  = delete;


	~CSV();

	std::ofstream export_csv;

};

CSV& operator<<(CSV &csv, const std::string &text);

void to_csv(TrajectoryData, std::string filename);



}  //namespace Serializers
} //namespace SPH