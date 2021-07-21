#pragma once

#include "coordinates.hpp"

namespace SPH
{
	
class State
{
public:

	State(Coordinates qs, Coordinates q_dots)
	: qs{qs}, q_dots{q_dots}
	{}

	Coordinates qs;
	Coordinates q_dots;



};


}