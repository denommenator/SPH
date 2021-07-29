#include <iostream>


#include "SPH/coordinates.hpp"
#include <SPH/collisions.hpp>


namespace SPH
{
namespace Collisions
{


void ContainerWall::finish_setup()
{
	n_dot_p = inward_normal.dot(point);
	n_norm_squared = inward_normal.squaredNorm();
}

CollisionList_t ContainerWall::detect_collisions(const Coordinates &qs) const
{
	
	const NumericalVectorArray_m &qs_mat = qs.coordinate_matrix.matrix();
	const NumericalScalarArray n_dot_p_array = NumericalScalarArray::Constant(qs.size(), n_dot_p);
	return (  inward_normal.transpose() * qs_mat  ).array() 
								< n_dot_p_array;
}

Coordinate ContainerWall::reflect_velocity(const Coordinate &q_dot) const
{
	num_t q_dot_n = q_dot.matrix().dot(inward_normal);
	return q_dot - 2 * q_dot_n / n_norm_squared * inward_normal.array();
	
}

Container::Container(const std::vector<ContainerWall> &container_walls)
:walls{container_walls}
{
	for(auto& wall : walls)
	{
		wall.finish_setup();
	}
}

State Container::collision_resolver(const State &s) const
{
	State s_resolved(s);
	for(auto&& wall : walls)
	{
		
		CollisionList_t collided = wall.detect_collisions(s_resolved.qs);
		const CoordinateIDManager &coordinate_ids = s_resolved.qs.coordinate_ids;
		for(auto coordinate_name : coordinate_ids.coordinate_names)
		{
			if (collided(coordinate_ids[coordinate_name]))
			{
				s_resolved.q_dots[coordinate_name] = wall.reflect_velocity(s_resolved.q_dots[coordinate_name]);
			}
		}
	}

	return s_resolved;

}

} //namespace Collisions
} //namespace SPH