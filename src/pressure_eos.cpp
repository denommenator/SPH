

#include <SPH/pressure_eos.hpp>

#include <cmath>

namespace SPH
{

ColeEOS cole_eos_default = ColeEOS();


num_t PressureEOS::operator()(const num_t &d)
{
	num_t c{15}, d_0{1000}, gamma{7};
	return    (d_0 * c * c / gamma)*(pow(d/d_0, gamma) - 1);
}

num_t ColeEOS::operator()(const num_t &d)
{
	return    (d_0 * c * c / gamma)*(pow(d/d_0, gamma) - 1);
}


}