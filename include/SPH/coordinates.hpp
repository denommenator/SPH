#pragma once

#include <Eigen/Dense>
#include <Eigen/src/Core/util/Constants.h>


#include <string>
#include <vector>
#include <set>
#include <map>



const int DIMENSION = 2;
using num_t = double;
//using Coordinate = Eigen::Array<num_t, DIMENSION, 1>;
using NumericalVectorArray = Eigen::Array<num_t, DIMENSION, Eigen::Dynamic>;
using coordinate_name_map = std::map<std::string, int>;


class Coordinates : public NumericalVectorArray 
{
public:
	using NumericalVectorArray::NumericalVectorArray;

	static Coordinates Zero();
	

	static void set_coordinates_by_names(std::set<std::string> names);
	static std::set<std::string> get_coordinate_names();



private:
	static coordinate_name_map coordinate_names;
	static int num_coords() {return coordinate_names.size();}
};

