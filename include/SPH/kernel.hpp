#pragma once

#include <functional>


#include <cmath>

#include <SPH/coordinates.hpp>


namespace SPH
{

constexpr num_t pi { 3.141592653589793238462643383279502884 };

num_t W_gaussian(Coordinate q, Coordinate p, num_t h);

Coordinate W_gaussian_gradient_q(Coordinate q, Coordinate p, num_t h);

class Kernel
{
public:
	num_t h{1};
	std::function<num_t (Coordinate, Coordinate, num_t)> W {W_gaussian};
	std::function<Coordinate(Coordinate, Coordinate, num_t)> W_gradient_q {W_gaussian_gradient_q};


};

extern Kernel gaussian_kernel;
	
}


