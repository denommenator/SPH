#pragma once

#include <SPH/coordinates.hpp>
#include <SPH/kernels.hpp>



namespace SPH
{

class ScalarField
{
public:

	ScalarField(Coordinates qs, Kernels::SmoothingKernel W = Kernels::W_gaussian);
	
	NumericalScalarArray::ColXpr operator[](std::string name);

	num_t operator()(Coordinate r);
	
	Coordinates qs;
	NumericalScalarArray weights;
	Kernels::SmoothingKernel W;

};


} // namespace SPH