#include <SPH/coordinates.hpp>
#include <Eigen/Dense>


#include <catch2/catch.hpp>

#include <string>

#include <vector>


SCENARIO("Coordinates can be read in")
{
	std::set<std::string> names = {"01", "02"};
	Coordinates qs(names);
	qs["01"] << 1,2;
	qs["02"] << 3,4;
	
	CAPTURE(qs["01"], qs["02"]);

	REQUIRE(qs["01"](0)==1);
	REQUIRE(qs["01"](1)==2);

	REQUIRE(qs["02"](0)==3);
	REQUIRE(qs["02"](1)==4);

};








