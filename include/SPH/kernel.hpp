#pragma once

#include <functional>

#define _USE_MATH_DEFINES
#include <cmath>

#include <SPH/coordinates.hpp>




num_t pi{M_PI};

num_t W_gaussian(Coordinate q, Coordinate p, num_t h)
{
	return  exp(-(q-p).matrix().squaredNorm() / (h*h)) / (h*h * pi); 
}

Coordinate W_gaussian_gradient_q(Coordinate q, Coordinate p, num_t h)
{
	return  (-2) / (h*h) * W_gaussian(q,p,h) * (q-p);
}

class Kernel
{
public:
	num_t h{1};
	std::function<num_t (Coordinate, Coordinate, num_t)> W {W_gaussian};
	std::function<Coordinate(Coordinate, Coordinate, num_t)> W_gradient_q {W_gaussian_gradient_q};


};

Kernel gaussian_kernel{};
	



