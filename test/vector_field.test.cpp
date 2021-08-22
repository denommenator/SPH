#include "SPH/vector_field.hpp"
#include <cmath>

#include <catch2/catch.hpp>

#include <SPH/coordinates.hpp>
#include <SPH/scalar_field.hpp>
#include <SPH/kernels.hpp>

using namespace SPH;

SCENARIO("We can find acceleration", "[accel], [vector_field]")
{
	CoordinateIDManager ids = {"01", "02"};
	Coordinates qs(ids);
	qs["01"] << 1,2;
	qs["02"] << 3,4;


	Coordinates accel = get_acceleration(qs);


	CAPTURE(accel);
	REQUIRE_FALSE(accel==Coordinates::Zero(qs.coordinate_ids));
}