#pragma once



#include "coordinates.hpp"
#include "state.hpp"
#include "collisions.hpp"
#include "trajectory_data.hpp"


namespace SPH
{

class DynamicalSystem
{
public:

	DynamicalSystem(const State &initial_state, const Collisions::Container &container);

	TrajectoryData run_dynamics(int num_steps, num_t dt);
	TrajectoryData step_dynamics(num_t dt);

	TrajectoryData trajectory_data;
	State initial_state;
	SPH::Collisions::Container container;
};

} //namespace SPH