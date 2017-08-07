/*
 * WordStream.h
 *
 *  Created on: Mar 20, 2015
 *      Author: Arjun
 */

#ifndef WORDSTREAM_H_
#define WORDSTREAM_H_

#include "Buffer.h"

typedef struct WordNode
{
	char* m_word;
	struct WordNode* m_next;
}WordNode;

typedef struct WordStream
{
	WordNode* m_head;
	int m_size;
	WordNode* m_tail;
}WordStream;

void initializeWordStream(WordStream* wordStream);
void addWord(WordStream* wordStream,char* word);
void addBufferToWordStream(WordStream* wordStream,Buffer* buffer);
char* getWord(WordStream* wordStream,int position);
void setWord(WordStream* wordStream,int position,char* word);
void removeWord(WordStream* wordStream,int position);
void printWordStream(WordStream* wordStream);
void freeWordStream(WordStream* wordStream);

#endif /* WORDSTREAM_H_ */
