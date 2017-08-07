/*
 * WordStream.cpp
 *
 *  Created on: Mar 20, 2015
 *      Author: Arjun
 */
#include "Globals.h"
#include "WordStream.h"
#include "Buffer.h"

void initializeWordStream(WordStream* wordStream)
{
	wordStream->m_head=(WordNode*)malloc(sizeof(WordNode));
    wordStream->m_head->m_word=NULL;
    wordStream->m_head->m_next=NULL;
	wordStream->m_size=0;
	wordStream->m_tail=wordStream->m_head;
}

void addWord(WordStream* wordStream,char* word)
{
	WordNode* temp=(WordNode*)malloc(sizeof(WordNode));
	temp->m_word=copyString(word);
	temp->m_next=NULL;
	wordStream->m_tail->m_next=temp;
	wordStream->m_tail=temp;
	wordStream->m_size+=1;
}

void addBufferToWordStream(WordStream* wordStream,struct Buffer* buffer)
{
	addWord(wordStream,buffer->m_word);
}

char* getWord(WordStream* wordStream,int position)
{
	if(position>=wordStream->m_size)
			return NULL;
	WordNode* current=wordStream->m_head->m_next;
	int index;
	for(index=0;index!=position;index++)
	{
		current=current->m_next;
	}
	return(current!=NULL?current->m_word:NULL);
}

void setWord(WordStream* wordStream,int position,char* word)
{
    if(position>=wordStream->m_size)
        return;
    WordNode* current=wordStream->m_head->m_next;
    int index;
    for(index=0;index!=position;index++)
    {
        current=current->m_next;
    }
    safeFree(current->m_word);
    current->m_word=copyString(word);
}

void removeWord(WordStream* wordStream,int position)
{
	if(position>=wordStream->m_size)
		return;
	WordNode* previous=wordStream->m_head;
	WordNode* temp=previous->m_next;
	int index;
	for(index=0;index!=position;index++)
	{
		previous=temp;
		temp=temp->m_next;
	}
	previous->m_next=temp->m_next;
	position++;
	if(position==wordStream->m_size)
		wordStream->m_tail=temp->m_next;
	if(position==1)
		wordStream->m_tail=wordStream->m_head;
	safeFree(temp->m_word);
	safeFree(temp);
}

void printWordStream(WordStream* wordStream)
{
	WordNode* current=wordStream->m_head->m_next;
	while(current!=NULL)
	{
		printf("%s\n",current->m_word);
		current=current->m_next;
	}
}

void freeWordStream(WordStream* wordStream)
{
    if(wordStream==NULL)
        return;
    wordStream->m_size=0;
    while(wordStream->m_head!=NULL)
    {
        wordStream->m_tail=wordStream->m_head->m_next;
        safeFree(wordStream->m_head->m_word);
        safeFree(wordStream->m_head);
        wordStream->m_head=wordStream->m_tail;
    }
}
