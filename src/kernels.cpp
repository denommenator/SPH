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
	return  (-2) / (h*h) * W_gaussian_(q,p,h) * (q-p);
}

NumericalScalarArray W_gaussian_vectorized_(Coordinates qs, Coordinate r, num_t h)
{
	NumericalVectorArray &qs_mat{qs.coordinate_matrix};
	//return  exp(-(q-p).matrix().squaredNorm() / (h*h)) / (h*h * pi); 

	return exp((-(qs_mat.colwise() - r).matrix().colwise().squaredNorm()/(h*h)).array()) / (h*h * pi);

	//return (-(qs_mat.matrix().colwise()-r).matrix().colwise().squaredNorm()/ (h*h) ).exp() / (h*h);
}

SmoothingKernelVectorized W_gaussian = SmoothingKernelVectorized({W_gaussian_, W_gaussian_gradient_q_, W_gaussian_vectorized_});



SmoothingKernel::SmoothingKernel(std::tuple<SmoothingKernel_t, SmoothingKernelGradient_t> Ws)
:W{std::get<0>(Ws)}, gradient_q{std::get<1>(Ws)}
{}

SmoothingKernelVectorized::SmoothingKernelVectorized(std::tuple<SmoothingKernel_t, 
																SmoothingKernelGradient_t,
																SmoothingKernelVectorized_t> Ws)
:SmoothingKernel{std::tie(std::get<0>(Ws), std::get<1>(Ws))}, W_vectorized{std::get<2>(Ws)}
{}

num_t SmoothingKernel::operator()(const Coordinate &q, const Coordinate &p, const num_t &h)
{
	return W(q, p, h);
}


NumericalScalarArray SmoothingKernelVectorized::operator()(const Coordinates &qs, const Coordinate &r, const num_t &h)
{
	

	return W_vectorized(qs, r, h);
}

} //namespace Kernels
} //namespace SPH