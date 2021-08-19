#include <SPH/coordinates.hpp>
#include <Eigen/Dense>


#include <catch2/catch.hpp>

#include <string>

#include <vector>

using namespace SPH;

SCENARIO("Coordinates can be initialized from a CoordinateIDManager", "[coordinates]")
{
	
	CoordinateIDManager ids = {"01", "02"};
	//std::set<std::string> names = {"01", "02"};
	Coordinates qs(ids);
	qs["01"] << 1,2;
	qs["02"] << 3,4;
	
	CAPTURE(qs["01"], qs["02"]);

	REQUIRE(qs["01"](0)==1);
	REQUIRE(qs["01"](1)==2);

	REQUIRE(qs["02"](0)==3);
	REQUIRE(qs["02"](1)==4);

	THEN("We can range-based for loop over the coordinates")
	{	
		int i{1};
		for(auto&& q : qs)
		{
			REQUIRE(q(0) == i);
			REQUIRE(q(1) == i + 1);
			i += 2;
		}

	}

	AND_THEN("We can use the Coordinates comparison operators")
	{
		REQUIRE(qs == qs);
	}


	AND_THEN("We can initialize a zero Coordinates")
	{
		Coordinates zero = Coordinates::Zero(ids);
		for(auto q : zero)
			REQUIRE(q.isApprox(Coordinate::Zero()));
	}

};








