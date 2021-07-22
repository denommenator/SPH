#include <SPH/scalar_field.hpp>
#include <SPH/coordinates.hpp>


namespace SPH
{
ScalarField::ScalarField(Coordinates qs)
:	qs{qs},
	weights{qs.size()}
{}



NumericalScalarArray::ColXpr ScalarField::operator[](std::string name)
{
	int index = qs.coordinate_ids[name];
	return weights.col(index);
}



} //namespace SPH