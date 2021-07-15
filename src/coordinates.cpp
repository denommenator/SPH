#include <SPH/coordinates.hpp>

coordinate_name_map Coordinates::coordinate_names = {};

void Coordinates::set_coordinates_by_names(std::set<std::string> names)
{
	
	Coordinates::coordinate_names = {};
	int i=0;
	for(auto name : names)
		Coordinates::coordinate_names.insert(std::make_pair(name, i++));
}

std::set<std::string> Coordinates::get_coordinate_names() 
{
	std::set<std::string> names ={};
	for (auto pair : coordinate_names)
		names.insert(pair.first);

	return names;
}

Coordinates Coordinates::Zero() 
{
		return NumericalVectorArray::Zero(DIMENSION, Coordinates::num_coords());
}



