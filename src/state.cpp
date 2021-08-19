#include <SPH/coordinates.hpp>
#include <SPH/state.hpp>



namespace SPH
{


State::State(Coordinates qs, 
		Coordinates q_dots)
	: qs{qs}, q_dots{q_dots}, coordinate_ids{qs.coordinate_ids}
	{}

State::State(CoordinateIDManager coordinate_ids)
	: qs{coordinate_ids}, q_dots{coordinate_ids}, coordinate_ids{coordinate_ids}
	{}


std::ostream& operator<<(std::ostream &strm, const State &s)
{
	strm << "qs: " << s.qs << std::endl;
	strm << "q_dots" << s.q_dots << std::endl;
	return strm;
}
	

} //namespace SPH