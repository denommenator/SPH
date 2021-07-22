

#include <SPH/pressure_eos.hpp>

#include <cmath>

namespace SPH
{

ColeEOS cole_eos_default_params = ColeEOS();




num_t PressureEOS::operator()(const num_t &d)
{
	return p(d);
}

num_t cole_( num_t d, num_t c, num_t d_0, num_t gamma )
{
	return    (d_0 * c * c / gamma)*(pow(d/d_0, gamma) - 1);
}

ColeEOS::ColeEOS(num_t c , num_t d_0, num_t gamma )
	:c{c}, d_0{d_0}, gamma{gamma}
	{p = [c, d_0, gamma](num_t d){return cole_(d, c, d_0, gamma);};}


}