

#include <catch2/catch.hpp>

#include <SPH/coordinates.hpp>
#include <SPH/state.hpp>


using namespace SPH;

SCENARIO("we can initialize a state vector with coordinate ids and define qs and q_dots later")
{
	SECTION("We can initialize a state vector from qs and q_dots")
	{
		CoordinateIDManager ids= {"01", "02", "03"};

		State initial_state{ids};
		Coordinates q_not{ids};

		initial_state.qs["01"] << 0,1;
		initial_state.qs["02"] << 2,3;
		initial_state.qs["03"] << 4,5;

		initial_state.q_dots["01"] << 6,7;
		initial_state.q_dots["02"] << 8,9;
		initial_state.q_dots["03"] << 10,11;

		q_not["01"] << 0,0; //not the same
		q_not["02"] << 2,3;
		q_not["03"] << 4,5;

		

		REQUIRE(initial_state.qs == initial_state.qs);
		REQUIRE(initial_state.q_dots == initial_state.q_dots);
		REQUIRE_FALSE(initial_state.qs == q_not);

		SECTION("Acceleration can be computed:")
		{
			REQUIRE_FALSE(initial_state.get_acceleration() == q_not);
		}

	}
}


SCENARIO("we can initialize a state vector with qs and q_dots")
{
	SECTION("We can initialize a state vector from qs and q_dots")
	{
		CoordinateIDManager ids= {"01", "02", "03"};
		Coordinates qs{ids}, q_dots{ids}, q_not{{"01", "02", "03"}};

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

		SECTION("Acceleration can be computed:")
		{
			REQUIRE_FALSE(initial_state.get_acceleration() == q_not);
		}

	}
}

