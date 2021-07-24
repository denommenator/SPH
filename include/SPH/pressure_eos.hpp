#pragma once


#include <cmath>

#include <SPH/coordinates.hpp>

#include <functional>



namespace SPH
{
using PressureEOS_t = std::function<num_t(num_t)>;

num_t cole_( num_t d, num_t c, num_t d_0, num_t gamma );

// pressure as a function of density d
class PressureEOS 
{
public:

	virtual num_t operator()(const num_t &d);
	PressureEOS_t p;

};

class ColeEOS : public PressureEOS
{
public:
	ColeEOS(num_t c = 15 , num_t d_0 = 1000, num_t gamma = 7 );
	//speed of sound
	num_t c;

	//reference/neutral density kg/m**3
	num_t d_0;

	//heat capacity ratio
	num_t gamma;

	

} ;


extern ColeEOS cole_eos_default_params;



} //namespace SPH