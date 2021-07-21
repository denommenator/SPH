#pragma once

#include "coordinates.hpp"
#include "kernel.hpp"

namespace SPH
{
	
class State
{
public:

	State(Coordinates qs, Coordinates q_dots, Kernel kernel = gaussian_kernel)
	: qs{qs}, q_dots{q_dots}, kernel_object{kernel}
	{}

	Coordinates get_acceleration();

	Coordinates qs;
	Coordinates q_dots;
	Kernel kernel_object;



};


}