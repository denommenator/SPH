
#include <catch2/catch.hpp>

#include <SPH/coordinates.hpp>
#include <SPH/collisions.hpp>
#include <SPH/dynamical_system.hpp>


using namespace SPH;

SCENARIO("Initialize a dynamical system", "[dynamicalsystem]")
{
	CoordinateIDManager ids= {"01", "02", "03"};

	State initial_state{ids};

	initial_state.qs["01"] << 1.5, .5;
	initial_state.qs["02"] << .2, .2;
	initial_state.qs["03"] << .4, .5;

	initial_state.q_dots["01"] << .5, .5;
	initial_state.q_dots["02"] << .5, .5;
	initial_state.q_dots["03"] << .5, .5;


	Coordinate lower_left, upper_right;
	lower_left << 0,0;
	upper_right << 10,10;

	Collisions::Container box = Collisions::BoxContainer(lower_left, upper_right);

	DynamicalSystem dynamical_system(initial_state, box);

	dynamical_system.run_dynamics(100, .1);

	CAPTURE(dynamical_system.trajectory_data.qs_list.back());
	CAPTURE(dynamical_system.trajectory_data.q_dots_list.back());
	CAPTURE(dynamical_system.trajectory_data.q_dot_dots_list.back());
	
}