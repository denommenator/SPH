#include "SPH/coordinates.hpp"
#include <SPH/kernels.hpp>

namespace SPH
{
namespace Kernels
{


num_t W_gaussian_(Coordinate q, Coordinate p, num_t h)
{
	return  exp(-(q-p).matrix().squaredNorm() / (h*h)) / (h*h * pi); 
}

Coordinate W_gaussian_gradient_q_(Coordinate q, Coordinate p, num_t h)
{
	return  (-2) / (h*h) * W_gaussian(q,p,h) * (q-p);
}

NumericalScalarArray W_gaussian_vectorized_(Coordinates qs, Coordinate r, num_t h)
{
	NumericalVectorArray &qs_mat{qs.coordinate_matrix};
	//return  exp(-(q-p).matrix().squaredNorm() / (h*h)) / (h*h * pi); 

	return exp((-(qs_mat.colwise() - r).matrix().colwise().squaredNorm()/(h*h)).array()) / (h*h * pi);

	//return (-(qs_mat.matrix().colwise()-r).matrix().colwise().squaredNorm()/ (h*h) ).exp() / (h*h);
}

SmoothingKernel W_gaussian = SmoothingKernel(W_gaussian_, W_gaussian_gradient_q_, W_gaussian_vectorized_);


// NumericalScalarArray W_gaussian_gradient_q_vectorized(Coordinate q, Coordinate r, num_t h)
// {
// 	return  (-2) / (h*h) * W_gaussian(q,p,h) * (q-p);
// }

num_t SmoothingKernel::operator()(const Coordinate &q, const Coordinate &p, const num_t &h)
{
	return W(q, p, h);
}


NumericalScalarArray SmoothingKernel::operator()(const Coordinates &qs, const Coordinate &r, const num_t &h)
{
	

	return W_vectorized(qs, r, h);
}

} //namespace Kernels
} //namespace SPH