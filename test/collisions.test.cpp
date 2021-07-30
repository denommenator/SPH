#include <string>
#include <vector>

#include <catch2/catch.hpp>


#include <SPH/coordinates.hpp>
#include <SPH/collisions.hpp>
#include <SPH/state.hpp>

using namespace SPH;

SCENARIO("We can construct a collision wall object", "[collisions]")
{
	
	CoordinateIDManager ids = {"inside_wall", 
								"outside_wall_moving_in",
								 "outside_wall_moving_away"	};

	Coordinates qs(ids), q_dots(ids);
	qs["inside_wall"] << .5,.5;
	qs["outside_wall_moving_in"] << .5,-0.1;
	qs["outside_wall_moving_away"] << .7,-0.2;

	q_dots["inside_wall"] << 1,1;
	q_dots["outside_wall_moving_in"] << 1,0.1;
	q_dots["outside_wall_moving_away"] << 1,-0.1;

	State one_collision(qs, q_dots);

	
	//normal vector, and point it goes through

	Collisions::ContainerWall wall_lower{};

	wall_lower.inward_normal << 0, 1;
	wall_lower.point << 0,0;
	

	// NumericalVector normal_vector_upper = {0,-1};
	// Coordinate point_upper = {0,1};
	// Collisions::ContainerWall wall_upper(normal_vector_upper, point_upper);

	// NumericalVector normal_vector_left = {1,0};
	// Coordinate point_left = {0,0};
	// Collisions::ContainerWall wall_left(normal_vector_left, point_left);

	// NumericalVector normal_vector_right = {-1,0};
	// Coordinate point_right = {1,0};
	// Collisions::ContainerWall wall_right(normal_vector_right, point_right);


	Collisions::Container box({wall_lower});
								//wall_upper, 
								//wall_left, 
								//wall_right});

	State one_collision_resolved = box.collision_resolver(one_collision);

	THEN("one collision should be detected")
	{

		Collisions::CollisionList_t collision = box.walls[0].detect_collisions(one_collision);
		CAPTURE(collision);
		REQUIRE_FALSE(collision(qs.coordinate_ids["inside_wall"]));
		REQUIRE_FALSE(collision(qs.coordinate_ids["outside_wall_moving_in"]));
		REQUIRE(collision(qs.coordinate_ids["outside_wall_moving_away"]));

	}

	THEN("the non-collided particles are unchanged")
	{
		REQUIRE(one_collision_resolved.qs["inside_wall"].isApprox(one_collision_resolved.qs["inside_wall"]));
		REQUIRE(one_collision_resolved.q_dots["inside_wall"].isApprox(one_collision_resolved.q_dots["inside_wall"]));

		REQUIRE(one_collision_resolved.qs["outside_wall_moving_in"].isApprox(one_collision_resolved.qs["outside_wall_moving_in"]));
		REQUIRE(one_collision_resolved.q_dots["outside_wall_moving_in"].isApprox(one_collision_resolved.q_dots["outside_wall_moving_in"]));

	}
	AND_THEN("the collided particle has its velocity reflected")
	{
		REQUIRE(one_collision_resolved.qs["outside_wall_moving_away"].isApprox(one_collision_resolved.qs["outside_wall_moving_away"]));

		REQUIRE(one_collision_resolved.q_dots["outside_wall_moving_away"](0) == Approx(one_collision.q_dots["outside_wall_moving_away"](0)));
		REQUIRE(one_collision_resolved.q_dots["outside_wall_moving_away"](1) == Approx(-one_collision.q_dots["outside_wall_moving_away"](1)));
	}

};
