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

void TrainingData::getTopology(vector<unsigned> &topology)
{
	string line;	//we're gonna ready line by line
	string label;

	getline(trainingDataFile, line);
	stringstream ss(line);	//
	ss >> label;
	if (this->isEof() || label.compare("topology:") != 0)	//if end of training data or not topology <no topology defined then>
	{
		abort();	//abort the mission!
	}

	while (!ss.eof())
	{
		unsigned n;
		ss >> n;
		topology.push_back(n);
	}
	//return;	//nvm
}

TrainingData::TrainingData(const string filename)
{
	/// art, perfect use of constructor
	trainingDataFile.open(filename.c_str());
}

unsigned TrainingData::getNextInputs(vector<double> &inputValues)	//unsigned ~ positive int
{
	inputValues.clear();

	string line;	//again read line by line
	getline(trainingDataFile, line);
	stringstream ss(line);
	
	//
	string label;
	ss >> label;
	if (label.compare("in:") == 0)	//dont read if it's not input
	{
		double oneValue;
		while (ss >> oneValue)
		{
			inputValues.push_back(oneValue);
		}
	}

	return inputValues.size();
}

unsigned TrainingData::getTargetOutputs(vector<double> &targetOutputValuess)
{
	targetOutputValuess.clear();

	string line;
	getline(trainingDataFile, line);
	stringstream ss(line);

	string label;
	ss >> label;
	if (label.compare("out:") == 0)	//dun read if it's not target output
	{
		double oneValue;
		while (ss >> oneValue)
		{
			targetOutputValuess.push_back(oneValue);
		}
	}

	return targetOutputValuess.size();
}
