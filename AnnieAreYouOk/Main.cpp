#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <fstream>
#include <sstream>
#include <array>	//"Don't use C arrays, they only bring pain and sorrow"	
#include "Neuron.h"
#include "Net.h"
#include "TrainingData.h"
#include "Recognize.h"

using namespace std;

int main()
{
	LoadAlpha myAlpha;
	TrainingData trainData("trainingData.txt");

	vector<unsigned> topology;
	trainData.getTopology(topology);

	Net myNet(topology);

	vector<double> inputValues, targetValues, resultValues;	//layers woo
	int trainingPass = 0;	//we're gonna count down our tries

	while (!trainData.isEof()) {
		++trainingPass;
		cout << endl << "Iteration " << trainingPass;

		// get new input and feed forward
		if (trainData.getNextInputs(inputValues) != topology[0])
		{
			break;	//i know this is just one line and brackets arent needed here but i feel better with them
		}
		showVectorValues(": Inputs:", inputValues);
		myAlpha.recognizeLetter("Input check: ", inputValues);
		myNet.feedForward(inputValues);
		// check actual results
		myNet.getResults(resultValues);
		showVectorValues("Outputs:", resultValues);
		myAlpha.recognizeLetter("Output check: ", resultValues);
		// compare with what it should be
		trainData.getTargetOutputs(targetValues);
		showVectorValues("Targets:", targetValues);
		assert(targetValues.size() == topology.back());	//if output amount is not same as output neuron number
		myNet.backProp(targetValues);

		// Report how well the training is working, average over recent samples:
		cout << "Net recent average error: "
			<< myNet.getRecentAverageError() << endl;
	}
	cout << endl << "Finished training!" << endl;
}
