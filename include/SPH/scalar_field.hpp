#pragma once

#include "coordinates.hpp"
#include "kernels.hpp"



namespace SPH
{
// using ScalarFieldSamples 
// using ScalarFieldArray 

class ScalarField
{
public:

	ScalarField(const Coordinates &qs);
	
	NumericalScalarArray::ColXpr operator[](std::string name);

	num_t operator()(Coordinate r);

	num_t non_vectorized(Coordinate r);
	
	Coordinates qs;
	NumericalScalarArray weights;
	Kernels::SmoothingKernel W{};

};



class DensityField : public ScalarField
{
public:
	DensityField(Coordinates qs);
};



} // namespace SPH