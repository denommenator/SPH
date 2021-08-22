#pragma once

#include <tuple>

#include "coordinates.hpp"
#include "collisions.hpp"
#include "trajectory_data.hpp"


namespace SPH
{

constexpr num_t drag{.5};

class DynamicalSystem
{
public:

	DynamicalSystem(const State &initial_state, const Collisions::Container &container);

	TrajectoryData run_dynamics(int num_steps, num_t dt);
	TrajectoryData step_dynamics_velocity_verlet(num_t dt);
	TrajectoryData step_dynamics_euler(num_t dt);
	TrajectoryData step_dynamics_midpoint_rule(num_t dt);

	TrajectoryData trajectory_data;
	Coordinates initial_qs;
	Coordinates initial_q_dots;
	SPH::Collisions::Container container;
};

} //namespace SPH