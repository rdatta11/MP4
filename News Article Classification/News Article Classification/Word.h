//
//  Word.h
//  News Article Classification
//
//  Created by Rahul Datta on 11/21/13.
//  Copyright (c) 2013 Rahul Datta. All rights reserved.
//

#ifndef __News_Article_Classification__Word__
#define __News_Article_Classification__Word__

#include <iostream>
#include <vector>
#include <string>
#define NUM_CLASSES 8
class Word{
private:
	char* mWord;
	float mNum;
public:
	
	Word();
	
	Word(char * word);
	
	inline char* getWord(){return mWord;}
	
	inline void setWord(char* string){ mWord = string;}
	
	inline void setNum(float n){ mNum += n;}
	
	inline float getNum(){ return mNum;}
};
#endif /* defined(__News_Article_Classification__Word__) */
