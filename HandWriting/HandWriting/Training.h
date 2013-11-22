//
//  Training.h
//  HandWriting
//
//  Created by Rahul Datta on 11/10/13.
//  Copyright (c) 2013 Rahul Datta. All rights reserved.
//

#ifndef __HandWriting__Training__
#define __HandWriting__Training__

#include <iostream>
#include <vector>
#include <string>
#include "Class.h"
#include <climits>


#define NUM_CLASSES 10

class Training{
private:
	
	struct fraction{
		float mBottom;
		float mTop;
		fraction() : mTop(0), mBottom(0){}
	};
	//used to help get avg digit statistics
	struct avgDigitStat{
		std::vector<char> charDigit;
		float prob = LLONG_MIN;
	};
	
	/*private variables*/
	std::vector<avgDigitStat> avgDigit;
	fraction conMatrix [NUM_CLASSES][NUM_CLASSES];
	std::vector<Class> mClass;
	std::vector<char> mChar;
	std::vector<float> mNumClass;
	std::vector<float> mProbPerNum;
	std::vector<fraction> mRate;
	float mNumCorrect;
	float mTotal;
	
	/*gets the most likely digits*/
	int getMax();
	
	//clears the probability array
	void clearProb();
	
	//get the testing probability
	void getTestingProb(int classIdx, int i, int j, bool filled);
	
	//sets the testing probability
	void setTestingProb(int digit, int k, int j, bool filled);
	
	//set the statistics for write up
	void setStatistics(int testLabel, int testGuess);
	
	//get the statistics for write up
	void getStatistics();
	
	//the the value of the max probabiltiy
	float getMaxProb();
	
	//used to get the most avg digit
	void setAvgDigit(int curNum, std::vector<char> curDigit);
	
	//get avg digit data
	void getAvgDigit();
	
	//prints the ascii heat map
	void printHeatMap(int num);
	
	//prints the ascii odd ratio map
	void printOddRation(int num1, int num2);
	
	//print the character buffer
	void printChar();
	
public:
	//parses file and creates train data
	void parser(std::string fname, std::string fNameLabel);
	
	//intialize private vars
	Training();
	
	//print the class values
	void printClassValue();
	
	//get the probability of a class
	float getProb(short classType, short idx);
	
	//parse test file and run the test algo
	void test(std::string fname, std::string fNameLabel);
	
	//gets the accuracy
	inline float getAccuracy(){return mNumCorrect/mTotal;}
	
	//print probabilty
	void printProb(int classNum);
	
	//MAP calculation
	void MAP();
	

	
};

#endif /* defined(__HandWriting__Training__) */
