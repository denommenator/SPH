#pragma once

#include <cmath>

#include "coordinates.hpp"

namespace SPH
{



class State
{
public:

	State(Coordinates qs, 
		Coordinates q_dots);

	State(CoordinateIDManager coordinate_ids);

	//template<typename EOS_t = ColeEOS, typename NextStateFunction_t>
	//State next_state(num_t dt, NextStateFunction_t next_state_function, EOS_t p = ColeEOS());
	

	CoordinateIDManager coordinate_ids;
	Coordinates qs;
	Coordinates q_dots;



};

std::ostream& operator<<(std::ostream &strm, const State &s);






} //namespace SPH