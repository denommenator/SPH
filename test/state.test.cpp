#include <SPH/coordinates.hpp>
#include <SPH/state.hpp>
#include <Eigen/Dense>


#include <catch2/catch.hpp>

#include <string>
#include <vector>


SCENARIO("we can initialize a state vector")
{
	SECTION("We can initialize a state vector from qs and q_dots")
	{
		CoordinateIDManager ids= {"01", "02", "03"};
		Coordinates qs{ids}, q_dots{ids}, q_not{ids};

		qs["01"] << 0,1;
		qs["02"] << 2,3;
		qs["03"] << 4,5;

		q_dots["01"] << 6,7;
		q_dots["02"] << 8,9;
		q_dots["03"] << 10,11;

		q_not["01"] << 0,0; //not the same
		q_not["02"] << 2,3;
		q_not["03"] << 4,5;

		State initial_state{qs, q_dots};

		REQUIRE(initial_state.qs == qs);
		REQUIRE(initial_state.q_dots == q_dots);
		REQUIRE_FALSE(initial_state.qs == q_not);


	}
}