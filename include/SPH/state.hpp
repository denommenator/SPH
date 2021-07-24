#pragma once

#include "coordinates.hpp"
#include "kernels.hpp"

namespace SPH
{
	
class State
{
public:

	State(Coordinates qs, Coordinates q_dots, Kernels::SmoothingKernel W = Kernels::W_gaussian)
	: qs{qs}, q_dots{q_dots}, W{W}
	{}

	Coordinates get_acceleration();

	Coordinates qs;
	Coordinates q_dots;
	Kernels::SmoothingKernel W;



};


} //namespace SPH