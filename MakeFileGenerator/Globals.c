#include "Globals.h"

int exitProgram(char* message,int exitCode)
{
	printf("%s\n",message);
	exit(exitCode);
}

/*
 * Globals.c
 *
 *  Created on: Mar 19, 2015
 *      Author: Arjun
 */
char* initializeCharPtr(int size)
{
	return (char*)malloc(sizeof(char)*size);
}

char* createLimitedCharPtr(int size)
{
    char*dst=(char*)malloc(sizeof(char)*(size+1));
    dst[size]='\0';
    return dst;
}

char** initializeBlock(int size)
{
    char**dst=(char**)malloc(sizeof(char*)*(size+1));
    dst[size]=NULL;
    return dst;
}

char** createdLimitedBlock(int size)
{
    char** dst=(char**)malloc(sizeof(char*)*size+1);
    dst[size]=NULL;
    return dst;
}

void resizeCharPtr(char** dst,int size)
{
	dst[0]=(char*)realloc(dst[0],size+1);
	dst[0][size]='\0';
}

void resizeBlock(char*** dst,int size)
{
    dst[0]=(char**)realloc(dst[0],size);
    dst[0][size-1]='\0';
}

char* copyString(char*src)
{
	int size=strlen(src)+1; //gets size of word
	char* dst=initializeCharPtr(size);
	size--;
	memcpy(dst,src,size);
	dst[size]='\0';
	return dst;
}

int findSubstring(const char* haystack,const char* needle,int offset) //returns position of first matching character
{
	if(needle==NULL || haystack==NULL ||offset<0) //NULL should not work. offset should not be negative
		return -1;
	int haystackSize=strlen(haystack); //calculates size of the haystack
	int needleSize=strlen(needle);//calculates size of needle
	int searchLimit=haystackSize-needleSize-offset; //determines if there is a point in searching
	if(searchLimit<needleSize) //if needle is larger, nothing to search
			return -1;
	int haystackPosition; //used to navigate through haystack
	int searchPosition; //used to check for the substring
	int needlePosition; //used to check through the substring
	for(haystackPosition=offset;searchLimit>-1;haystackPosition++,searchLimit--)
	{
		if(haystack[haystackPosition]==needle[0]) //if initial character matches,search for substring
		{
			searchPosition=haystackPosition;//begins checking for substring
			needlePosition=0;//resets needle position to search from the beginning
			while(needle[needlePosition]!='\0' && searchPosition<haystackSize) //searches for the end of the substring using the null byte
			{
				if(haystack[searchPosition++]!=needle[needlePosition++]) //character doesn't match so break
					break;
			}
			if(needlePosition==needleSize)//this means the entire substring was found
				return haystackPosition;//returns where the start of the substring can be found
		}
	}
	return -1;
}

void writeBlock(char** block,int blockSize,FILE* dstFile)
{
    int position;
    char* word;
    for(position=0;position<blockSize;position++)
    {
        word=block[position];
        fwrite(word,1,strlen(word),dstFile);
    }
}

void safeFree(void* ptr)
{
	if(ptr!=NULL)
		free(ptr);
    ptr=NULL;
}
