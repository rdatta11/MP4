//
//  Class.h
//  HandWriting
//
//  Created by Rahul Datta on 11/10/13.
//  Copyright (c) 2013 Rahul Datta. All rights reserved.
//

#ifndef __HandWriting__Class__
#define __HandWriting__Class__

#include <iostream>
#include <vector>


#define BITMAP_WIDTH 28
#define BITMAP_HEIGHT 28
#define K 1

class Class{
private:
	 struct pixel{
		float mTotal;
		float mColored;
		
		 pixel() : mTotal(K), mColored(K){}
	};
	
	std::vector<pixel> mProb;
	inline short _getRowMajorOrder(short i, short j){return j*BITMAP_WIDTH +i;}
	inline size_t _getSizeTotal(){return mProb.size();}
public:
	Class ();
	void changeProb(short i, short j, bool filled);
	
	void changeProb(short idx, bool filled);
	
	float getProb(short i , short j);
	
	float getProb(short idx);
	
	
};

#endif /* defined(__HandWriting__Class__) */
