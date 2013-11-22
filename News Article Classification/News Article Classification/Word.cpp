//
//  Word.cpp
//  News Article Classification
//
//  Created by Rahul Datta on 11/21/13.
//  Copyright (c) 2013 Rahul Datta. All rights reserved.
//

#include "Word.h"
Word::Word(){
	mWord = NULL;
	mNum = 0;
}

Word::Word(char* word){
	mWord = word;
	mNum = 0;
}