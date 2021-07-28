#pragma once

#include <functional>


#include <cmath>

#include <SPH/coordinates.hpp>


namespace SPH
{
namespace Kernels
{

constexpr num_t pi { 3.141592653589793238462643383279502884 };


Coordinate W_gaussian_gradient_q(Coordinate q, Coordinate p, num_t h);

//convenience object so that SmoothingKernel W will be callable W(q,p,h) and have a member W.gradient_q(q,p,h)
class SmoothingKernel
{
public:
	//SmoothingKernel();

	num_t operator()(const Coordinate &q, const Coordinate &r, const num_t &h);
	NumericalScalarArray operator()(const Coordinates &qs, const Coordinate &r, const num_t &h);
	
	//gradient_q is a member of SmoothingKernel, and is a reference to the function W_gaussian_gradient_q
	decltype(W_gaussian_gradient_q)& gradient_q{W_gaussian_gradient_q};

};

} //namespace Kernels
} //namespace SPH


