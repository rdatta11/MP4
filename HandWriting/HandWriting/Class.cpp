//
//  Class.cpp
//  HandWriting
//
//  Created by Rahul Datta on 11/10/13.
//  Copyright (c) 2013 Rahul Datta. All rights reserved.
//

#include "Class.h"



Class::Class(){
	mProb.resize((BITMAP_HEIGHT*BITMAP_WIDTH));
}
void Class:: changeProb(short i, short j, bool filled){
	mProb[_getRowMajorOrder(i, j)].mTotal++;
	if(filled){
		mProb[_getRowMajorOrder(i, j)].mColored++;
	}
}

void Class:: changeProb(short idx, bool filled){
	mProb[idx].mTotal++;
	if(filled){
		mProb[idx].mColored++;
	}
}

float Class:: getProb(short i , short j){
	return mProb[_getRowMajorOrder(i, j)].mColored/mProb[_getRowMajorOrder(i, j)].mTotal;
}

float Class:: getProb(short idx){
	return mProb[idx].mColored/mProb[idx].mTotal;
}