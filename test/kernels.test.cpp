#include <SPH/coordinates.hpp>
#include <SPH/kernels.hpp>


#include <catch2/catch.hpp>

#include <string>
#include <vector>

using namespace SPH;
using namespace SPH::Kernels;

SCENARIO("Evaluate the two gaussian smoothing kernel functions")
{
	SmoothingKernel &W{W_gaussian};

	CoordinateIDManager ids= {"01", "02", "03"};
		Coordinates qs{ids}, q_dots{ids}, q_not{{"01", "02", "03"}};

		qs["01"] << 0,1;
		qs["02"] << 2,3;
		qs["03"] << 4,5;

		q_dots["01"] << 6,7;
		q_dots["02"] << 8,9;
		q_dots["03"] << 10,11;

		q_not["01"] << 0,0; //not the same
		q_not["02"] << 2,3;
		q_not["03"] << 4,5;


		REQUIRE_FALSE(W(qs["01"], qs["02"], 1)==0);

		REQUIRE_FALSE(W.gradient_q(qs["01"],qs["02"], 1).isApprox(Coordinate::Zero()));
}