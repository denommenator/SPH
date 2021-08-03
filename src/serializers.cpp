#include "SPH/coordinates.hpp"
#include <Eigen/src/Core/util/Constants.h>
#include <SPH/serializers.hpp>


namespace SPH
{
namespace Serializers
{


CSV::CSV(std::string filename)
{
	std::string absolute_filename = std::string(EXPORT_DATA_PATH) + "/" + filename;
	export_csv = std::ofstream(absolute_filename, std::ofstream::trunc);
}




CSV::~CSV()
{
	export_csv.close();
}



CSV& operator<<(CSV &csv, const std::string &text)
{
	csv.export_csv << text;
	return csv;
}


//print the headers for the CSV
CSV& operator<<(CSV &csv, const CoordinateIDManager &ids)
{
	
	if(ids.coordinate_names.empty())
		return csv;
	auto stop = ids.coordinate_names.end();
	stop--;
	for(auto it{ids.coordinate_names.begin()}; it != stop; ++it)
	{
		std::string name = *it;
		csv << name + ".x, " + name + ".y, ";
	}
	csv << ids.coordinate_names.back() << ".x, " + ids.coordinate_names.back() + ".y\n";

	return csv;
}

CSV& operator<<(CSV &csv, const State &s) 
{
	const static Eigen::IOFormat CSVFormat(Eigen::StreamPrecision, 0, ", ");
	
	const Eigen::Matrix<num_t, DIMENSION, Eigen::Dynamic> qs_matrix = s.qs.coordinate_matrix;
	const Eigen::Map<const Eigen::Matrix<num_t, 1, Eigen::Dynamic>> qs_flattened(qs_matrix.data(), s.qs.coordinate_matrix.size());
	csv.export_csv << qs_flattened.format(CSVFormat);
	csv << "\n";
	return csv;
}

void to_csv(TrajectoryData td, std::string filename)
{
	CSV export_csv(filename);
	export_csv << td.current_state().coordinate_ids;
	for(auto &state : td.states)
		export_csv << state;




}

}  //namespace Serializers
} //namespace SPH