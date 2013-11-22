//
//  News.h
//  News Article Classification
//
//  Created by Rahul Datta on 11/21/13.
//  Copyright (c) 2013 Rahul Datta. All rights reserved.
//

#ifndef __News_Article_Classification__News__
#define __News_Article_Classification__News__

#include <iostream>
#include <vector>
#include "Category.h"

class News{
private:
	
	std::vector<float> mProb;
	
	Category mCat;
	
	void addWord(int idx, char * word, int num);
	
	void setTestingProb(char *word, int num);
	
	void clearProb();
	
	int getMaxCat();
	
	float mTop;
	
	float mBottom;
	
	inline float getAccuracy(){return mTop/mBottom;}
	
public:
	
	News();
	
	void parse(std::string fName);
	
	void test(std::string fName);
};

#endif /* defined(__News_Article_Classification__News__) */
