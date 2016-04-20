#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <fstream>
#include <sstream>
#include "Net.h"
#include "Neuron.h"
#include "TrainingData.h"
using namespace std;

double Net::averageSmoothingFactor = 4.0;// 558.0;//100.0; //smaples to average over. Edit this if it changed;		//yes, smaples
void Net::getResults(vector<double> &resultValues) const
{
	resultValues.clear();

	for (int n = 0; n < myLayers.back().size() - 1; n++)
	{
		resultValues.push_back(myLayers.back()[n].getOutputValues());
	}
}
void Net::backProp(const vector<double> &targetValues)
{
	// overall net error (RMS of output neuron errors)
	Layer &outputLayer = myLayers.back();
	myError = 0.0;

	for (int n = 0; n < outputLayer.size() - 1; n++)
	{
		double delta = targetValues[n] - outputLayer[n].getOutputValues();
		myError += delta * delta;
	}
	myError /= outputLayer.size() - 1; // get average error squared
	myError = sqrt(myError); // RMS

	myRecentAverageError = (myRecentAverageError * averageSmoothingFactor + myError) / (averageSmoothingFactor + 1.0);

	// output layer gradients
	for (int n = 0; n < outputLayer.size() - 1; n++)
	{
		outputLayer[n].calculateOutputGradients(targetValues[n]);
	}

	// hidden layer gradients
	for (int layerNum = myLayers.size() - 2; layerNum > 0; layerNum--)
	{
		Layer &hiddenLayer = myLayers[layerNum];	//looks better, ok?
		Layer &nextLayer = myLayers[layerNum + 1];

		for (int n = 0; n < hiddenLayer.size(); ++n)
		{
			hiddenLayer[n].calculateHiddenGradients(nextLayer);
		}
	}

	//for all except inputs update weights
	for (int layerNum = myLayers.size() - 1; layerNum > 0; layerNum--)
	{
		Layer &layer = myLayers[layerNum];	//much better
		Layer &prevLayer = myLayers[layerNum - 1];

		for (int n = 0; n < layer.size() - 1; n++)
		{
			layer[n].updateInputWeights(prevLayer);
		}
	}
}
void Net::feedForward(const vector<double> &inputValues)
{
	assert(inputValues.size() == myLayers[0].size() - 1);	//-1 cuz of bias

	// assign input vals
	for (int i = 0; i < inputValues.size(); i++)
	{
		myLayers[0][i].setOutputVal(inputValues[i]);
	}

	// forward propagate
	for (int layerNum = 1; layerNum < myLayers.size(); layerNum++)
	{
		Layer &prevLayer = myLayers[layerNum - 1];
		for (int n = 0; n < myLayers[layerNum].size() - 1; n++)
		{
			myLayers[layerNum][n].feedForward(prevLayer);
		}
	}
}
Net::Net(const vector<unsigned> &topology)
{
	unsigned numLayers = topology.size();		//unsigned is kinda universal? //test
	for (unsigned layerNum = 0; layerNum < numLayers; layerNum++)
	{
		myLayers.push_back(Layer());
		unsigned numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];		//if == topology -1, return 0, otherwise new layer

		// new layer, we fill it with neurons and add bias neuron at each one at the end
		for (unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum) {
			myLayers.back().push_back(Neuron(numOutputs, neuronNum));
			//cout << "Woo, created neuron~ ^^" << endl;	//test
		}

		// force bias neurons output to be 1.0. it was the last one so back().back()
		myLayers.back().back().setOutputVal(1.0);
	}
}