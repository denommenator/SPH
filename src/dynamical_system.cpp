#include <tuple>



#include <indicators/block_progress_bar.hpp>
#include <indicators/cursor_control.hpp>

#include <SPH/integrators.hpp>
#include <SPH/vector_field.hpp>
#include <SPH/dynamical_system.hpp>

namespace SPH
{

DynamicalSystem::DynamicalSystem(const State &initial_state, const Collisions::Container &container)
:initial_qs{initial_state.qs}, initial_q_dots{initial_state.q_dots}, container{container}, trajectory_data{container}
{
	trajectory_data.qs_list.push_back(initial_qs);
	trajectory_data.q_dots_list.push_back(initial_q_dots);
	trajectory_data.q_dot_dots_list.push_back(get_acceleration(initial_qs));
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
		step_dynamics_midpoint_rule(dt);

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


// TrajectoryData DynamicalSystem::step_dynamics_velocity_verlet(num_t dt)
// {
// 	Coordinates &qs_current = trajectory_data.qs_list.back();
// 	Coordinates &q_dots_current = trajectory_data.q_dots_list.back();
// 	Coordinates &q_dot_dots_current = trajectory_data.q_dot_dots_list.back();

// 	State s_current{qs_current, q_dots_current};

// 	State s_next{s_current.coordinate_ids};
// 	Coordinates q_dot_dots_next{s_current.coordinate_ids};
// 	std::tie(s_next, q_dot_dots_next) = Integrators::velocity_verlet_next(s_current, q_dot_dots_current, dt);


// 	State s_next_resolved = container.resolve_collisions(s_next);
	
// 	trajectory_data.qs_list.push_back(s_next_resolved.qs);
// 	trajectory_data.q_dots_list.push_back(s_next_resolved.q_dots);

// 	//note: this is not exactly what we want, as we should resolved the positions first before calculating q_dot_dots_next.
// 	trajectory_data.q_dot_dots_list.push_back(q_dot_dots_next);

// 	return trajectory_data;
// }


TrajectoryData DynamicalSystem::step_dynamics_euler(num_t dt)
{
	Coordinates &qs_current = trajectory_data.qs_list.back();
	Coordinates &q_dots_current = trajectory_data.q_dots_list.back();
	Coordinates &q_dot_dots_current = trajectory_data.q_dot_dots_list.back();

	const State s_current{qs_current, q_dots_current};

	State s_next = Integrators::explicit_euler_next(s_current, q_dot_dots_current, dt);
	

	State s_next_resolved = container.resolve_collisions(s_next);
	
	trajectory_data.qs_list.push_back(s_next_resolved.qs);
	trajectory_data.q_dots_list.push_back(s_next_resolved.q_dots);
	trajectory_data.q_dot_dots_list.push_back(get_acceleration(s_next_resolved.qs));

	return trajectory_data;
}

TrajectoryData DynamicalSystem::step_dynamics_midpoint_rule(num_t dt)
{
	Coordinates &qs_current = trajectory_data.qs_list.back();
	Coordinates &q_dots_current = trajectory_data.q_dots_list.back();
	Coordinates &q_dot_dots_current = trajectory_data.q_dot_dots_list.back();

	State s_current{qs_current, q_dots_current};

	State s_next = Integrators::midpoint_rule_next(s_current, q_dot_dots_current, dt);
	

	State s_next_resolved = container.resolve_collisions(s_next);
	
	trajectory_data.qs_list.push_back(s_next_resolved.qs);
	trajectory_data.q_dots_list.push_back(s_next_resolved.q_dots);
	trajectory_data.q_dot_dots_list.push_back(get_acceleration(s_next_resolved.qs));

	return trajectory_data;
}

} //namespace SPH