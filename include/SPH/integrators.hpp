#pragma once

#include <cmath>
#include <functional>
#include <tuple>


#include "pressure_eos.hpp"
#include "coordinates.hpp"
#include "kernels.hpp"
#include "vector_field.hpp"

namespace SPH
{
namespace Integrators
{


template<typename EOS_t = ColeEOS>
State explicit_euler_next(const State &s, const Coordinates &q_dot_dots, num_t dt, const Kernels::SmoothingKernel W = Kernels::SmoothingKernel(), const EOS_t p = ColeEOS())
{
	
	State s_next{s};

	auto q_dot_dot_it = q_dot_dots.begin();
	for(auto q_it = s_next.qs.begin(), q_dot_it = s_next.q_dots.begin();
		q_it != s_next.qs.end();
		q_it++, q_dot_it++, q_dot_dot_it++)
	{ 
		auto& q = *(q_it);
		auto& q_dot = *(q_dot_it);
		auto& q_dot_dot =  *(q_dot_dot_it);

		q += dt * q_dot;
		q_dot += dt * q_dot_dot;
	}
	return s_next;
}

template<typename EOS_t = ColeEOS>
State midpoint_rule_next(const State &s, const Coordinates &q_dot_dots, num_t dt, const Kernels::SmoothingKernel W = Kernels::SmoothingKernel(), const EOS_t p = ColeEOS())
{
	const State midpoint_state = explicit_euler_next(s, q_dot_dots, dt/2, W, p);
	const Coordinates midpoint_q_dot_dots = get_acceleration(midpoint_state.qs);

	
	State s_next{s};

	auto midpoint_q_dot_dot_it = q_dot_dots.begin();
	auto midpoint_q_dot_it = midpoint_state.q_dots.begin();
	for(auto q_it = s_next.qs.begin(), q_dot_it = s_next.q_dots.begin();
		q_it != s_next.qs.end();
		q_it++, q_dot_it++, midpoint_q_dot_dot_it++, midpoint_q_dot_it++)
	{ 
		auto &q = *(q_it), &q_dot = *(q_dot_it);
		auto& midpoint_q_dot = *(midpoint_q_dot_it);
		auto& midpoint_q_dot_dot =  *(midpoint_q_dot_dot_it);
		
		q += dt * midpoint_q_dot;
		q_dot += dt * midpoint_q_dot_dot;
	}
	return s_next;
}


// template<typename EOS_t = ColeEOS>
// std::tuple<State, Coordinates> velocity_verlet_next(const State &s, const Coordinates &q_dot_dots , num_t dt, EOS_t p = ColeEOS())
// {
// 	Coordinates qs_next{s.qs}, q_dots_next{s.q_dots};


// 	qs_next.coordinate_matrix += dt * s.q_dots.coordinate_matrix
// 								+ 0.5 * dt * dt * q_dot_dots.coordinate_matrix;

// 	Coordinates q_dot_dots_next{get_acceleration(qs_next)};

// 	q_dots_next.coordinate_matrix += 0.5 * dt * 
// 							( q_dot_dots.coordinate_matrix + 
// 								q_dot_dots_next.coordinate_matrix);

// 	return std::make_tuple(State(qs_next, q_dots_next), q_dot_dots_next);

// }




}//namespace Integrators
}//namespace SPH