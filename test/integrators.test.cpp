#include "SPH/vector_field.hpp"
#include <SPH/pressure_eos.hpp>
#include <SPH/coordinates.hpp>
#include <SPH/integrators.hpp>



#include <catch2/catch.hpp>

#include <string>
#include <vector>

using namespace SPH;

SCENARIO("We can initialize a state", "[integrators]")
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
		Coordinates q_dot_dots{get_acceleration(initial_state.qs)};
		CAPTURE(q_dot_dots);
		State next_state = Integrators::explicit_euler_next(initial_state,q_dot_dots, 0.5);


		//check if q_dots is updated by the accel
		auto q_dot_dot_it = q_dot_dots.begin();
		for(auto init_q_it = initial_state.qs.begin(),
			next_q_it = next_state.qs.begin(),
			init_q_dot_it = initial_state.q_dots.begin(), 
			next_q_dot_it = next_state.q_dots.begin();
			
			init_q_dot_it != initial_state.q_dots.end();
			
			init_q_it++,
			next_q_it++,
			init_q_dot_it++, 
			next_q_dot_it++, 
			q_dot_dot_it++)
		{
			auto& init_q = *(init_q_it), 
				  next_q = *(next_q_it),
				  init_q_dot = *(init_q_dot_it), 
				  next_q_dot = *(next_q_dot_it);
			auto& q_dot_dot = *(q_dot_dot_it);

			REQUIRE(next_q.isApprox(init_q + .5 * init_q_dot));
			REQUIRE(next_q_dot.isApprox(init_q_dot + .5 * q_dot_dot));
		}
	}

	// THEN("We can step the state forward using the integrator velocity verlet")
	// {

	// 	State next_state{ids};
	// 	Coordinates q_dot_dots_next{ids};
	// 	std::tie(next_state, q_dot_dots_next) = Integrators::velocity_verlet_next(initial_state, get_acceleration(initial_state.qs), .5);
		
	// }

}