//
//  Parser.cpp
//  HandWriting
//
//  Created by Rahul Datta on 11/8/13.
//  Copyright (c) 2013 Rahul Datta. All rights reserved.
//

#include "Parser.h"
#include <iostream>
#include <fstream>

Parser::Parser(std::string fName){
	
	char ch;
	
	std::fstream fIn(fName, std::fstream::in);
	while(fIn >> std::noskipws >>ch){
		mChar.push_back(ch);
	}
	
}