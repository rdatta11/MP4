//
//  Training.cpp
//  FaceDetection
//
//  Created by Rahul Datta on 11/17/13.
//  Copyright (c) 2013 Rahul Datta. All rights reserved.
//

#include "Training.h"
#include <fstream>
#include "Face.h"
#include <stdlib.h>
#include <math.h>
#include <climits>
#include <iomanip>

#define NUM_DIGITS_TRAIN 451
#define NUM_DIGITS_TEST 150
#define BITMAP_DIM 70

Training::Training(){
	mFace.resize(NUM_FACES);
	mNumFace.resize(NUM_FACES);
	mProbPerNum.resize(NUM_FACES);
	mRate.resize(NUM_FACES);
	for(int i = 0 ; i< mNumFace.size(); i++){
		mNumFace[i] = 0;
		mProbPerNum[i] = 1;
	}
	mTotal = 0;
	mNumCorrect = 0;
}

void Training::parser(std::string fName, std::string fNameLabel){
	std::ifstream labelFile(fNameLabel);
	std::string labelString;
	std::ifstream dataFile(fName);
	std::string dataString;
	int face;
	
	for(int i = 0; i < NUM_DIGITS_TRAIN; i++){
		std::getline(labelFile, labelString);
		face = atoi(labelString.c_str());
		//std::cout<<"Value: "<<face<<std::endl;
		mNumFace[face]++;
		for(int j = 0; j < BITMAP_HEIGHT; j++){
			std::getline(dataFile, dataString);
			for(int k = 0; k < dataString.size(); k++){
				//std::cout<<dataString[k];
				if(dataString[k] == ' '){
					mFace[face].changeProb(k, j, false);
				}
				else{
					mFace[face].changeProb(k, j, true);
				}
			}
			//std::cout<<std::endl;
		}
	}
}
void Training:: printProb(int FaceNum){
	std::cout<<"Digit: "<<FaceNum<<std::endl;
	for(int i = 0 ; i < BITMAP_WIDTH; i++){
		for(int j = 0 ; j < BITMAP_HEIGHT; j++){
			std::cout<<"The prob of point "<<i<<", "<<j<<" is "<<mFace[FaceNum].getProb(i, j)<<std::endl;
		}
	}
	std::cout<<std::endl<<std::endl;
}

void Training::printFaceValue(){
	for(int i = 0 ; i < mNumFace.size(); i++){
		std::cout<<"Face "<< i <<" has a value "<< mNumFace[i]<<std::endl;
	}
}

float Training::getProb(short FaceType, short idx){
	return mFace[FaceType].getProb(idx);
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
		for(int j = 0; j< BITMAP_HEIGHT; j++){
			std::getline(dataFile, dataString);
			for(int k = 0; k < dataString.size(); k++){
				for(int ba = 0; ba < NUM_FACES; ba++){
					if(dataString[k] == ' '){
						setTestingProb(ba, k, j, false);
					}
					else{
						setTestingProb(ba, k, j, true);
					}
				}
			}
		}
		setStatistics(curNum, getMax());
		if(getMax() == curNum){
			mNumCorrect++;
		}
		mTotal++;
		clearProb();
	}
	std::cout<<"The accuracy is: "<<getAccuracy()<<std::endl;
	getStatistics();
	std::cout<<std::endl;
	printOddRation(0, 1);
	std::cout<<std::endl;
	printOddRation(1, 0);
}

void Training::setTestingProb(int digit, int k, int j, bool filled){
	if(filled){
		mProbPerNum[digit] = mProbPerNum[digit] + log(mFace[digit].getProb(k, j));
	}
	else{
		mProbPerNum[digit] = mProbPerNum[digit] + log(1-mFace[digit].getProb(k, j));
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
	for(int i = 0 ; i < NUM_FACES; i++){
		sum += mNumFace[i];
	}
	std::cout<<"Sum: "<<sum<<::std::endl;
}

void Training::setStatistics(int testLabel, int testGuess){
	mRate[testLabel].mBottom++;
	
	if(testLabel == testGuess)
		mRate[testLabel].mTop++;
	conMatrix[testLabel][testGuess].mTop++;
	for(int i = 0; i < NUM_FACES; i++)
		conMatrix[testLabel][i].mBottom++;
}

void Training::getStatistics(){
	std::cout<<"Classification Rate"<<std::endl;
	std::cout<<"-------------------"<<std::endl;
	for(int i = 0; i < mRate.size(); i++){
		std::cout<<i<<" : "<<std::setprecision(2)<< std::fixed<<mRate[i].mTop/mRate[i].mBottom<<std::endl;
	}
	std::cout<<std::endl<<std::endl;
	std::cout<<"Confusion Matrix"<<std::endl;
	std::cout<<"-------------------"<<std::endl;
	
	for(int i = 0; i < NUM_FACES; i++){
		std::cout<<i<<" : ";
		for(int j = 0; j < NUM_FACES; j++){
			std::cout<<conMatrix[i][j].mTop/conMatrix[i][j].mBottom<<"  ";
		}
		std::cout<<std::endl;
	}
}

void Training:: printOddRation(int num1, int num2){
	for(int i = 0; i < BITMAP_HEIGHT; i++){
		for(int j = 0; j< BITMAP_WIDTH; j++){
			float prob = log((mFace[num1].getProb(i, j))/mFace[num2].getProb(i, j));
			if(prob < 0){
				std::cout<<"-";
			}
			else if (.9 < prob && 1.1 > prob){
				std::cout<<" ";
			}
			else{
				std::cout<<"+";
			}
		}
		std::cout<<std::endl;
	}
}
