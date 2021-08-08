#pragma once



#include "coordinates.hpp"
#include "collisions.hpp"
#include "trajectory_data.hpp"
#include "state.hpp"


namespace SPH
{

class DynamicalSystem
{
public:

	DynamicalSystem(const State &initial_state, const Collisions::Container &container);

	TrajectoryData run_dynamics(int num_steps, num_t dt);
	TrajectoryData step_dynamics(num_t dt);

	TrajectoryData trajectory_data;
	Coordinates initial_qs;
	Coordinates initial_q_dots;
	SPH::Collisions::Container container;
};

} //namespace SPH