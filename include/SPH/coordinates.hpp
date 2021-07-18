#pragma once

#include <Eigen/Dense>
#include <Eigen/src/Core/util/Constants.h>


#include <string>
#include <vector>
#include <set>
#include <map>



const int DIMENSION = 2;
using num_t = double;
using Coordinate = Eigen::Array<num_t, Eigen::Dynamic, Eigen::Dynamic>;
using NumericalVectorArray = Eigen::Array<num_t, DIMENSION, Eigen::Dynamic>;
using coordinate_name_map = std::map<std::string, int>;


class Coordinates : public NumericalVectorArray 
{
public:
	

	Coordinates(void) 
		: NumericalVectorArray{DIMENSION, num_coords()}
	{}

	

	static Coordinates Zero();
	

	static void set_coordinates_by_names(std::set<std::string> names);
	static std::set<std::string> get_coordinate_names();

	Coordinate& operator[](std::string name);

	static int get_coordinate_id(std::string name);


//private:
	//using NumericalVectorArray::NumericalVectorArray;
	
	// This constructor allows you to construct MyVectorType from Eigen expressions
    template<typename OtherDerived>
    Coordinates(const Eigen::ArrayBase<OtherDerived>& other)
        : NumericalVectorArray(other)
    { }

	template<typename OtherDerived>
    Coordinates& operator=(const Eigen::ArrayBase <OtherDerived>& other)
    {
        this->NumericalVectorArray::operator=(other);
        return *this;
    }

	static coordinate_name_map coordinate_names;
	static int num_coords() {return coordinate_names.size();}
};

