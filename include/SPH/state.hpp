#pragma once

#include "coordinates.hpp"
#include "kernel.hpp"


class State
{
public:

	State(Coordinates qs, Coordinates q_dots, Kernel W = gaussian_kernel)
	: qs{qs}, q_dots{q_dots}
	{}

	Coordinates get_acceleration();

	Coordinates qs;
	Coordinates q_dots;



};