#pragma once

#include "coordinates.hpp"
#include "kernels.hpp"
#include "scalar_field.hpp"


namespace SPH
{

template<typename EOS_t = ColeEOS>
Coordinates get_acceleration(const Coordinates &qs, const Kernels::SmoothingKernel W = Kernels::SmoothingKernel(), const EOS_t &p = ColeEOS(), const num_t g = 9.8)
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
		for(int p_id = q_id + 1; p_id < N; p_id++)
		{
			//accel due to fluid mechanics
			 
			Coordinate accel_q_p = -masses[p_id] * (
								pressure_samples(q_id)/pow(density_samples(q_id),2)
								+pressure_samples(p_id)/pow(density_samples(q_id), 2)
								) * W.gradient_q(qs_matrix.col(q_id), qs_matrix.col(p_id), 1);
			accel.col(q_id) += accel_q_p;
			accel.col(p_id) -= accel_q_p;
			//accel due to gravity
			accel.col(q_id) += -g * Coordinate(0,-1);
				
		}
	}



	return qs_dot_dot;

}

} // namespace SPH