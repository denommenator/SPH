#include "SPH/kernel.hpp"
#include <SPH/scalar_field.hpp>
#include <SPH/coordinates.hpp>


namespace SPH
{
ScalarField::ScalarField(Coordinates qs, SmoothingKernel W)
:	qs{qs},
	weights{qs.size()},
	W{W}
{}



NumericalScalarArray::ColXpr ScalarField::operator[](std::string name)
{
	int index = qs.coordinate_ids[name];
	return weights.col(index);
}


num_t ScalarField::operator()(Coordinate r)
{
	num_t F_r{0};
	NumericalVectorArray &coord_matrix = qs.coordinate_matrix;
	NumericalScalarArray &masses = qs.coordinate_ids.coordinate_masses;
	NumericalScalarArray &densities = qs.coordinate_ids.coordinate_densities;

	//Eigen will support range-based looping via this interface. Currently only in devel though
	//for (auto col : qs.coordinate_matrix.colwise())
	for(int coord_index=0; coord_index < coord_matrix.cols(); coord_index++)
	{
		NumericalVectorArray::ColXpr q = qs.coordinate_matrix.col(coord_index);
		F_r += weights(coord_index) * masses(coord_index) / densities(coord_index) * W(q, r, 1);
	}

	return F_r;
}	



} //namespace SPH