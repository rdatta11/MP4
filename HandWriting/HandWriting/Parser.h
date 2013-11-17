//
//  Parser.h
//  HandWriting
//
//  Created by Rahul Datta on 11/8/13.
//  Copyright (c) 2013 Rahul Datta. All rights reserved.
//

#ifndef __HandWriting__Parser__
#define __HandWriting__Parser__

#include <iostream>
#include <vector>
#include <string>
class Parser{
private:
	std::vector<char> mChar;
public:
	Parser(std::string fname, std::string fNameLabel);
	void printFile();
	
};
#endif /* defined(__HandWriting__Parser__) */
