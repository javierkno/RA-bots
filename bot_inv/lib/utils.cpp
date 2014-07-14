#include <iomanip>
#include <cstdlib>
#include <ctime>

#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>

#include "utils.h"

// =============================================================================
//	STATIC METHODS
// =============================================================================
void Utils::GenerateSeed()
{
	srand(time(0));
}

double Utils::RandomDouble()
{
	return (double) rand() / (double) RAND_MAX;
}

void Utils::InitializeVector(TVecDouble& vec, size_t size, bool random)
{
	vec.clear();

	for(unsigned int i = 0; i < size; ++i)
		if(!random)
			vec.push_back(0);
		else
			vec.push_back(Utils::RandomDouble());
}

void Utils::ClearVector(TVecDouble& vec, bool random)
{
	for(unsigned int i = 0; i < vec.size(); ++i)
		if(!random)
			vec[i] = 0;
		else
			vec[i] = Utils::RandomDouble();
}

void Utils::PrintVector(const TVecDouble& vec, const std::string& label)
{
	std::string prefix;

	if(label == "")
		prefix = "[ ";
	else
		prefix = label + ": [ ";

	Utils::PrintVector(vec, prefix, "]", " ", true);
}

void Utils::PrintVector(const TVecDouble& vec, const std::string& prefix, const std::string& suffix,
	const std::string& separator, const bool lineBreak)
{
	std::cout << prefix << std::fixed << std::setprecision(2);

	for(unsigned int i = 0; i < vec.size(); ++i)
	{
		std::cout << vec[i];

		if(i < vec.size() - 1)
			std::cout << separator;
	}

	std::cout << suffix;
	if(lineBreak)
		std::cout << std::endl;
}


std::vector<std::string> Utils::split(std::string s) {
    std::istringstream iss(s);
    std::vector<std::string> tokens;
    std::copy(std::istream_iterator<std::string>(iss),
              std::istream_iterator<std::string>(),
              std::back_inserter<std::vector<std::string> > (tokens));
    
    return tokens;
}