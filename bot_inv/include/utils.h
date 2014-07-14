#ifndef __UTILS_H__
#define __UTILS_H__

#include <iostream>
#include <vector>

typedef std::vector<double> TVecDouble;

class Utils
{
public:
	static void GenerateSeed();
	static double RandomDouble();

	static void InitializeVector(TVecDouble& vec, size_t size, bool random = false);
	static void ClearVector(TVecDouble& vec, bool random = false);
	static void PrintVector(const TVecDouble& vec, const std::string& label = "");
	static void PrintVector(const TVecDouble& vec, const std::string& prefix, const std::string& suffix,
		const std::string& separator, const bool lineBreak);
        static std::vector<std::string> split(std::string);
};

#endif