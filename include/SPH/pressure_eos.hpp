#pragma once


#include <cmath>

#include "coordinates.hpp"

#include <functional>



namespace SPH
{


class ColeEOS
{
public:
	ColeEOS(num_t c = 15 , num_t d_0 = 1000, num_t gamma = 7 );
	num_t operator()(const num_t d) const;

	//speed of sound
	num_t c;

	//reference/neutral density kg/m**3
	num_t d_0;

	//heat capacity ratio
	num_t gamma;

	

} ;


} //namespace SPH