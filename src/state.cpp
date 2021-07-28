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


	

} //namespace SPH