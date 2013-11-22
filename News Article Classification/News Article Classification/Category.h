//
//  Category.h
//  News Article Classification
//
//  Created by Rahul Datta on 11/21/13.
//  Copyright (c) 2013 Rahul Datta. All rights reserved.
//

#ifndef __News_Article_Classification__Category__
#define __News_Article_Classification__Category__

#include <iostream>
#include "Word.h"
#include <vector>
class Category{
private:
	
	struct wordperClass{
		std::vector<Word> mWPC;
		float mTotalWords = 0;
	};
public:
	
	std::vector<wordperClass> mCategory;
	
	Category();
	
	//inline void setTotalWords(float n){mTotalWords+=n;}
	
	//inline float getTotalWords(){return mTotalWords;}
	
	
};

#endif /* defined(__News_Article_Classification__Category__) */
