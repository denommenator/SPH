#include <string>
#include <vector>

#include <catch2/catch.hpp>


#include <SPH/coordinates.hpp>
#include <SPH/collisions.hpp>

using namespace SPH;

SCENARIO("We can construct a collision wall object", "[collisions]")
{
	
	CoordinateIDManager ids = {"inside_wall", 
								"outside_wall_moving_in",
								 "outside_wall_moving_away"	};

	State s{ids};

	s.qs["inside_wall"] << .5,.5;
	s.qs["outside_wall_moving_in"] << .5,-0.1;
	s.qs["outside_wall_moving_away"] << .7,-1;

	s.q_dots["inside_wall"] << 1,1;
	s.q_dots["outside_wall_moving_in"] << 1,0.1;
	s.q_dots["outside_wall_moving_away"] << 1,-0.1;

	//State one_collision(qs, q_dots);

	

	Collisions::ContainerWall wall_lower{};

	wall_lower.inward_normal << 0, 1;
	wall_lower.point << 0,0;
	

	Collisions::Container box({wall_lower});

	

	State s_resolved = box.collision_resolver(s);

	THEN("one collision should be detected")
	{

		Collisions::CollisionList_t collision = box.walls[0].detect_collisions(s);
		CAPTURE(collision);
		REQUIRE_FALSE(collision(s.coordinate_ids["inside_wall"]));
		REQUIRE_FALSE(collision(s.coordinate_ids["outside_wall_moving_in"]));
		REQUIRE(collision(s.coordinate_ids["outside_wall_moving_away"]));

	}

	THEN("the non-collided particles are unchanged")
	{
		REQUIRE(s_resolved.qs["inside_wall"].isApprox(s.qs["inside_wall"]));
		REQUIRE(s_resolved.q_dots["inside_wall"].isApprox(s.q_dots["inside_wall"]));

		REQUIRE(s_resolved.qs["outside_wall_moving_in"].isApprox(s.qs["outside_wall_moving_in"]));
		REQUIRE(s_resolved.q_dots["outside_wall_moving_in"].isApprox(s.q_dots["outside_wall_moving_in"]));

	}
	AND_THEN("the collided particle has its velocity reflected")
	{
		REQUIRE(s_resolved.qs["outside_wall_moving_away"].isApprox(Coordinate(.7, Collisions::epsilon)));

		REQUIRE(s_resolved.q_dots["outside_wall_moving_away"](0) == Approx(s.q_dots["outside_wall_moving_away"](0)));
		REQUIRE(s_resolved.q_dots["outside_wall_moving_away"](1) == Approx(-s.q_dots["outside_wall_moving_away"](1)));
	}

};
