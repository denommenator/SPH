#pragma once

#include <cmath>
#include <functional>
#include <tuple>


#include "pressure_eos.hpp"
#include "coordinates.hpp"
#include "kernels.hpp"
#include "vector_field.hpp"
#include "state.hpp"

namespace SPH
{
namespace Integrators
{


template<typename EOS_t = ColeEOS>
State explicit_euler_next(const State &s, const Coordinates &q_dot_dots, num_t dt, const Kernels::SmoothingKernel W = Kernels::SmoothingKernel(), const EOS_t p = ColeEOS())
{
	const Coordinates& qs{s.qs}, q_dots{s.q_dots};
	
	State s_next{s};
	Coordinates& qs_next{s_next.qs}, q_dots_next{s_next.q_dots};

	qs_next.coordinate_matrix += dt * q_dots.coordinate_matrix;
	q_dots_next.coordinate_matrix += dt * q_dot_dots.coordinate_matrix;

	return s_next;
}

template<typename EOS_t = ColeEOS>
std::tuple<State, Coordinates> velocity_verlet_next(const State &s, const Coordinates &q_dot_dots , num_t dt, EOS_t p = ColeEOS())
{
	Coordinates qs_next{s.qs}, q_dots_next{s.q_dots};


	qs_next.coordinate_matrix += dt * s.q_dots.coordinate_matrix
								+ 0.5 * dt * dt * q_dot_dots.coordinate_matrix;

	Coordinates q_dot_dots_next{get_acceleration(qs_next)};

	q_dots_next.coordinate_matrix += 0.5 * dt * 
							( q_dot_dots.coordinate_matrix + 
								q_dot_dots_next.coordinate_matrix);

	return std::make_tuple(State(qs_next, q_dots_next), q_dot_dots_next);

}




}//namespace Integrators
}//namespace SPH