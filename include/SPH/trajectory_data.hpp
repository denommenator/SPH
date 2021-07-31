#pragma once

#include <vector>


#include "coordinates.hpp"
#include "state.hpp"
#include "collisions.hpp"
#include "trajectory_data.hpp"


namespace SPH
{

class TrajectoryData
{
public:

	TrajectoryData(const Collisions::Container &container);
	TrajectoryData operator<<(const State &s);

	State& current_state();

	std::vector<State> states{};
	Collisions::Container container;

};

} //namespace SPH