#pragma once

#include <Eigen/Dense>
#include <Eigen/src/Core/util/Constants.h>


#include <string>
#include <vector>
#include <set>
#include <map>
#include <initializer_list>


namespace SPH
{

const int DIMENSION = 2;
using num_t = double;
using Coordinate = Eigen::Array<num_t, DIMENSION, 1>;
using NumericalVectorArray = Eigen::Array<num_t, DIMENSION, Eigen::Dynamic>;
using NumericalScalarArray  = Eigen::Array<num_t, 1, Eigen::Dynamic>;




class CoordinateIDManager
{
public:
	CoordinateIDManager(const std::initializer_list<std::string> &names);


	int size();
	int operator[](std::string name);
	std::string operator[](int id);

	friend bool operator==(const CoordinateIDManager &ids, const CoordinateIDManager &other_ids);



	std::map<std::string, int> coordinate_id_map;
	//names kept in order: id == coordinate_id_map[coordinate_names[id]]
	std::vector<std::string> coordinate_names;
	NumericalScalarArray coordinate_masses;
	NumericalScalarArray coordinate_densities;
};



class Coordinates 
{
public:

	Coordinates(CoordinateIDManager ids);
	
	friend bool operator==(const Coordinates &qs, const Coordinates &qs_other);

	static Coordinates Zero();
	int size();

	NumericalVectorArray::ColXpr operator[](std::string name);

	
	CoordinateIDManager coordinate_ids;
	NumericalVectorArray coordinate_matrix;

};

} //namespace SPH
