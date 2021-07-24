#include <SPH/coordinates.hpp>
#include <SPH/state.hpp>



namespace SPH
{


Coordinates State::get_acceleration()
{
	int N = qs.coordinate_ids.size();

	return qs;
}

} //namespace SPH