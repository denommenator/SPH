#include <SPH/coordinates.hpp>
#include <initializer_list>




CoordinateIDManager::CoordinateIDManager(std::initializer_list<std::string> names)
{
	int i=0;
	for (auto name : names)
	{
		coordinate_names.push_back(name);
		coordinate_id_map[name]=i;
		i++;
	}
}


int CoordinateIDManager::size()
{
	return coordinate_id_map.size();
}


int CoordinateIDManager::operator[](std::string name)
{
	return coordinate_id_map[name];
}

std::string CoordinateIDManager::operator[](int id)
{
	return coordinate_names[id];
}



Coordinates::Coordinates(CoordinateIDManager ids)
:	coordinate_ids{ids},
	coordinate_matrix{DIMENSION, ids.size()}
{}


NumericalVectorArray::ColXpr Coordinates::operator[](std::string name)
{
	int index = coordinate_ids[name];
	return coordinate_matrix.col(index);
}