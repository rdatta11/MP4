//
//  Face.h
//  FaceDetection
//
//  Created by Rahul Datta on 11/17/13.
//  Copyright (c) 2013 Rahul Datta. All rights reserved.
//

#ifndef __FaceDetection__Face__
#define __FaceDetection__Face__

#include <iostream>
#include <vector>
#define BITMAP_WIDTH 60
#define BITMAP_HEIGHT 70
#define K 1
#define V 2

class Face{
private:
	struct pixel{
		float mTotal;
		float mColored;
		
		pixel() : mTotal(V*K), mColored(K){}
	};
	
	std::vector<pixel> mProb;
	inline int  getRowMajorOrder(int i, int j){return j*BITMAP_WIDTH + i;}
	inline size_t getSizeTotal(){return mProb.size();}
	
public:
	Face();
	
	void changeProb(int i, int j, bool filled);
	
	void changeProb(int idx, bool filled);
	
	float getProb(int i, int j);
	
	float getProb(int idx);
};


#endif /* defined(__FaceDetection__Face__) */
