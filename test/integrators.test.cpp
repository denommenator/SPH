#include <SPH/coordinates.hpp>
#include <SPH/state.hpp>
#include <SPH/integrators.hpp>


#include <catch2/catch.hpp>

#include <string>
#include <vector>

using namespace SPH;

SCENARIO("We can initialize a state")
{

	CoordinateIDManager ids= {"01", "02", "03"};
	Coordinates qs{ids}, q_dots{ids}, q_not{{"01", "02", "03"}};

	qs["01"] << 0,1;
	qs["02"] << 2,3;
	qs["03"] << 4,5;

	q_dots["01"] << 6,7;
	q_dots["02"] << 8,9;
	q_dots["03"] << 10,11;

	q_not["01"] << 0,0; //not the same
	q_not["02"] << 2,3;
	q_not["03"] << 4,5;

	State initial_state{qs, q_dots};

	THEN("We can step the state forward using the integrator euler_next")
	{
		State next_state = Integrators::explicit_euler.next_state(initial_state, .5);
	}

}