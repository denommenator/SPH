#include <string>


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

CSV& operator<<(CSV &csv, const Coordinates &qs) 
{
	const static Eigen::IOFormat CSVFormat(Eigen::StreamPrecision, 0, ", ");
	
	Eigen::Matrix<num_t, 1, Eigen::Dynamic> qs_matrix(DIMENSION * qs.size());
	int idx{0};
	for(auto&& q : qs)
	{
		qs_matrix.block(0, idx, 1, DIMENSION) << q.transpose();
		idx += DIMENSION;
	}
	csv.export_csv << qs_matrix.format(CSVFormat);
	csv << "\n";
	return csv;
}

CSV& operator<<(CSV &csv, const std::vector<Coordinates> &qs_list) 
{
	for(auto &qs : qs_list)
		csv << qs;
	return csv;
}

void to_csv(TrajectoryData td, std::string filename)
{
	CSV export_csv(filename);
	export_csv << td.current_qs().coordinate_ids;
	export_csv << td.qs_list;

	std::string filename_minus_csv = filename.substr(0,filename.size()-4);
	CSV export_q_dots(filename_minus_csv+"_q_dots.csv");
	export_q_dots << td.current_qs().coordinate_ids;
	export_q_dots << td.q_dots_list;

	CSV export_q_dot_dots(filename_minus_csv+"_q_dot_dots.csv");
	export_q_dot_dots << td.current_qs().coordinate_ids;
	export_q_dot_dots << td.q_dot_dots_list;



}

}  //namespace Serializers
} //namespace SPH