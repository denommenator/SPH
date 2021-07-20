#include <SPH/coordinates.hpp>
#include <SPH/state.hpp>
#include <Eigen/Dense>


#include <catch2/catch.hpp>

#include <string>
#include <vector>


// SCENARIO("we can initialize a state vector")
// {
// 	SECTION("We can initialize a state vector from qs and q_dots")
// 	{
// 		std::set<std::string> names = {"01", "02", "03"};
// 		Coordinates qs{names}, q_dots{names};

// 		qs["01"] << 0,1;
// 		qs["02"] << 2,3;
// 		qs["03"] << 4,5;

// 		q_dots["01"] << 6,7;
// 		q_dots["02"] << 8,9;
// 		q_dots["03"] << 10,11;

// 		State initial_state{names, qs, q_dots};

// 		REQUIRE(initial_state.qs == qs);
// 		REQUIRE(initial_state.q_dots == q_dots);


// 	}
// }