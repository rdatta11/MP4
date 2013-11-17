//
//  Training.cpp
//  HandWriting
//
//  Created by Rahul Datta on 11/10/13.
//  Copyright (c) 2013 Rahul Datta. All rights reserved.
//

#include "Training.h"
#include <fstream>
#include "Class.h"
#include <stdlib.h>
#include <math.h>
#include <climits>

#define NUM_DIGITS_TRAIN 5000
#define NUM_DIGITS_TEST 1000
#define BITMAP_DIM 28

Training::Training(){
	mClass.resize(NUM_CLASSES);
	mNumClass.resize(NUM_CLASSES);
	mProbPerNum.resize(NUM_CLASSES);
	for(int i = 0 ; i< mNumClass.size(); i++){
		mNumClass[i] = 0;
		mProbPerNum[i] = 1;
	}
	mTotal = 0;
	mNumCorrect = 0;
}

void Training::parser(std::string fName, std::string fNameLabel){
	std::ifstream inLabel(fNameLabel);
	std::string inLine;
	std::ifstream input(fName);
	std::string line;
	int curNum;

	for(int i = 0 ; i <NUM_DIGITS_TRAIN; i++){
		std::getline(inLabel, inLine);
		curNum = atoi(inLine.c_str());
		mNumClass[curNum]++;
		for(int j = 0 ; j< BITMAP_DIM; j++){
			std::getline(input, line);
			for(int k = 0 ; k < line.size(); k++){
				if(line[k] == ' '){
					mClass[curNum].changeProb(k, j, false);
				}
				else{
					mClass[curNum].changeProb(k, j, true);
				}
			}
		}
	}
}
void Training:: printProb(int classNum){
	std::cout<<"Digit: "<<classNum<<std::endl;
	for(int i = 0 ; i < BITMAP_WIDTH; i++){
		for(int j = 0 ; j < BITMAP_HEIGHT; j++){
			std::cout<<"The prob of point "<<i<<", "<<j<<" is "<<mClass[classNum].getProb(i, j)<<std::endl;
		}
	}
	std::cout<<std::endl<<std::endl;
}

void Training::printClassValue(){
	for(int i = 0 ; i < mNumClass.size(); i++){
		std::cout<<"Class "<< i <<" has a value "<< mNumClass[i]<<std::endl;
	}
}

float Training::getProb(short classType, short idx){
	return mClass[classType].getProb(idx);
}

void Training::test(std::string fName, std::string fNameLabel){
	std::ifstream labelFile(fNameLabel);
	std::string labelString;
	std::ifstream dataFile(fName);
	std::string dataString;
	int curNum;
	
	for(int i = 0; i < NUM_DIGITS_TEST; i++){
		std::getline(labelFile, labelString);
		curNum = atoi(labelString.c_str());
		for(int j = 0 ; j < BITMAP_HEIGHT; j++){
			std::getline(dataFile, dataString);
			for(int k = 0 ; k < dataString.size(); k++){
				for(int ba = 0 ; ba < 10; ba++)
				if(dataString[k] == ' '){
					setTestingProb(ba, k, j, false);
				}
				else{
					setTestingProb(ba, k, j, true);
				}
			}
		}
		if(getMax() == curNum){
			mNumCorrect++;
		}
		mTotal++;
		clearProb();
	}
	std::cout<<"The accuracy is: "<<getAccuracy()<<std::endl;
}

void Training::setTestingProb(int digit, int k, int j, bool filled){
	if(filled){
		mProbPerNum[digit] = mProbPerNum[digit] + log(mClass[digit].getProb(k, j));
	}
	else{
		mProbPerNum[digit] = mProbPerNum[digit] + log(1-mClass[digit].getProb(k, j));
	}
}
	
int Training::getMax(){
	int maxIdx = -1;
	float maxProb = LLONG_MIN;
	for(int i = 0 ; i < mProbPerNum.size(); i++){
		if(mProbPerNum[i] > maxProb){
			maxIdx = i;
			maxProb = mProbPerNum[i];
		}
	}
	return maxIdx;
}
void Training::clearProb(){
	for(int i = 0 ; i< mProbPerNum.size(); i++){
		mProbPerNum[i] = 0;
	}
}


void Training::MAP(){
	int sum = 0;
	for(int i = 0 ; i < NUM_CLASSES; i++){
		sum += mNumClass[i];
	}
	std::cout<<"Sum: "<<sum<<::std::endl;
}