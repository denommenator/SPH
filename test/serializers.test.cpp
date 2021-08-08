#include <catch2/catch.hpp>

#include <SPH/coordinates.hpp>
#include <SPH/collisions.hpp>
#include <SPH/dynamical_system.hpp>
#include <SPH/serializers.hpp>
#include <SPH/state.hpp>

using namespace SPH;

SCENARIO("Write a trajectory data item to disk", "[serializers]")
{
	CoordinateIDManager ids= {"01", "02", "03"};

	State s{ids};

	s.qs["01"] << 1.5, .5;
	s.qs["02"] << .2, .2;
	s.qs["03"] << .4, .5;

	s.q_dots["01"] << .5, .5;
	s.q_dots["02"] << .5, .5;
	s.q_dots["03"] << .5, .5;


	Coordinate lower_left, upper_right;
	lower_left << 0,0;
	upper_right << 10,10;

	Collisions::Container box = Collisions::BoxContainer(lower_left, upper_right);

	DynamicalSystem dynamical_system(s, box);

	TrajectoryData td = dynamical_system.run_dynamics(100, .1);

	Serializers::to_csv(td, "first_test.csv");

}