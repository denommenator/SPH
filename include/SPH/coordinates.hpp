#pragma once

#include <string>
#include <ostream>
#include <vector>
#include <initializer_list>
#include <set>
#include <map>
#include <tuple>

#include <Eigen/Dense>
#include <Eigen/src/Core/util/Constants.h>





namespace SPH
{

const int DIMENSION = 2;
using num_t = double;
using Coordinate = Eigen::Array<num_t, DIMENSION, 1>;
using NumericalVector = Eigen::Array<num_t, DIMENSION, 1>;
using NumericalVectorArray = Eigen::Array<num_t, DIMENSION, Eigen::Dynamic>;
using NumericalScalarArray  = Eigen::Array<num_t, 1, Eigen::Dynamic>;







class CoordinateIDManager
{
public:
	CoordinateIDManager(const std::initializer_list<std::string> &names);

	CoordinateIDManager(const std::vector<std::string> &names);


	int size() const;
	int operator[](std::string name) const;
	std::string operator[](int id) const;

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

	static Coordinates Zero(CoordinateIDManager ids);
	int size() const;

	NumericalVectorArray::ColXpr operator[](std::string name);
	const NumericalVectorArray::ConstColXpr operator[](std::string name) const;
	NumericalVectorArray::ColXpr operator[](int id);
	const NumericalVectorArray::ConstColXpr operator[](int id) const;

	
	CoordinateIDManager coordinate_ids;
	NumericalVectorArray coordinate_matrix;

};


std::ostream& operator<<(std::ostream &strm, const Coordinates &qs);

} //namespace SPH
