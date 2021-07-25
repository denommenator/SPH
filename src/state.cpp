#include "SPH/scalar_field.hpp"
#include <SPH/coordinates.hpp>
#include <SPH/state.hpp>



namespace SPH
{


Coordinates State::get_acceleration()
{
	

	int N = qs.coordinate_ids.size();



	Coordinates qs_dot_dot = Coordinates(qs.coordinate_ids);
	NumericalVectorArray &accel = qs_dot_dot.coordinate_matrix;
	NumericalVectorArray &qs_matrix = qs.coordinate_matrix;

	DensityField density_field = DensityField(qs, W);

	NumericalScalarArray density_samples{qs.size()};
	NumericalScalarArray pressure_samples{qs.size()};
	NumericalScalarArray &masses = qs.coordinate_ids.coordinate_masses;


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