#pragma once

#include <vector>

#include "coordinates.hpp"
#include "state.hpp"

namespace SPH
{
namespace Collisions
{
using Coordinate_m = Eigen::Matrix<num_t, DIMENSION, 1>;
using NumericalVector_m = Eigen::Matrix<num_t, DIMENSION, 1>;
using NumericalVectorArray_m = Eigen::Matrix<num_t, DIMENSION, Eigen::Dynamic>;
using NumericalScalarArray_m  = Eigen::Matrix<num_t, 1, Eigen::Dynamic>; 

using CollisionList_t = Eigen::Array<bool, 1, Eigen::Dynamic>;


class ContainerWall
{
public:

	CollisionList_t detect_collisions(const Coordinates &qs) const;
	
	Coordinate reflect_velocity(const Coordinate &q_dot) const;

	NumericalVector_m inward_normal{};
	Coordinate_m point{};

	void finish_setup();
private:
	num_t n_dot_p;
	num_t n_norm_squared;
};



class Container 
{
public:
	Container(const std::vector<ContainerWall> &walls);

	State collision_resolver(const State &s) const;

	std::vector<ContainerWall> walls;
};

} //namespace Collisions
} //namespace SPH