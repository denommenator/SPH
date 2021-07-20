#pragma once

#include <Eigen/Dense>
#include <Eigen/src/Core/util/Constants.h>


#include <string>
#include <vector>
#include <set>
#include <map>
#include <initializer_list>



const int DIMENSION = 2;
using num_t = double;
using Coordinate = Eigen::Array<num_t, DIMENSION, 1>;
using NumericalVectorArray = Eigen::Array<num_t, DIMENSION, Eigen::Dynamic>;

using NumericalVectorColumn = NumericalVectorArray::ColXpr;

class Coordinates : public NumericalVectorArray 
{
public:

	Coordinates(std::set<std::string> names);

	static Coordinates Zero();
	//Eigen::Block<coordinate_matrix.derived(), DIMENSION, 1>& operator[](std::string name);

	NumericalVectorColumn operator[](std::string name)
	{
		int index = coordinate_id_map[name];
		return coordinate_matrix.col(index);
	}

	
	

	std::set<std::string> coordinate_names;
	std::map<std::string, int> coordinate_id_map;
	NumericalVectorArray coordinate_matrix;
	std::string current_coordinate_name;

	void set_coordinate_id_map(std::set<std::string> names);
};

