#include "SPH/collisions.hpp"
#include <SPH/trajectory_data.hpp>


namespace SPH
{


TrajectoryData::TrajectoryData(const Collisions::Container &container)
:container{container}
{}


Coordinates& TrajectoryData::current_qs()
{
	return qs_list.back();
}

Coordinates& TrajectoryData::current_q_dots()
{
	return q_dots_list.back();
}

Coordinates& TrajectoryData::current_q_dot_dots()
{
	return q_dot_dots_list.back();
}

} //namespace SPH