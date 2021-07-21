#pragma once

#include "coordinates.hpp"
#include "kernel.hpp"

namespace SPH
{
	
class State
{
public:

	State(Coordinates qs, Coordinates q_dots, SmoothingKernel W = W_gaussian)
	: qs{qs}, q_dots{q_dots}, W{W}
	{}

	Coordinates get_acceleration();

	Coordinates qs;
	Coordinates q_dots;
	SmoothingKernel W;



};


}