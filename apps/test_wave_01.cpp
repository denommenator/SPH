#include <iostream>


#include <SPH/coordinates.hpp>
#include <SPH/state.hpp>
#include <SPH/collisions.hpp>
#include <SPH/dynamical_system.hpp>

using namespace SPH;


std::string get_name(int row, int col)
{
	return std::to_string(row) + "_" + std::to_string(col);
}


int main()
{
	//setup parameters for simulation
	num_t box_width = 80;
	num_t box_height = 20;

	num_t fluid_depth = 10;

	num_t dt = 1./20;
	num_t time = 1;


	//setup container box
	Coordinate lower_left, upper_right;
	lower_left << -box_width / 2, 0;
	upper_right << box_width / 2, box_height;

	Collisions::Container box = Collisions::BoxContainer(lower_left, upper_right);

	//setup particles
	int N_rows = fluid_depth;
	int N_cols = box_width;

	std::vector<std::string> names{};

	for(int row = 0; row < N_rows; row++)
		for(int col = 0; col < N_cols; col++)
		{
			names.push_back(get_name(row, col));
		}

  	CoordinateIDManager ids(names);

	State initial_state{ids};

	

	for(int row = 0; row < N_rows; row++)
		for(int col = 0; col < N_cols; col++)
		{
			initial_state.qs[get_name(row, col)]  << col, row;
			initial_state.qs[get_name(row, col)] -= lower_left;

			initial_state.q_dots[get_name(row, col)] << 0, 0;

		}
	



	DynamicalSystem dynamical_system(initial_state, box);

	dynamical_system.run_dynamics(time / dt, dt);

}
