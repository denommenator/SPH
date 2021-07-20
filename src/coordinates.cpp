#include <SPH/coordinates.hpp>
#include <initializer_list>




void Coordinates::set_coordinate_id_map(std::set<std::string> names)
{
	int i=0;
	for (auto name : names)
	{
		coordinate_id_map[name]=i;
		i++;
	}
}


Coordinates::Coordinates(std::set<std::string> names)
{
	coordinate_names = names;
	set_coordinate_id_map(names);
	coordinate_matrix = NumericalVectorArray(DIMENSION, names.size());


}

// Coordinates& Coordinates::operator<<(Eigen::CommaInitializer<NumericalVectorArray> q)
// {
// 	int index = coordinate_id_map[current_coordinate_name];
// 	coordinate_matrix.col(index) << q;
// 	return (*this);
// }

// Eigen::Block<NumericalVectorArray, DIMENSION, 1>& Coordinates::operator[](std::string name)
// {
// 	int index = coordinate_id_map[name];
// 	return coordinate_matrix.col(index);
// }

