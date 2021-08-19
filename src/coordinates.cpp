#include <SPH/coordinates.hpp>
#include <vector>
#include <initializer_list>

namespace SPH{

CoordinateIDManager::CoordinateIDManager(const std::initializer_list<std::string> &names)
:CoordinateIDManager(std::vector<std::string>(names))
{}

CoordinateIDManager::CoordinateIDManager(const std::vector<std::string> &names)
:coordinate_names{names}, coordinate_masses(NumericalScalarArray::Constant(names.size(), 1000)), coordinate_densities(NumericalScalarArray::Constant(names.size(), 1000))
{
	int i=0;
	for (auto name : names)
	{
		coordinate_id_map[name]=i;
		i++;
	}
}


int CoordinateIDManager::size() const
{
	return coordinate_id_map.size();
}


int CoordinateIDManager::operator[](std::string name) const
{
	return coordinate_id_map.at(name);
}

std::string CoordinateIDManager::operator[](int id)const 
{
	return coordinate_names[id];
}

bool operator==(const CoordinateIDManager &ids, const CoordinateIDManager &other_ids)
{
	return ids.coordinate_names == other_ids.coordinate_names;
}

bool operator!=(const CoordinateIDManager &ids, const CoordinateIDManager &other_ids)
{
	return ids.coordinate_names != other_ids.coordinate_names;
}



Coordinates::Coordinates(CoordinateIDManager ids)
:	coordinate_ids{ids}
{
	coordinate_array = coordinate_array_t(ids.size(), Coordinate{});
}


Coordinates Coordinates::Zero(CoordinateIDManager ids)
{
	Coordinates Zero = Coordinates(ids);
	Zero.coordinate_array = coordinate_array_t(ids.size(), Coordinate::Zero());
	return Zero;
}


Coordinate& Coordinates::operator[](std::string name)
{
	int index = coordinate_ids[name];
	return coordinate_array[index];
}

const Coordinate& Coordinates::operator[](std::string name) const
{
	int index = coordinate_ids[name];
	return coordinate_array[index];
}

Coordinate& Coordinates::operator[](int id)
{
	return coordinate_array[id];
}

const Coordinate& Coordinates::operator[](int id) const
{
	return coordinate_array[id];
}

coordinate_array_t::iterator Coordinates::begin()
{
	return coordinate_array.begin();
}

coordinate_array_t::const_iterator Coordinates::begin() const
{
	return coordinate_array.begin();
}

coordinate_array_t::const_iterator Coordinates::cbegin() const
{
	return coordinate_array.cbegin();
}

coordinate_array_t::iterator Coordinates::end()
{
	return coordinate_array.end();
}

coordinate_array_t::const_iterator Coordinates::end() const
{
	return coordinate_array.end();
}

coordinate_array_t::const_iterator Coordinates::cend() const
{
	return coordinate_array.cend();
}

bool operator==(const Coordinates &qs, const Coordinates &qs_other)
{
	if(qs.coordinate_ids != qs_other.coordinate_ids)
		return false;

	auto q_other_it = qs_other.cbegin();
	for(auto&& q : qs)
	{
		if( not q.isApprox(*q_other_it))
			return false;
		q_other_it++;
	}

	return true;

}

int Coordinates::size() const
{
	return coordinate_ids.size();
}

std::ostream& operator<<(std::ostream &strm, const Coordinates &qs)
{
	int i=0;
	for(auto name : qs.coordinate_ids.coordinate_names)
	{
		strm << "\ncoordinate: \"" << name << "\":\n" << qs.coordinate_array[i];
		i++;
	}
	return strm;
}

} //namespace SPH