#ifndef __PERCEPTRON_H__
#define __PERCEPTRON_H__

#include <vector>
#include <cstddef>
#include <iostream>
#include "utils.h"

typedef std::vector<double> 	TVecDouble;
typedef std::vector<TVecDouble> DataSet;

namespace ra
{

const double K_BURNED_ERROR_RANGE = 2.5;

class Perceptron
{
private:
	DataSet	   m_DataSet;
	TVecDouble m_Weights;
	TVecDouble m_Outputs;
	size_t     m_Dimension;
	double 	   m_LearningRate;

public:
	bool m_EvaluateInput;

	Perceptron();
	Perceptron(const Perceptron& toCopy);
	Perceptron& operator=(const Perceptron& toCopy);
	~Perceptron();

	double h(const TVecDouble& input) const;
	void learn();

	void add(const TVecDouble& inputs, double output);
	void clear();

	const DataSet&    getDataSet() const;
	const TVecDouble& getWeights() const;
	const TVecDouble& getOutputs() const;
	const size_t	  getDimension() const;
	const double 	  getLearningRate() const;
};
}

#endif
