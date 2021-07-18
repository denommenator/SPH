#include <SPH/coordinates.hpp>
#include <Eigen/Dense>


#include <catch2/catch.hpp>

#include <string>
#include <vector>



TEST_CASE( "Catch2 works", "[catch]") 
{
	REQUIRE(1==1);
}


SCENARIO("Eigen objects work as expected")
{
	GIVEN("A 2x1 matrix can be initialized")
	{
		Eigen::Array<num_t, 2, Eigen::Dynamic> qs{2,4};

		THEN("We should be able to assign to it using blocks")
		{
			std::set<std::string> names = {"01", "02", "03", "10"};
			int i=0;

			for(auto name : names)
			{
				Coordinate Vector_i = Coordinate(DIMENSION, 1);

				Vector_i << i, i+1;
				qs.block(0,i/2, 2,1) = Vector_i;
				CAPTURE(name, Vector_i);

				i += 2;
				

				
				


			}

			i = 0;
			for(auto name : names)
			{
				CAPTURE(qs.block(0,i, 2,1));
				REQUIRE(qs(0, i) == 2*i);

				REQUIRE(qs(1,i) == 2*i+1);

				i+=1;
			}
		}
	}
}

SCENARIO("Coordinate names/existence can be set up and initialized correctly", 
	"[coordinates]") 
{

	GIVEN("the coordinate names can be set")	
	{
		std::set<std::string> names = {"01", "02", "03", "10"};
		Coordinates::set_coordinates_by_names(names);
		REQUIRE(Coordinates::get_coordinate_names() == names);
		
		int i=0;
		for(auto name : names)
		{
			REQUIRE(Coordinates::get_coordinate_id(name) == i++);
		}
		
		THEN("a zero vector can be initialized")	
		{
			Coordinates qs = Coordinates::Zero();

			REQUIRE(qs.cols() == names.size());

			for(int column=0 ; column < names.size() ; column++)
				for(int row =0 ; row < DIMENSION ; row++)
				{
					REQUIRE(qs(row, column) == 0);
				}

			for(auto name : names)
				for(int row =0 ; row < DIMENSION ; row++)
				{
					CAPTURE(qs[name]);
					REQUIRE(qs[name](row) == 0);
				}

			for(auto name : names)
			{
				Coordinate V_name = qs[name];
				CHECK(V_name(0) == Approx(0));
				CHECK(V_name(1) == Approx(0));
			}


		}

		AND_THEN("a non-zero 2d-vector can be initialized via (row, col) assignment")
		{
			int i = 0;
			Coordinates qs = Coordinates();
			for(auto name : names)
			{

				(qs[name])(0, Coordinates::get_coordinate_id(name)) = i;
				(qs[name])(1, Coordinates::get_coordinate_id(name)) = i+1;
				CAPTURE(qs[name]);
				i += 2;

			}

			i = 0;
			for(auto name : names)
			{
				CAPTURE(qs[name]);
				REQUIRE((qs[name])(0, Coordinates::get_coordinate_id(name))== Approx(2*i));
				REQUIRE((qs[name])(1, Coordinates::get_coordinate_id(name))== Approx(2*i));


				i+=1;
			}
		}


		// AND_THEN("a non-zero 2d-vector can be initialized via << assignment")
		// {
		// 	int i = 0;
		// 	Coordinates qs;
		// 	for(auto name : names)
		// 	{
		// 		Coordinate Vector_i = Coordinate(DIMENSION, 1);

		// 		qs[name] << i, i+1;
		// 		CAPTURE(qs[name]);
		// 		i += 2;

		// 	}

		// 	i = 0;
		// 	for(auto name : names)
		// 	{
		// 		CAPTURE(qs[name]);
		// 		REQUIRE((qs[name])(0) == Approx(2*i));

		// 		REQUIRE((qs[name])(1) == Approx(2*i+1));

		// 		i+=1;
		// 	}



		// }

		// AND_THEN("a non-zero 2d-vector can be initialized via block assignment")
		// {
		// 	int i = 0;
		// 	Coordinates qs;
		// 	for(auto name : names)
		// 	{
		// 		Coordinate Vector_i = Coordinate(DIMENSION, 1);

		// 		Vector_i << i, i+1;
		// 		i += 2;
				

				
		// 		qs[name] = Vector_i;
		// 		CAPTURE(name, Vector_i, qs[name]);


		// 	}

		// 	i = 0;
		// 	for(auto name : names)
		// 	{
		// 		CAPTURE(qs[name]);
		// 		REQUIRE((qs[name])(0) == i);

		// 		REQUIRE((qs[name])(1) == i+1);

		// 		i+=1;
		// 	}



		// }

	}
	
}











