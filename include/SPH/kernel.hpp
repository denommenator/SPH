#pragma once

#include <functional>


#include <cmath>

#include <SPH/coordinates.hpp>


namespace SPH
{
	using SmoothingKernel_t = std::function<num_t (Coordinate, Coordinate, num_t)>;
	using SmoothingKernelGradient_t = std::function<Coordinate(Coordinate, Coordinate, num_t)>;

constexpr num_t pi { 3.141592653589793238462643383279502884 };

num_t W_gaussian_(Coordinate q, Coordinate p, num_t h);

Coordinate W_gaussian_gradient_q_(Coordinate q, Coordinate p, num_t h);

class SmoothingKernel
{
public:
	virtual num_t operator()(Coordinate q, Coordinate p, num_t h);

	SmoothingKernelGradient_t gradient_q{W_gaussian_gradient_q_};



};

extern SmoothingKernel W_gaussian;
	
}


