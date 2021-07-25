#pragma once

#include <SPH/coordinates.hpp>
#include <SPH/kernels.hpp>



namespace SPH
{
// using ScalarFieldSamples 
// using ScalarFieldArray 

class ScalarField
{
public:

	ScalarField(Coordinates qs, Kernels::SmoothingKernel W = Kernels::W_gaussian);
	
	NumericalScalarArray::ColXpr operator[](std::string name);

	num_t operator()(Coordinate r);
	num_t vectorized(Coordinate r);
	
	Coordinates qs;
	NumericalScalarArray weights;
	Kernels::SmoothingKernel W;

};


class DensityField : public ScalarField
{
public:
	DensityField(Coordinates qs, Kernels::SmoothingKernel W = Kernels::W_gaussian);
};


class PressureField : public ScalarField
{
public:
	PressureField(Coordinates qs, Kernels::SmoothingKernel W = Kernels::W_gaussian);
};

} // namespace SPH