#include <SPH/coordinates.hpp>

std::vector<std::string> Coordinates::coordinate_names = {};

void Coordinates::push_coordinate(std::string name){
	Coordinates::coordinate_names.push_back(name);
}
