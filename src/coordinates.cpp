#include <SPH/coordinates.hpp>

coordinate_name_map Coordinates::coordinate_names = {};

void Coordinates::set_coordinates_by_names(coordinate_name_map names)
{
	Coordinates::coordinate_names = names;
}

Coordinates Coordinates::Zero() 
{
		return NumericalVectorList::Zero(DIMENSION, Coordinates::num_coords());
}