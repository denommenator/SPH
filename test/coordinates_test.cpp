#include <SPH/coordinates.hpp>
#include <Eigen/Dense>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <string>
#include <vector>



TEST_CASE( "Catch2 works", "[catch]") {
	REQUIRE(1==1);
}


SCENARIO("Coordinate names/existence can be set up and initialized correctly", 
	"[coordinates]") {

	GIVEN("the coordinate names can be set")	{
		coordinate_name_map names = {"01", "02", "03", "10"};
		Coordinates::set_coordinates_by_names(names);
		REQUIRE(Coordinates::get_coordinate_names() == names);
		
		THEN("a zero vector can be initialized")	{
			Coordinates qs = Coordinates::Zero();

			REQUIRE(qs.cols() == names.size());

			for(int column=0 ; column < names.size() ; column++)
				for(int row =0 ; row < DIMENSION ; row++)
				{
					REQUIRE(qs(row, column) == 0);
				}

		}

	}
	
}











