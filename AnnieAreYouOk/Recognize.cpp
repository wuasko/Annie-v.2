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


void showVectorValues(string label, vector<double> &v) {
	
	cout << label << " " << endl;	//for letters
	for (unsigned i = 0; i < v.size(); i) {
		for (int j = 0; j < 5;j++)
		{
			//cout << v[i] << " ";
			char c = 219;
			if (v[i] > 0.5)
			{
				cout << c << c; //<< " ";
			}
			else
			{
				cout << "  ";// << " ";
			}
			i++;
		}
		cout << endl;
	}
}

LoadAlpha::LoadAlpha()
{
	ifstream alphfile;	//thats file with letter coding
	alphfile.open("alph.txt");
	int temp;
	//check if exists
	if (!alphfile)
	{
		cout << "Error! Cannot load alphabet file." << endl;
	}
	else
	{
		int j = 0;
		while (!alphfile.eof())
		//for (int pap = 1;pap < 3;pap++)	//test
		{
			alphfile >> LoadAlpha::checkLetter[j].letter;
			alphfile.ignore();
			//cout << "Loaded " << LoadAlpha::checkLetter[j].letter << " :"; //test

			for (int i = 0;i < 35;i++)
			{
				alphfile >> temp;
				LoadAlpha::checkLetter[j].letters[i] = temp;
				alphfile.ignore();
				//cout << LoadAlpha::checkLetter[j].letters[i];
			}
			//cout << endl;
			j++;
		}
		alphfile.close();
	}
}

void LoadAlpha::recognizeLetter(string label, vector<double> &v)
{
	cout << label << " " << endl;
	//int *interpret;
	//interpret = new int[v.size()];
	array<int, 35> interpret;	//meeeh, not dynamic since it's specifically for this case, we dun need dynamic allo here
	for (int i = 0;i < v.size();i++)	///convert to 1 0 form
	{
		if (v[i] > 0.5)
		{
			interpret[i] = 1;
		}
		else
		{
			interpret[i] = 0;
		}
	}
	for (int j = 0;j < 26;j++)
	{
		if (interpret == LoadAlpha::checkLetter[j].letters)
		{
			cout << "Perfect match! Recognized as " << LoadAlpha::checkLetter[j].letter << endl;
			///i am very tired
		}
	}
}