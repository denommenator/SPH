#pragma once

#include <Eigen/Dense>
#include <Eigen/src/Core/util/Constants.h>


#include <string>
#include <vector>

const int DIMENSION = 2;
using num_t = double;
using NumericalVectorList = Eigen::Array<num_t, DIMENSION, Eigen::Dynamic>;
using coordinate_name_map = std::vector<std::string>;


class Coordinates : public NumericalVectorList {
public:
	using NumericalVectorList::NumericalVectorList;

	static Coordinates Zero();
	

	static void set_coordinates_by_names(coordinate_name_map names);
	static coordinate_name_map get_coordinate_names() {return coordinate_names;}

private:
	static coordinate_name_map coordinate_names;
	static int num_coords() {return coordinate_names.size();}
};

