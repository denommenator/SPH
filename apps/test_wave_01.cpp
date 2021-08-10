#include "SPH/trajectory_data.hpp"
#include <iostream>


#include <SPH/coordinates.hpp>
#include <SPH/state.hpp>
#include <SPH/collisions.hpp>
#include <SPH/dynamical_system.hpp>
#include <SPH/serializers.hpp>

using namespace SPH;


std::string get_name(int row, int col)
{
	return std::to_string(row) + "_" + std::to_string(col);
}


int main()
{
	//setup parameters for simulation
	const num_t box_width = 20;
	const num_t box_height = 20;

	const num_t fluid_depth = 10;

	const num_t dt = 1./60;
	const num_t time = 10;


	//setup container box
	Coordinate lower_left, upper_right;
	lower_left << -box_width / 2, 0;
	upper_right << box_width / 2, box_height;

	Collisions::Container box = Collisions::BoxContainer(lower_left, upper_right);

	//setup particles
	const int N_rows = fluid_depth;
	const int N_cols = box_width;

	std::vector<std::string> names{};

	for(int row = 0; row < N_rows; row++)
		for(int col = 0; col < N_cols; col++)
		{
			if( (row % 2 == 1) && (col == N_cols-1))
			{
				break;
			}
			names.push_back(get_name(row, col));
		}

  	CoordinateIDManager ids(names);

	State initial_state{ids};

	

	for(int row = 0; row < N_rows; row++)
		for(int col = 0; col < N_cols; col++)
		{
			if(row % 2 == 0)
			{
				initial_state.qs[get_name(row, col)]  << col, row;
			}
			else if (col == N_cols-1)
			{
				break;
			}
			else
			{
				initial_state.qs[get_name(row, col)]  << col + 0.5, row;
			}
			initial_state.qs[get_name(row, col)] += lower_left;

			initial_state.q_dots[get_name(row, col)] << 5, 0;

		}
	



	DynamicalSystem dynamical_system(initial_state, box);

	TrajectoryData td = dynamical_system.run_dynamics(time / dt, dt);

	Serializers::to_csv(td, "test_wave_01.csv");

}
