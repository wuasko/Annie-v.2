#ifndef NEURON
#define NEURON

#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <fstream>
#include <sstream>
#include "Net.h"
using namespace std;
struct Connection;	//define at least
class Neuron;
typedef vector<Neuron> Layer;
// =============== class Neuron ===================
class Neuron
{
public:
	Neuron(unsigned numOutputs, unsigned myIndex);
	void setOutputVal(double val) { myOutputVal = val; }
	double getOutputValues(void) const { return myOutputVal; }
	void feedForward(const Layer &prevLayer);
	void calculateOutputGradients(double targetVal);
	void calculateHiddenGradients(const Layer &nextLayer);
	void updateInputWeights(Layer &prevLayer);

private:
	static double eta;   // [0.0..1.0] overall net training rate
	static double alpha; // [0.0..n] multiplier of last weight change ("momentum")
	static double transferFunction(double x);
	static double transferFunctionDerivative(double x);
	static double randomWeight(void) { return rand() / double(RAND_MAX); }	//"magic incantation to get number between 0 and 1"
	double sumOfDifferentials(const Layer &nextLayer) const;
	double myOutputVal;
	vector<Connection> myoutputWeights;
	unsigned neuronIndex;
	double mygradient;
};

#endif