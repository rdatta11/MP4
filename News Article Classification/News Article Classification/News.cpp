//
//  News.cpp
//  News Article Classification
//
//  Created by Rahul Datta on 11/21/13.
//  Copyright (c) 2013 Rahul Datta. All rights reserved.
//

#include "News.h"
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>

News::News(){
	mProb.resize(NUM_CLASSES);
	mTop = 0;
	mBottom = 0;
	clearProb();
}
void News::clearProb(){
	for(int i = 0 ; i < mProb.size(); i++){
		mProb[i] = 0;
	}
}
void News::parse(std::string fName){
	std::ifstream trainFile(fName);
	std::string trainString;
	char * word= NULL;
	while(std::getline(trainFile, trainString)){
		//std::cout<<trainString<<std::endl;
		//std::cout<<trainString[0]<<std::endl;
		int cat = trainString[0] - '0';
		trainString[0] = ' ';
		char* pch;
		char *dup = strdup(trainString.c_str());
		pch = strtok(dup, " :");
		int i = 0;
		
		while(pch != NULL){
			//std::cout<<pch<<std::endl;
			if(i%2 == 0){
				word = pch;
			}
			else{
				//convert to int
				addWord(cat, word, atoi(pch));
			}
			i++;
			pch = strtok(NULL, " :");
		}
		//free(pch);
		//free(dup);
		//free(word);
	}
	std::cout<<word<<std::endl;
}

void News:: test(std::string fName){
	std::ifstream testFile(fName);
	std::string testString;
	
	char * word= NULL;
	while(std::getline(testFile, testString)){
		//std::cout<<trainString<<std::endl;
		//std::cout<<trainString[0]<<std::endl;
		int cat = testString[0] - '0';
		testString[0] = ' ';
		char* pch;
		char *dup = strdup(testString.c_str());
		pch = strtok(dup, " :");
		int i = 0;
		
		while(pch != NULL){
			//std::cout<<pch<<std::endl;
			if(i%2 == 0){
				word = pch;
			}
			else{
				//convert to int
				//setTesting
				setTestingProb(word, atoi(pch));
			}
			i++;
			pch = strtok(NULL, " :");
		}
		//free(pch);
		//free(dup);
		//free(word);
		if(getMaxCat() == cat){
			mTop++;
		}
		mBottom++;
		clearProb();
	}
	std::cout<<"The accuarcy is: "<<getAccuracy()<<std::endl;
	//std::cout<<word<<std::endl;
	
}
void News::addWord(int idx, char *word, int num){
	for(int n = 0; n < mCat.mCategory[idx].mWPC.size(); n++){
		if(mCat.mCategory[idx].mWPC[n].getWord() == word){
			mCat.mCategory[idx].mWPC[n].setNum(num);
			mCat.mCategory[idx].mTotalWords += num;
			return;
		}
	}
	mCat.mCategory[idx].mWPC.push_back(word);
	mCat.mCategory[idx].mWPC[mCat.mCategory[idx].mWPC.size()-1].setNum(num);
}

void News::setTestingProb(char *word, int num){
	for(int i = 0; i < NUM_CLASSES; i++){
		for(int j = 0; j < mCat.mCategory[i].mWPC.size(); j++){
			if(mCat.mCategory[i].mWPC[j].getWord() == word){
				mProb[i] = mProb[i] + log((mCat.mCategory[i].mWPC[j].getNum()/mCat.mCategory[i].mTotalWords)*num);
				return;
			}
		}
	}
}

int News::getMaxCat(){
	float max = LLONG_MIN;
	int idx = -1;
	for(int i = 0; i < mProb.size(); i++){
		if(mProb[i] > max){
			max = mProb[i];
			idx = i;
		}
	}
	return idx;
}