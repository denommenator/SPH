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

	virtual num_t operator()(Coordinate r);
	
	Coordinates qs;
	NumericalScalarArray weights;
	Kernels::SmoothingKernel W;

};

class ScalarFieldVectorized: public ScalarField
{
public:
	ScalarFieldVectorized(Coordinates qs, Kernels::SmoothingKernelVectorized W_vectorized = Kernels::W_gaussian);
	Kernels::SmoothingKernelVectorized W_vectorized;

	num_t operator()(Coordinate r) override;
};


class DensityField : public ScalarField
{
public:
	DensityField(Coordinates qs, Kernels::SmoothingKernel W = Kernels::W_gaussian);
};

class DensityFieldVectorized : public ScalarFieldVectorized
{
public:
	DensityFieldVectorized(Coordinates qs, Kernels::SmoothingKernelVectorized W = Kernels::W_gaussian);
};

class PressureField : public ScalarField
{
public:
	PressureField(Coordinates qs, Kernels::SmoothingKernel W = Kernels::W_gaussian);
};

} // namespace SPH