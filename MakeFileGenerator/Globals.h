/*
 * Globals.h
 *
 *  Created on: Mar 19, 2015
 *      Author: Arjun
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

typedef unsigned char byte;

int exitProgram(char* message,int exitCode);
char* initializeCharPtr(int size);
char** initializeBlock(int size);
char* createLimitedCharPtr(int size);
char** createLimitedBlock(int size);
void resizeCharPtr(char** dst,int size);
void resizeBlock(char*** dst,int size);
char* copyString(char*src);
int findSubstring(const char* haystack,const char* needle,int offset);//offset should be positive from haystack
void writeBlock(char** block,int blockSize,FILE* dstFile);
void safeFree(void* ptr);

#endif /* GLOBALS_H_ */
