#pragma once

#include <cmath>
#include <functional>


#include "pressure_eos.hpp"
#include "coordinates.hpp"
#include "kernels.hpp"
#include "state.hpp"

namespace SPH
{
namespace Integrators
{

// class Integrator
// {
// public:
// 	Integrator(NextState_t next_state_function, NextState_t initial_next_state_function);

// 	template<typename EOS_t = ColeEOS, typename NextStateFunction_t>
// 	State next_state(State s, num_t dt, NextStateFunction_t next_state_function, EOS_t p = ColeEOS());
	
// 	template<typename EOS_t = ColeEOS>
// 	State initial_next_state(State s, num_t dt, EOS_t p = ColeEOS());

// 	NextState_t next_state_function;
// 	NextState_t initial_next_state_function;

// };


template<typename EOS_t = ColeEOS>
State explicit_euler_next(const State &s, num_t dt, EOS_t p = ColeEOS())
{
	Coordinates qs_next{s.qs}, q_dots_next{s.q_dots};

	Coordinates q_dot_dots{s.get_acceleration(p)};

	qs_next.coordinate_matrix += dt * s.q_dots.coordinate_matrix;
	q_dots_next.coordinate_matrix += dt * q_dot_dots.coordinate_matrix;

	State s_next{qs_next, q_dots_next};

	return s_next;

}

}//namespace Integrators
}//namespace SPH