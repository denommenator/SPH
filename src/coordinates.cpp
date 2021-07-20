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

bool operator==(const CoordinateIDManager &ids, const CoordinateIDManager &other_ids)
{
	return ids.coordinate_names == other_ids.coordinate_names;
}



Coordinates::Coordinates(CoordinateIDManager ids)
:	coordinate_ids{ids},
	coordinate_matrix{DIMENSION, ids.size()}
{}

Coordinates::Coordinates(std::initializer_list<std::string> names)
:	Coordinates{CoordinateIDManager(names)}
{}


NumericalVectorArray::ColXpr Coordinates::operator[](std::string name)
{
	int index = coordinate_ids[name];
	return coordinate_matrix.col(index);
}


bool operator==(const Coordinates &qs, const Coordinates &qs_other)
{
	return (qs.coordinate_ids == qs_other.coordinate_ids) && ( qs.coordinate_matrix.isApprox(qs_other.coordinate_matrix) );
}