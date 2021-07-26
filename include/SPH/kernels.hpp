#pragma once

#include <functional>


#include <cmath>

#include <SPH/coordinates.hpp>


namespace SPH
{
namespace Kernels
{
	using SmoothingKernel_t = std::function<num_t (Coordinate, Coordinate, num_t)>;
	using SmoothingKernelGradient_t = std::function<Coordinate(Coordinate, Coordinate, num_t)>;
	using SmoothingKernelVectorized_t = std::function<NumericalScalarArray (Coordinates, Coordinate, num_t)>;
	//using SmoothingKernelGradientVectorized_t = std::function<Coordinate(Coordinate, Coordinate, num_t)>;


constexpr num_t pi { 3.141592653589793238462643383279502884 };



//convenience object so that SmoothingKernel W will be callable W(q,p,h) and have a member W.gradient_q(q,p,h)
class SmoothingKernel
{
public:
	SmoothingKernel(std::tuple<SmoothingKernel_t, SmoothingKernelGradient_t>);

	virtual num_t operator()(const Coordinate &q, const Coordinate &p, const num_t &h);
	

	SmoothingKernel_t W;
	SmoothingKernelGradient_t gradient_q;
	SmoothingKernelVectorized_t W_vectorized;


};

class SmoothingKernelVectorized: public SmoothingKernel
{
public:
	SmoothingKernelVectorized(std::tuple<SmoothingKernel_t, 
										SmoothingKernelGradient_t ,
										SmoothingKernelVectorized_t> );
	//vectorized version 
	NumericalScalarArray operator()(const Coordinates &qs, const Coordinate &r, const num_t &h);
	SmoothingKernelVectorized_t W_vectorized;
};

extern SmoothingKernelVectorized W_gaussian;

} //namespace Kernels
} //namespace SPH


