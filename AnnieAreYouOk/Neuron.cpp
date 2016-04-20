#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <fstream>
#include <sstream>
#include "Neuron.h"
#include "Net.h"
#include "TrainingData.h"
using namespace std;

double Neuron::eta = 0.15;    // that funny n letter. Overall learning rate
double Neuron::alpha = 0.5;   // momentum, multiplier of last deltaWeight
void Neuron::updateInputWeights(Layer &prevLayer)
{
	for (unsigned n = 0; n < prevLayer.size(); n++)
	{
		Neuron &neuron = prevLayer[n];
		double oldDeltaWeight = neuron.myoutputWeights[neuronIndex].deltaWeight;

		//new weight formula
		double newDeltaWeight = eta * neuron.getOutputValues() * mygradient + alpha * oldDeltaWeight;

		neuron.myoutputWeights[neuronIndex].deltaWeight = newDeltaWeight;
		neuron.myoutputWeights[neuronIndex].weight += newDeltaWeight;
	}
}
double Neuron::sumOfDifferentials(const Layer &nextLayer) const
{
	double sum = 0.0;

	// "sum our contributions of the errors at the nodes we feed"
	for (unsigned n = 0; n < nextLayer.size() - 1; ++n)		//oooooo, works the other way too
	{
		sum += myoutputWeights[n].weight * nextLayer[n].mygradient;
	}
	return sum;
}
void Neuron::calculateHiddenGradients(const Layer &nextLayer)	//delta error, sth like that
{
	double dow = sumOfDifferentials(nextLayer);	//sum of differential of weights of next layer
	mygradient = dow * Neuron::transferFunctionDerivative(myOutputVal);
}
void Neuron::calculateOutputGradients(double targetVal)
{
	double delta = targetVal - myOutputVal;
	mygradient = delta * Neuron::transferFunctionDerivative(myOutputVal);
}
double Neuron::transferFunction(double x)
{
	// tanh - output range [-1.0..1.0] - thats why we use tanh btw, good range for true-false
	return tanh(x);
}
double Neuron::transferFunctionDerivative(double x)
{
	// tanh derivative
	return 1.0 - x * x;
}
void Neuron::feedForward(const Layer &prevLayer)
{
	double sum = 0.0;

	// sum the previous layer's outputs
	for (int n = 0; n < prevLayer.size(); n++)
	{
		sum += prevLayer[n].getOutputValues() * prevLayer[n].myoutputWeights[neuronIndex].weight;
	}
	myOutputVal = Neuron::transferFunction(sum);
}
Neuron::Neuron(unsigned numOutputs, unsigned myIndex)
{
	//each neuron has some number to adress it to, connection and weigth
	for (unsigned c = 0; c < numOutputs; c++) 
	{
		myoutputWeights.push_back(Connection());
		myoutputWeights.back().weight = randomWeight();
	}
	neuronIndex = myIndex;
}