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


SCENARIO("we can initialize a state vector with coordinate ids and define qs and q_dots later", "[state]")
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


	}
}


SCENARIO("we can initialize a state vector with qs and q_dots", "[state]")
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

		
		THEN("We can iterate through the state using range-based for loop")
		{
			std::vector<Coordinate> q_coords = {qs["01"], qs["02"], qs["03"]};
			std::vector<Coordinate> q_dot_coords = {q_dots["01"], q_dots["02"], q_dots["03"]};
			
			auto q_coords_it = q_coords.begin();
			auto q_dot_coords_it = q_dot_coords.begin();

			for(auto&& s : initial_state)
			{
				REQUIRE(s.q.isApprox(*(q_coords_it)));
				q_coords_it++;
			}

			for(auto&& s : initial_state)
			{
				REQUIRE(s.q_dot.isApprox(*(q_dot_coords_it)));
				q_dot_coords_it++;
			}
		}
	}
}





