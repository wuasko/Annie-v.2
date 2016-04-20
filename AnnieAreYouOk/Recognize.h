#ifndef READ
#define READ

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

using namespace std;

void showVectorValues(string label, vector<double> &v);
struct alphaabt {	//that was mistype but i like it, it'll stay like this
	char letter;
	array<int, 35> letters;
};
class LoadAlpha {
public:
	array<alphaabt, 26> checkLetter;
	LoadAlpha();
	void recognizeLetter(string label, vector<double> &v);
};



#endif