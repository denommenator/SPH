#include <algorithm>

#include <SPH/coordinates.hpp>
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

bool outside_wall_(const Coordinate &q, const NumericalVector_m inward_normal, num_t n_dot_p) 
{
	return inward_normal.dot(q.matrix()) < n_dot_p;
}

CollisionList_t ContainerWall::outside_wall(const Coordinates &qs) const
{
	CollisionList_t results{};
	results.resize(qs.size());
	std::transform(qs.begin(), qs.end(), results.begin(), [this](const Coordinate &q) {return outside_wall_(q, this->inward_normal, this->n_dot_p);});
	return results;
}

bool moving_away_(const Coordinate &q_dot, const NumericalVector_m inward_normal)
{
	return inward_normal.dot(q_dot.matrix()) < 0;
}

CollisionList_t ContainerWall::moving_away(const Coordinates &q_dots) const
{
	CollisionList_t results{};
	results.resize(q_dots.size());
	std::transform(q_dots.begin(), q_dots.end(), results.begin(), [this](const Coordinate &q_dot) {return moving_away_(q_dot, this->inward_normal);});
	return results;
}

Coordinate ContainerWall::reflect_velocity(const Coordinate &q_dot) const
{
	num_t q_dot_n = q_dot.matrix().dot(inward_normal);
	return q_dot - 2 * q_dot_n / n_norm_squared * inward_normal.array();
	//return Coordinate::Zero();
}

Coordinate ContainerWall::reset_position(const Coordinate &q) const
{
	num_t q_dot_n = (q.matrix() - point).dot(inward_normal);
	return q - (1) * q_dot_n / n_norm_squared * inward_normal.array();
	
}

Container::Container(const std::vector<ContainerWall> &container_walls)
:walls{container_walls}
{
	for(auto& wall : walls)
	{
		wall.finish_setup();
	}
}

State Container::resolve_collisions(const State &s) const
{
	State s_resolved{s};

	const CoordinateIDManager &coordinate_ids = s.coordinate_ids;

	for(auto&& wall : walls)
	{
		
		CollisionList_t outside_wall_list = wall.outside_wall(s.qs);
		CollisionList_t moving_away_list = wall.moving_away(s.q_dots);
		
		for(int id=0; id<coordinate_ids.size(); id++)
		{
			if (outside_wall_list[id])
			{
				s_resolved.qs[id] = wall.reset_position(s_resolved.qs[id]);

				if(moving_away_list[id])
				{
					s_resolved.q_dots[id] = wall.reflect_velocity(s_resolved.q_dots[id]);
				}
			}
		}
	}

	return s_resolved;

}

Container BoxContainer(const Coordinate lower_left, const Coordinate upper_right)
{
	Collisions::ContainerWall wall_lower{},
							  wall_upper{},
							  wall_left{},
							  wall_right{};

	wall_lower.inward_normal << 0, 1;
	wall_lower.point = lower_left;

	wall_upper.inward_normal << 0, -1;
	wall_upper.point = upper_right;

	wall_left.inward_normal << 1, 0;
	wall_left.point = lower_left;

	wall_right.inward_normal << -1, 0;
	wall_right.point = upper_right;

	return Container({wall_lower, wall_upper, wall_left, wall_right});
}

} //namespace Collisions
} //namespace SPH