#ifndef TRAIN
#define TRAIN

#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <fstream>
#include <sstream>
using namespace std;

class TrainingData
{
public:
	TrainingData(const string filename);
	bool isEof(void) { return trainingDataFile.eof(); }	//short so stays here. Checks if enf of file
	void getTopology(vector<unsigned> &topology);

	unsigned getNextInputs(vector<double> &inputValues);
	unsigned getTargetOutputs(vector<double> &targetOutputValuess);

private:
	ifstream trainingDataFile;
};


#endif