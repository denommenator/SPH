#include <SPH/integrators.hpp>



namespace SPH
{
namespace Integrators
{

Integrator::Integrator(NextState_t next_state_function, NextState_t initial_next_state_function)
:next_state_function{next_state_function},
 initial_next_state_function{initial_next_state_function}
{}

State Integrator::next_state(State s, num_t dt)
{
	return next_state_function(s, dt);
}

State Integrator::initial_next_state(State s, num_t dt)
{
	return initial_next_state_function(s, dt);
}


State explicit_euler_next(State s, num_t dt)
{
	Coordinates qs_next{s.qs}, q_dots_next{s.q_dots};

	Coordinates q_dot_dots{s.get_acceleration()};

	qs_next.coordinate_matrix += dt * s.q_dots.coordinate_matrix;
	q_dots_next.coordinate_matrix += dt * q_dot_dots.coordinate_matrix;

	State s_next{qs_next, q_dots_next, s.p, s.W};

	return s_next;

}


Integrator explicit_euler{explicit_euler_next, explicit_euler_next};

}//namespace Integrators
}//namespace SPH