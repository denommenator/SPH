

#include <SPH/pressure_eos.hpp>

#include <cmath>

namespace SPH
{

ColeEOS::ColeEOS(num_t c , num_t d_0, num_t gamma)
:c{c}, d_0{d_0}, gamma{gamma}
{}

num_t cole_eos( num_t d, num_t c, num_t d_0, num_t gamma )
{
	return    (d_0 * c * c / gamma)*(pow(d/d_0, gamma) - 1);
}

num_t ColeEOS::operator()(const num_t d) const
{
	return cole_eos(d, c, d_0, gamma);
}

} //namespace SPH