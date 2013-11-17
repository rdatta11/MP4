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
#include <vector>

#define BITMAP_DIM 28
#define NUM_DIGITS 5000
Parser::Parser(std::string fName, std::string fNameLabel){

	std::ifstream inLabel(fNameLabel);
	std::string inLine;
	std::ifstream input(fName);
	std::string line;
	int curNum;
	for(int i = 0 ;i < NUM_DIGITS; i++){
		std::getline(inLabel, inLine);
		curNum = atoi(inLine.c_str());
		std::cout<<"The number is: "<<curNum<<std::endl;
		for(int j = 0 ; j< BITMAP_DIM; j++){
			std::getline(input, line);
			for(int k = 0 ; k < line.size(); k++){
				mChar.push_back(line[k]);
				std::cout<<line[k];
			}
			std::cout<<'\n';
			mChar.push_back('\n');
		}
	}
}

void Parser::printFile(){
	int n = 0;
	for(auto &x : mChar){
		if(x != '\n'){
			n++;
		}
		else{
			std::cout<<"The number of characters is: "<<n<<std::endl;
			n = 0;
		}
		std::cout<<x;
	}
}