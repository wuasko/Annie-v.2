#ifndef NET
#define NET

#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <fstream>
#include <sstream>

using namespace std;
struct Connection
{
	double weight;
	double deltaWeight;
};
class Neuron;
typedef vector<Neuron> Layer;
// ================= class Net =========================
class Net
{
public:
	Net(const vector<unsigned> &topology);
	void feedForward(const vector<double> &inputValues);
	void backProp(const vector<double> &targetValues);
	void getResults(vector<double> &resultValues) const;	//we wont change so const
	double getRecentAverageError(void) const { return myRecentAverageError; }	//so short, it's staying here!

private:
	vector<Layer> myLayers; // myLayers[layerNum][neuronNum]
	double myError;
	double myRecentAverageError;
	static double averageSmoothingFactor;
};

#endif