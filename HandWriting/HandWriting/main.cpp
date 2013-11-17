//
//  main.cpp
//  HandWriting
//
//  Created by Rahul Datta on 11/8/13.
//  Copyright (c) 2013 Rahul Datta. All rights reserved.
//

#include <iostream>
#include "Training.h"
#include "Parser.h"

int main(int argc, const char * argv[])
{

	Training t1;
	
	t1.parser("/Users/RahulDatta/Downloads/digitdata/trainingimages", "/Users/RahulDatta/Downloads/digitdata/traininglabels");

	t1.test("/Users/RahulDatta/Downloads/digitdata/testimages", "/Users/RahulDatta/Downloads/digitdata/testlabels");
	
	t1.MAP();
    return 0;
}

