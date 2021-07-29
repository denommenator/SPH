#include "SPH/scalar_field.hpp"
#include <SPH/coordinates.hpp>
#include <SPH/state.hpp>



namespace SPH
{

//ColeEOS cole_object{};

State::State(Coordinates qs, 
		Coordinates q_dots)
	: qs{qs}, q_dots{q_dots}
	{}

std::ostream& operator<<(std::ostream &strm, const State &s)
{
	strm << "qs: " << s.qs << std::endl;
	strm << "q_dots" << s.qs << std::endl;
	return strm;
}
	

} //namespace SPH