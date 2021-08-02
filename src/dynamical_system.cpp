
#include <indicators/block_progress_bar.hpp>
#include <indicators/cursor_control.hpp>

#include "SPH/integrators.hpp"

#include <SPH/dynamical_system.hpp>

namespace SPH
{

DynamicalSystem::DynamicalSystem(const State &initial_state, const Collisions::Container &container)
:initial_state{initial_state}, container{container}, trajectory_data{container}
{
	trajectory_data << initial_state;
}


TrajectoryData DynamicalSystem::run_dynamics(int num_steps, num_t dt)
{
	using namespace indicators;
	show_console_cursor(false);

	 BlockProgressBar bar{
	    option::BarWidth{50},
	    option::Start{"["},
	    option::End{"]"},
	    option::ShowElapsedTime{true},
    	option::ShowRemainingTime{true},
	    option::ForegroundColor{Color::green},
	    option::FontStyles{std::vector<FontStyle>{FontStyle::bold}},
	    option::MaxProgress{num_steps}
	  };


	for(int n=0; n<num_steps; n++)
	{
		step_dynamics(dt);

		bar.set_option(indicators::option::PostfixText{"Dynamics iteration: " 
													+ std::to_string(n) + "/" 
													+ std::to_string(num_steps)}
													);
		bar.tick();

	}

	show_console_cursor(true);
	bar.mark_as_completed();
	return trajectory_data;
}


TrajectoryData DynamicalSystem::step_dynamics(num_t dt)
{
	State &s_current = trajectory_data.current_state();

	State s_next = Integrators::explicit_euler_next(s_current, dt);
	State s_next_resolved = container.collision_resolver(s_next);
	trajectory_data << s_next_resolved;
	return trajectory_data;
}


} //namespace SPH