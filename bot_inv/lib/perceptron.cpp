#include <cassert>

#include "perceptron.h"
//#include "utils.h"

namespace ra
{

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
Perceptron::Perceptron() : m_Dimension(0), m_LearningRate(0.1)
{
}

Perceptron::~Perceptron()
{
}

// =============================================================================
//	REGULAR METHODS
// =============================================================================
void Perceptron::add(const TVecDouble& inputs, double output)
{
	if(m_Dimension == 0)
		m_Dimension = inputs.size();

	assert(m_Dimension == inputs.size());

	m_DataSet.push_back(inputs);
	m_DataSet.back().insert(m_DataSet.back().begin(), 1.0);	// x0 = 1.0
	m_Outputs.push_back(output);
}

void Perceptron::clear()
{
	m_DataSet.clear();
	m_Outputs.clear();
	m_Weights.clear();
	m_Dimension = 0;
}

double Perceptron::h(const TVecDouble& input) const
{
	TVecDouble x;	// Features vector
	
	// If the input doesn't have x0 add it
	if(input.size() != m_Dimension + 1)
	{
		x = input;
		x.insert(x.begin(), 1.0);
	}
	else
	{
		x = input;
	}

	double summation = 0;

	for(unsigned int i = 0; i < x.size(); ++i)
		summation += m_Weights[i] * x[i];	// Theta_i * X_i

	
	// If we are between the burnt range, assume we are
	// going to be burnt, so let's return 1.0
	if(m_EvaluateInput)
	{
		//std::cout << "Evaluating summation: " << summation << std::endl;
		if(summation >= -K_BURNED_ERROR_RANGE && summation <= K_BURNED_ERROR_RANGE)
		{
			//std::cout << "Between the error range! " << -K_BURNED_ERROR_RANGE << " <= " << summation << " <= " << K_BURNED_ERROR_RANGE << std::endl;
			return 1.0;
		}
	}

        //std::cerr << summation << std::endl;
	return (summation >= 0) ? 1.0 : -1.0;
}



void Perceptron::learn()
{
	const unsigned int K_MAX_ITER = 1000;
	unsigned int errors = 0;
	unsigned int iterations = 0;

	Utils::InitializeVector(m_Weights, m_Dimension + 1, true);

	do
	{
		errors = 0;
		iterations++;
		for(unsigned int i = 0; i < m_DataSet.size(); ++i)
		{
			if(h(m_DataSet[i]) == m_Outputs[i])
				continue;	// If the sample is well classified continue

			errors++;
			// If we are here, the sample is bad classified
			// let's update the weight vector
			for(unsigned int j = 0; j < m_Weights.size(); ++j)
				m_Weights[j] = m_Weights[j] + (m_LearningRate * (m_Outputs[i] * m_DataSet[i][j]));
		}

	}
	while(errors > 0 && iterations < K_MAX_ITER);

	//Utils::PrintVector(m_Weights);
}

// =============================================================================
//	GETTERS & SETTERS
// =============================================================================
const DataSet& Perceptron::getDataSet() const
{
	return m_DataSet;
}

const TVecDouble& Perceptron::getWeights() const
{
	return m_Weights;
}

const TVecDouble& Perceptron::getOutputs() const
{
	return m_Outputs;
}

const size_t Perceptron::getDimension() const
{
	return m_Dimension;
}

const double Perceptron::getLearningRate() const
{
	return m_LearningRate;
}

}
