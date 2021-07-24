#pragma once

#include <SPH/coordinates.hpp>
#include <SPH/kernel.hpp>



namespace SPH
{

class ScalarField
{
public:

	ScalarField(Coordinates qs, SmoothingKernel W = W_gaussian);
	
	NumericalScalarArray::ColXpr operator[](std::string name);

	num_t operator()(Coordinate r);
	
	Coordinates qs;
	NumericalScalarArray weights;
	SmoothingKernel W;

};


} // namespace SPH