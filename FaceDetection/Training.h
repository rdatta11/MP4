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
	
	fraction conMatrix [NUM_FACES][NUM_FACES];
	std::vector<fraction> mRate;
	std::vector<Face> mFace;
	std::vector<char> mChar;
	std::vector<int> mNumFace;
	std::vector<float> mProbPerNum;
	float mNumCorrect;
	float mTotal;
	int getMax();
	void clearProb();
	void getTestingProb(int FaceIdx, int i, int j, bool filled);
	void setTestingProb(int digit, int k, int j, bool filled);
	void setStatistics(int testLabel, int testGuess);
	void getStatistics();
	void printOddRation(int num1, int num2);
	
public:
	void parser(std::string fname, std::string fNameLabel);
	
	Training();
	
	void printFaceValue();
	
	float getProb(short FaceType, short idx);
	
	void test(std::string fname, std::string fNameLabel);
	
	inline float getAccuracy(){return mNumCorrect/mTotal;}
	
	void printProb(int FaceNum);
	
	void MAP();
	
};


#endif /* defined(__FaceDetection__Training__) */
