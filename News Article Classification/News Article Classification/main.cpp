//
//  main.cpp
//  News Article Classification
//
//  Created by Rahul Datta on 11/21/13.
//  Copyright (c) 2013 Rahul Datta. All rights reserved.
//

#include <iostream>
#include "News.h"

int main(int argc, const char * argv[])
{

	// insert code here...
	//std::cout << "Hello, World!\n";
	News n1;
	
	n1.parse("/Users/RahulDatta/Downloads/8newsgroups/8.trainingdata.txt");
	
	n1.test("/Users/RahulDatta/Downloads/8newsgroups/8.testingdata.txt");
    return 0;
}

