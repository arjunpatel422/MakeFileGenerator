#include "Globals.h"
#include "Tags.h"
#include "WordStream.h"
#include "Buffer.h"

const char tagStart='<';
const char tagClose='>';
const char closingTagMark='/';

void setTagNames(char** tagNames)
{
    int position=0;
    tagNames[position++]="Language"; //position 0
    tagNames[position++]="Compiler"; //position 1
    tagNames[position++]="Dependency"; //position 2
	tagNames[position++]="Source"; //position 3
	tagNames[position++]="Flag"; //position 4
	tagNames[position++]="Executable"; //position 5
    tagNames[position]=NULL;
}

char* initializeOpeningTag(char*tagName)
{
	int size=strlen(tagName); //gets size of word
	char* dst=initializeCharPtr(size+3); //initializes ptr
	dst[0]=tagStart;
	memcpy(dst+1,tagName,size); //copies the bytes over
	size++;
	dst[size]=tagClose;
	size++;
	dst[size]='\0'; //sets the null byte
	return dst;
}

char* initializeClosingTag(char*tagName)
{
	int size=strlen(tagName); //gets size of word
	char* dst=initializeCharPtr(size+4); //initializes ptr
	dst[0]=tagStart;
	dst[1]=closingTagMark;
	memcpy(dst+2,tagName,size); //copies the bytes over
	size+=2;
	dst[size]=tagClose;
	size++;
	dst[size]='\0'; //sets the null byte
	return dst;
}

void setOpeningTags(Tags* openingTags,char** tagNames)
{
    int position;
    for(position=0;tagNames[position]!=NULL;position++)
        openingTags->m_fields[position]=initializeOpeningTag(tagNames[position]);
    openingTags->m_size=position;
}

void setClosingTags(Tags* closingTags,char** tagNames)
{
    int position;
    for(position=0;tagNames[position]!=NULL;position++)
        closingTags->m_fields[position]=initializeClosingTag(tagNames[position]);
    closingTags->m_size=position;
}

void releaseTags(Tags* tags)
{
    int position;
    for(position=0;position<tags->m_size;position++)
        safeFree(tags->m_fields[position]);
}

WordStream * getTags(char* body,int size,char* openingTag,char* closingTag)
{
	WordStream* wordStream=(WordStream*)malloc(sizeof(WordStream));
	initializeWordStream(wordStream);
	int position=0;
	Buffer buffer;
    initializeBuffer(&buffer);
	int tagClose;
	char value;
	int openingTagLength=strlen(openingTag);
	int closingTagLength=strlen(closingTag);
	while(position<size)
	{
		resetBuffer(&buffer);
		position=findSubstring(body,openingTag,position);
		if(position==-1)
			break;
		position+=openingTagLength;
		tagClose=findSubstring(body,closingTag,position);
		if(tagClose==-1)
		{
			printf("The following Tag could not be resolved: %s\n",closingTag);
			exit(5);
		}
		while(position<tagClose)
		{
			value=body[position];
			if(value!='\r' && value!='\n')
				addCharacterToBuffer(&buffer,value);
			position++;
		}
        if(buffer.m_position>0)
            addBufferToWordStream(wordStream,&buffer);
		position+=closingTagLength;
	}
    freeBuffer(&buffer);
	return wordStream;
}
