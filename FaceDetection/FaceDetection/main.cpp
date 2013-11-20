//
//  main.cpp
//  FaceDetection
//
//  Created by Rahul Datta on 11/17/13.
//  Copyright (c) 2013 Rahul Datta. All rights reserved.
//

#include <iostream>
#include "Training.h"
int main(int argc, const char * argv[])
{

	Training t1;
	
	t1.parser("/Users/RahulDatta/Downloads/facedata/facedatatrain", "/Users/RahulDatta/Downloads/facedata/facedatatrainlabels");
	
	t1.test("/Users/RahulDatta/Downloads/facedata/facedatatest", "/Users/RahulDatta/Downloads/facedata/facedatatestlabels");
    return 0;
}

