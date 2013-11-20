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
#include <iomanip>

#define NUM_DIGITS_TRAIN 5000
#define NUM_DIGITS_TEST 1000
#define BITMAP_DIM 28

Training::Training(){
	mClass.resize(NUM_CLASSES);
	mNumClass.resize(NUM_CLASSES);
	mProbPerNum.resize(NUM_CLASSES);
	mRate.resize(NUM_CLASSES);
	avgDigit.resize(NUM_CLASSES);
	for(int i = 0 ; i< mNumClass.size(); i++){
		mNumClass[i] = 0;
		mProbPerNum[i] = 1;
	}
	mTotal = 0;
	mNumCorrect = 0;
	for(int i = 0; i < NUM_CLASSES; i++){
		for(int j = 0; j < NUM_CLASSES; j++){
			conMatrix[i][j].mTop = 0;
			conMatrix[i][j].mBottom = 0;
		}
	}
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
		for(int j = 0 ; j< BITMAP_WIDTH; j++){
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
	std::vector<char>curDigit;
	curDigit.resize(BITMAP_HEIGHT*BITMAP_WIDTH);
	
	for(int i = 0; i < NUM_DIGITS_TEST; i++){
		std::getline(labelFile, labelString);
		curNum = atoi(labelString.c_str());
		for(int j = 0 ; j < BITMAP_HEIGHT; j++){
			std::getline(dataFile, dataString);
			for(int k = 0 ; k < dataString.size(); k++){
				curDigit[j*BITMAP_WIDTH + k] = dataString[k];
				for(int ba = 0 ; ba < 10; ba++)
				if(dataString[k] == ' '){
					setTestingProb(ba, k, j, false);
				}
				else{
					setTestingProb(ba, k, j, true);
				}
			}
		}
		setAvgDigit(curNum, curDigit);
		setStatistics(curNum, getMax());
		if(getMax() == curNum){
			mNumCorrect++;
		}
		mTotal++;
		clearProb();
	}
	std::cout<<"The accuracy is: "<<getAccuracy()<<std::endl;
	getStatistics();
	getAvgDigit();
	printHeatMap(0);
	std::cout<<std::endl;
	printHeatMap(9);
	std::cout<<std::endl;
	printHeatMap(8);
	std::cout<<std::endl;
	printHeatMap(4);
	std::cout<<std::endl;
	printHeatMap(7);
	std::cout<<std::endl;
	printHeatMap(5);
	std::cout<<std::endl;
	printHeatMap(3);
	
	printOddRation(4, 9);
	std::cout<<std::endl;
	printOddRation(7, 9);
	std::cout<<std::endl;
	printOddRation(8, 9);
	std::cout<<std::endl;
	printOddRation(5, 3);
	std::cout<<std::endl;
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

float Training:: getMaxProb(){
	int maxIdx = -1;
	float maxProb = LLONG_MIN;
	for(int i = 0 ; i < mProbPerNum.size(); i++){
		if(mProbPerNum[i] > maxProb){
			maxIdx = i;
			maxProb = mProbPerNum[i];
		}
	}
	return maxProb;
}
void Training::clearProb(){
	for(int i = 0 ; i< mProbPerNum.size(); i++){
		mProbPerNum[i] = 0;
	}
}


void Training::MAP(){
	float sum = 0;
	for(int i = 0 ; i < NUM_CLASSES; i++){
		sum += mNumClass[i];
	}
	std::cout<<"Sum: "<<sum<<::std::endl;
}

void Training::setStatistics(int testLabel, int testGuess){
	mRate[testLabel].mBottom++;
	
	if(testLabel == testGuess)
		mRate[testLabel].mTop++;
	conMatrix[testLabel][testGuess].mTop++;
	for(int i = 0; i < NUM_CLASSES; i++)
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
	
	for(int i = 0; i < NUM_CLASSES; i++){
		std::cout<<i<<" : ";
		for(int j = 0; j < NUM_CLASSES; j++){
			std::cout<<conMatrix[i][j].mTop/conMatrix[i][j].mBottom<<"  ";
		}
		std::cout<<std::endl;
	}
}

void Training::setAvgDigit(int curNum, std::vector<char> curDigit){
	if(avgDigit[curNum].prob < getMaxProb()){
		avgDigit[curNum].prob = getMaxProb();
		avgDigit[curNum].charDigit = curDigit;
	}
}

void Training::getAvgDigit(){
	for(int i = 0; i < NUM_CLASSES; i++){
		int x = 0;
		std::cout<<"Classified with log probability: "<<avgDigit[i].prob<<std::endl;
		for(int j = 0; j< avgDigit[i].charDigit.size(); j++){
			std::cout<<avgDigit[i].charDigit[j];
			x++;
			if(x == 28){
				std::cout<<std::endl;
				x = 0;
			}
		}
	}
}

void Training:: printHeatMap(int num){
	for( int i = 0; i < BITMAP_HEIGHT; i++){
		for( int j = 0; j < BITMAP_WIDTH; j++){
			float prob = log(mClass[num].getProb(i, j));
			if(prob < -.60205){
				std::cout<<":";
			}
			else if (prob < -0.30102999566){
				std::cout<<"-";
			}
			else if (prob < -0.1249387366){
				std::cout<<"|";
			}
			else{
				std::cout<<"+";
			}
		}
		std::cout<<std::endl;
	}
}

void Training:: printOddRation(int num1, int num2){
	for(int i = 0; i < BITMAP_HEIGHT; i++){
		for(int j = 0; j< BITMAP_WIDTH; j++){
			float prob = log((mClass[num1].getProb(i, j))/mClass[num2].getProb(i, j));
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
