#pragma once

#include <SPH/coordinates.hpp>
#include <SPH/kernel.hpp>



namespace SPH
{

using NumericalScalarArray  = Eigen::Array<num_t, 1, Eigen::Dynamic>;

class ScalarField
{
public:

	ScalarField(Coordinates qs);
	
	NumericalScalarArray::ColXpr operator[](std::string name);

	num_t operator()(Coordinate r);
	
	Coordinates qs;
	NumericalScalarArray weights;

};


} // namespace SPH