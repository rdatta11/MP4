//
//  Face.cpp
//  FaceDetection
//
//  Created by Rahul Datta on 11/17/13.
//  Copyright (c) 2013 Rahul Datta. All rights reserved.
//

#include "Face.h"
Face::Face(){
	mProb.resize(BITMAP_WIDTH*BITMAP_HEIGHT);
}

void Face:: changeProb(int i, int j, bool filled){
	changeProb(getRowMajorOrder(i, j), filled);
}

void Face::changeProb(int idx, bool filled){
	mProb[idx].mTotal++;
	if(filled){
		mProb[idx].mColored++;
	}
}

float Face:: getProb(int i, int j){
	return getProb(getRowMajorOrder(i, j));
}

float Face:: getProb(int idx){
	return mProb[idx].mColored/mProb[idx].mTotal;
}