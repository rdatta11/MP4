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
	struct avgDigitStat{
		std::vector<char> charDigit;
		float prob = LLONG_MIN;
	};
	
	std::vector<avgDigitStat> avgDigit;
	fraction conMatrix [NUM_CLASSES][NUM_CLASSES];
	std::vector<Class> mClass;
	std::vector<char> mChar;
	std::vector<float> mNumClass;
	std::vector<float> mProbPerNum;
	std::vector<fraction> mRate;
	float mNumCorrect;
	float mTotal;
	int getMax();
	void clearProb();
	void getTestingProb(int classIdx, int i, int j, bool filled);
	void setTestingProb(int digit, int k, int j, bool filled);
	
	void setStatistics(int testLabel, int testGuess);
	void getStatistics();
	float getMaxProb();
	void setAvgDigit(int curNum, std::vector<char> curDigit);
	void getAvgDigit();
	void printHeatMap(int num);
	void printOddRation(int num1, int num2);
	
public:
	void parser(std::string fname, std::string fNameLabel);
	
	Training();
	
	void printClassValue();
	
	float getProb(short classType, short idx);
	
	void test(std::string fname, std::string fNameLabel);
	
	inline float getAccuracy(){return mNumCorrect/mTotal;}
	
	void printProb(int classNum);
	
	void MAP();
	

	
};

#endif /* defined(__HandWriting__Training__) */
