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

#define NUM_CLASSES 10

class Training{
private:
	
	std::vector<Class> mClass;
	std::vector<char> mChar;
	std::vector<int> mNumClass;
	std::vector<float> mProbPerNum;
	float mNumCorrect;
	float mTotal;
	int getMax();
	void clearProb();
	void getTestingProb(int classIdx, int i, int j, bool filled);
	void setTestingProb(int digit, int k, int j, bool filled);
	
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
