#pragma once

#include <cmath>

#include "SPH/pressure_eos.hpp"
#include "coordinates.hpp"
#include "kernels.hpp"

namespace SPH
{
	
class State
{
public:

	State(Coordinates qs, 
		Coordinates q_dots, 
		PressureEOS p = cole_eos_default_params, 
		Kernels::SmoothingKernel W = Kernels::W_gaussian)
	: qs{qs}, q_dots{q_dots}, W{W}, p{p}
	{}

	Coordinates get_acceleration();

	Coordinates qs;
	Coordinates q_dots;
	Kernels::SmoothingKernel W;
	PressureEOS p;



};


} //namespace SPH