#include <SPH/pressure_eos.hpp>
#include <SPH/coordinates.hpp>
#include <SPH/integrators.hpp>
#include <SPH/state.hpp>



#include <catch2/catch.hpp>

#include <string>
#include <vector>

using namespace SPH;

SCENARIO("We can initialize a state")
{

	CoordinateIDManager ids= {"01", "02", "03"};
	State initial_state{ids};

	Coordinates	q_not{{"01", "02", "03"}};

	initial_state.qs["01"] << 0,1;
	initial_state.qs["02"] << 2,3;
	initial_state.qs["03"] << 4,5;

	initial_state.q_dots["01"] << 6,7;
	initial_state.q_dots["02"] << 8,9;
	initial_state.q_dots["03"] << 10,11;

	q_not["01"] << 0,0; //not the same
	q_not["02"] << 2,3;
	q_not["03"] << 4,5;


	THEN("We can step the state forward using the integrator euler_next")
	{
		State next_state = Integrators::explicit_euler_next(initial_state, .5);
	}

	// THEN("We can step the state forward using the integrator velocity verlet")
	// {
	// 	State next_state = Integrators::velocity_verlet_next(initial_state, .5);
	// }

}