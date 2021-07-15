#include <SPH/coordinates.hpp>
#include <Eigen/Dense>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <string>
#include <vector>



TEST_CASE( "Catch2 works", "[catch]") 
{
	REQUIRE(1==1);
}


SCENARIO("Coordinate names/existence can be set up and initialized correctly", 
	"[coordinates]") 
{

	GIVEN("the coordinate names can be set")	
	{
		std::set<std::string> names = {"01", "02", "03", "10"};
		Coordinates::set_coordinates_by_names(names);
		REQUIRE(Coordinates::get_coordinate_names() == names);
		
		THEN("a zero vector can be initialized")	
		{
			Coordinates qs = Coordinates::Zero();

			REQUIRE(qs.cols() == names.size());

			for(int column=0 ; column < names.size() ; column++)
				for(int row =0 ; row < DIMENSION ; row++)
				{
					REQUIRE(qs(row, column) == 0);
				}

		}

		// THEN("a non-zero 2d-vector can be initialized")
		// {
		// 	Coordinates qs = Coordinates();
		// 	qs[names[0]] = Coordinate({3.0, 4.0});
		// 	qs[names[1]] = Coordinate({5.0, 6.0});
		// 	qs[names[2]] = Coordinate({7.0, 8.0});
		// 	qs[names[3]] = Coordinate({9.0, 10.0});


		// }

	}
	
}











