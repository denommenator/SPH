#include "SPH/collisions.hpp"
#include <SPH/trajectory_data.hpp>


namespace SPH
{


TrajectoryData::TrajectoryData(const Collisions::Container &container)
:container{container}
{}

TrajectoryData TrajectoryData::operator<<(const State &s)
{
	states.push_back(s);
	return (*this);
}


State& TrajectoryData::current_state()
{
	return states.back();
}


} //namespace SPH