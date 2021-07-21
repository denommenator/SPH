#pragma once

#include <functional>


#include <cmath>

#include <SPH/coordinates.hpp>





namespace SPH
{
// pressure as a function of density d
class PressureEOS 
{
public:
	virtual num_t operator()(const num_t &d);
};

class ColeEOS : public PressureEOS
{
public:
	ColeEOS(num_t c = 15 , num_t d_0 = 1000, num_t gamma = 7 )
	:c{c}, d_0{d_0}, gamma{gamma}
	{}

	//speed of sound
	num_t c;

	//reference/neutral density kg/m**3
	num_t d_0;

	//heat capacity ratio
	num_t gamma{7};

	num_t operator()(const num_t &d);

} ;


extern ColeEOS cole_eos_default;



}