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




	DensityField density_field(qs);

	NumericalScalarArray density_samples{qs.size()};
	NumericalScalarArray pressure_samples{qs.size()};
	const NumericalScalarArray &masses = qs.coordinate_ids.coordinate_masses;

	int q_id{0};
	for(auto&& q : qs)
	{
		num_t density_q = density_field(q);
		density_samples(q_id) = density_q;
		pressure_samples(q_id) = p(density_q);
		q_id++;
	}

	Coordinates accel = Coordinates::Zero(qs.coordinate_ids);

	for(int q_id = 0; q_id < N; q_id++)
	{
		for(int p_id = q_id + 1; p_id < N; p_id++)
		{
			//accel due to fluid mechanics
			 
			Coordinate accel_q_p = -masses[p_id] * (
								pressure_samples(q_id)/pow(density_samples(q_id),2)
								+pressure_samples(p_id)/pow(density_samples(p_id), 2)
								) * W.gradient_q(qs[q_id], qs[p_id], 1);
			accel[q_id] += accel_q_p;
			accel[p_id] -= accel_q_p;
			
				
		}
		//accel due to gravity
		accel[q_id] += -g * Coordinate(0,1);
	}



	return accel;

}

} // namespace SPH