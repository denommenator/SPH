#pragma once

#include <cmath>

#include "pressure_eos.hpp"
#include "scalar_field.hpp"
#include "coordinates.hpp"
#include "kernels.hpp"

namespace SPH
{

//extern ColeEOS cole_object;

class State
{
public:

	State(Coordinates qs, 
		Coordinates q_dots);

	State(CoordinateIDManager coordinate_ids);

	template<typename EOS_t = ColeEOS>
	Coordinates get_acceleration(const EOS_t &p = ColeEOS()) const;

	//template<typename EOS_t = ColeEOS, typename NextStateFunction_t>
	//State next_state(num_t dt, NextStateFunction_t next_state_function, EOS_t p = ColeEOS());
	

	CoordinateIDManager coordinate_ids;
	Coordinates qs;
	Coordinates q_dots;
	Kernels::SmoothingKernel W{};



};

std::ostream& operator<<(std::ostream &strm, const State &s);




template<typename EOS_t>
Coordinates State::get_acceleration(const EOS_t &p) const
{
	

	int N = qs.coordinate_ids.size();



	Coordinates qs_dot_dot = Coordinates(qs.coordinate_ids);
	NumericalVectorArray &accel = qs_dot_dot.coordinate_matrix;
	const NumericalVectorArray &qs_matrix = qs.coordinate_matrix;

	DensityField density_field(qs);

	NumericalScalarArray density_samples{qs.size()};
	NumericalScalarArray pressure_samples{qs.size()};
	const NumericalScalarArray &masses = qs.coordinate_ids.coordinate_masses;


	for(int q_id = 0; q_id < N; q_id++)
	{
		num_t density_q = density_field(qs.coordinate_matrix.col(q_id));
		density_samples(q_id) = density_q;
		pressure_samples(q_id) = p(density_q);
	}

	accel = Coordinates::Zero(qs.coordinate_ids).coordinate_matrix;

	for(int q_id = 0; q_id < N; q_id++)
	{
		for(int p_id = 0; p_id < N; p_id++)
		{
			accel.col(q_id) += 
							-masses[p_id] * (
								pressure_samples(q_id)/pow(density_samples(q_id),2)
								+pressure_samples(p_id)/pow(density_samples(q_id), 2)
								) * W.gradient_q(qs_matrix.col(q_id), qs_matrix.col(p_id), 1);
				
		}
	}

	return qs_dot_dot;

}


} //namespace SPH