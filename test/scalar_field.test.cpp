#include <cmath>

#include <catch2/catch.hpp>

#include <SPH/coordinates.hpp>
#include <SPH/scalar_field.hpp>
#include <SPH/kernel.hpp>

using namespace SPH;

SCENARIO("We can initialize and evaluate a scalar field using SPH interpolation")
{
	CoordinateIDManager ids = {"01", "02"};
	Coordinates qs(ids);
	qs["01"] << 1,2;
	qs["02"] << 3,4;


	ScalarField F(qs);

	F["01"] << 100;
	F["02"] << 200;

	//F({1,2})
	Coordinate r{1,2};
	//F(r);

}