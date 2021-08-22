#pragma once

#include <vector>


#include "coordinates.hpp"
#include "collisions.hpp"
#include "trajectory_data.hpp"


namespace SPH
{

class TrajectoryData
{
public:

	TrajectoryData(const Collisions::Container &container);

	Coordinates& current_qs();
	Coordinates& current_q_dots();
	Coordinates& current_q_dot_dots();


	void to_csv(std::string filename);

	std::vector<Coordinates> qs_list{};
	std::vector<Coordinates> q_dots_list{};
	std::vector<Coordinates> q_dot_dots_list{};
	Collisions::Container container;

};

} //namespace SPH