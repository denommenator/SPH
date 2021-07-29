#include <string>
#include <vector>

#include <catch2/catch.hpp>


#include <SPH/coordinates.hpp>
#include <SPH/collisions.hpp>
#include <SPH/state.hpp>

using namespace SPH;

SCENARIO("We can construct a collision wall object", "[collisions]")
{
	
	CoordinateIDManager ids = {"non-collision", "collision"};
	//std::set<std::string> names = {"01", "02"};
	Coordinates qs(ids), q_dots(ids);
	qs["non-collision"] << .5,.5;
	qs["collision"] << .5,-0.1;

	q_dots["non-collision"] << 1,1;
	q_dots["collision"] << 1,-0.1;

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

		Collisions::CollisionList_t collision = box.walls[0].detect_collisions(one_collision.qs);
		CAPTURE(collision);
		REQUIRE_FALSE(collision(qs.coordinate_ids["non-collision"]));
		REQUIRE(collision(qs.coordinate_ids["collision"]));

	}

	THEN("the non-collided particle is unchanged")
	{
		REQUIRE(one_collision_resolved.qs["non-collision"].isApprox(one_collision_resolved.qs["non-collision"]));
		REQUIRE(one_collision_resolved.q_dots["non-collision"].isApprox(one_collision_resolved.q_dots["non-collision"]));
	}
	AND_THEN("the collided particle has its velocity reflected")
	{
		REQUIRE(one_collision_resolved.qs["collision"].isApprox(one_collision_resolved.qs["collision"]));

		REQUIRE(one_collision_resolved.q_dots["collision"](0) == Approx(one_collision.q_dots["collision"](0)));
		REQUIRE(one_collision_resolved.q_dots["collision"](1) == Approx(-one_collision.q_dots["collision"](1)));
	}

};
