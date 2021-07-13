#include <SPH/coordinates.hpp>
#include <Eigen/Dense>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <string>
#include <vector>

TEST_CASE("Register the coordinate names to be used","[coordinates]"){
	std::vector<std::string> names = {"01", "02", "03", "10"};
	for(auto name : names)
		Coordinates::push_coordinate(name);
	
}


TEST_CASE( "Coordinates can be indexed correctly", "[coordinates]" ) {
	Coordinates test_vec1 = Coordinates();
	test_vec1 << 1,2,3;
	REQUIRE(test_vec1[0]==1);
	REQUIRE(test_vec1[1]==2);
	REQUIRE(test_vec1[2]==3);
}




TEST_CASE( "Eigen Coordinates can be indexed correctly", "[coordinates]" ) {
	Eigen::Array3f vec;
	vec << 1,2,3;
	REQUIRE(vec[0]==1);
	REQUIRE(vec[1]==2);
	REQUIRE(vec[2]==3);
}


TEST_CASE( "Catch2 works", "[catch]") {
	REQUIRE(1==1);
}