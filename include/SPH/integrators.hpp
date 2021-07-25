#pragma once

#include <cmath>
#include <functional>


#include "coordinates.hpp"
#include "kernels.hpp"
#include "state.hpp"

namespace SPH
{
namespace Integrators
{
using NextState_t = std::function<State(State, num_t)>;

class Integrator
{
public:
	Integrator(NextState_t next_state_function, NextState_t initial_next_state_function);


	State next_state(State s, num_t dt);
	State initial_next_state(State s, num_t dt);

	NextState_t next_state_function;
	NextState_t initial_next_state_function;

};

extern Integrator explicit_euler;

}//namespace Integrators
}//namespace SPH