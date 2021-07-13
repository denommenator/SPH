#pragma once

#include <Eigen/Dense>

#include <string>
#include <vector>

const int DIMENSION = 3;
using num_t = double;
using NumericalVector = Eigen::Array<num_t, DIMENSION, 1>;

class Coordinates : public NumericalVector {
public:
	using NumericalVector::NumericalVector;

	static void push_coordinate(std::string name);


private:
	static std::vector<std::string> coordinate_names;
};

