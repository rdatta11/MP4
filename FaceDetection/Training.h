//
//  Training.h
//  FaceDetection
//
//  Created by Rahul Datta on 11/17/13.
//  Copyright (c) 2013 Rahul Datta. All rights reserved.
//

#ifndef __FaceDetection__Training__
#define __FaceDetection__Training__

#include <iostream>
#include <vector>
#include <string>
#include "Face.h"

#define NUM_FACES 2

class Training{
private:
	struct fraction{
		float mBottom;
		float mTop;
		fraction() : mTop(0), mBottom(0){}
	};
	struct avgDigitStat{
		std::vector<char> charDigit;
		float prob = LLONG_MIN;
	};
	//private vars
	fraction conMatrix [NUM_FACES][NUM_FACES];
	std::vector<fraction> mRate;
	std::vector<Face> mFace;
	std::vector<char> mChar;
	std::vector<int> mNumFace;
	std::vector<float> mProbPerNum;
	float mNumCorrect;
	float mTotal;
	
	//get max probability
	int getMax();
	
	//clears probability array
	void clearProb();
	
	//gets the testing prob value
	void getTestingProb(int FaceIdx, int i, int j, bool filled);
	
	//sets the testing prob value
	void setTestingProb(int digit, int k, int j, bool filled);
	
	//set the statistics for reporting
	void setStatistics(int testLabel, int testGuess);
	
	//get the statistics for reporting
	void getStatistics();
	
	//print the odd ratio
	void printOddRation(int num1, int num2);
	
	//print face
	void printFace();
	
public:
	//parse and train data
	void parser(std::string fname, std::string fNameLabel);
	
	//intialize values of private vars
	Training();
	
	//print the face value
	void printFaceValue();
	
	//get the probability
	float getProb(short FaceType, short idx);
	
	//parse and test data
	void test(std::string fname, std::string fNameLabel);
	
	//get accuracy for experiment
	inline float getAccuracy(){return mNumCorrect/mTotal;}
	
	//print the probability for experiment
	void printProb(int FaceNum);
	
	//map code (not used)
	void MAP();
	
};


#endif /* defined(__FaceDetection__Training__) */
