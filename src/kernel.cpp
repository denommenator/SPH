#include <SPH/kernel.hpp>

namespace SPH
{

SmoothingKernel W_gaussian = SmoothingKernel(W_gaussian_, W_gaussian_gradient_q_);

num_t W_gaussian_(Coordinate q, Coordinate p, num_t h)
{
	return  exp(-(q-p).matrix().squaredNorm() / (h*h)) / (h*h * pi); 
}

Coordinate W_gaussian_gradient_q_(Coordinate q, Coordinate p, num_t h)
{
	return  (-2) / (h*h) * W_gaussian(q,p,h) * (q-p);
}


num_t SmoothingKernel::operator()(const Coordinate &q, const Coordinate &p, const num_t &h)
{
	return W(q, p, h);
}


}