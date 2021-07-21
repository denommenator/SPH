#include <SPH/coordinates.hpp>
#include <SPH/pressure_eos.hpp>

#include <cmath>

#include <catch2/catch.hpp>


using namespace SPH;
num_t c{15}, d_0{1000}, gamma{7};

num_t cole(num_t d)
{
	return (d_0 * c * c / gamma)*(pow(d/d_0, gamma) - 1);
}

SCENARIO("initialize various Cole EOS objects")
{
	ColeEOS rho = ColeEOS(15, 1000, 7);

	REQUIRE(rho(1500) == Approx(cole(1500)));
}