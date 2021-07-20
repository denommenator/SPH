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





class CoordinateIDManager
{
public:
	CoordinateIDManager(std::initializer_list<std::string> names);


	int size();
	int operator[](std::string name);
	std::string operator[](int id);


	std::map<std::string, int> coordinate_id_map;
	//names kept in order: id == coordinate_id_map[coordinate_names[id]]
	std::vector<std::string> coordinate_names;
};



class Coordinates : public NumericalVectorArray 
{
public:

	Coordinates(CoordinateIDManager ids);

	static Coordinates Zero();
	//Eigen::Block<coordinate_matrix.derived(), DIMENSION, 1>& operator[](std::string name);

	NumericalVectorArray::ColXpr operator[](std::string name);

	
	CoordinateIDManager coordinate_ids;
	NumericalVectorArray coordinate_matrix;

};

