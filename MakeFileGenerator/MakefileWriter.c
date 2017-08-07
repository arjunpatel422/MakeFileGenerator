//
//  FileWriter.c
//  MakeFileGenerator
//
//  Created by Arjun on 3/23/15.
//  Copyright (c) 2015 Arjun. All rights reserved.
//

#if defined (_WIN32) || defined(_WIN64)
const char line='\r';
#
#else
const char line='\n';
#endif

#include "Globals.h"
#include "MakefileWriter.h"

void fixFields(WordStream** allFields)
{
    int position=0;
    int firstDot; //finds first dot
    int fileExtension; //finds first file extension's dot
    WordNode* iterator=NULL; //declares it for later
    WordStream* currentField=allFields[position++];//starts by fixing the language
    if(currentField->m_size<0) //this means no language tag was entered
        addWord(currentField,"C++");
    char* check=getWord(currentField,0);
    if(strcmp(check,"C")!=0 || strcmp(check,"C++"))
        setWord(currentField,0,"C++");
    currentField=allFields[position];
    iterator=currentField->m_head->m_next; //made to allow better access for setting elements
    //having an order N instead of N^2 to use sequential access
    while(iterator!=NULL)
    {
        check=iterator->m_word;
        firstDot=findSubstring(check,".",0);
        fileExtension=(firstDot>-1?findSubstring(check,".h",firstDot):-1);
        if(firstDot==-1 || fileExtension!=firstDot || check[fileExtension+1]!='\0')
        {
            printf("%s has incorrect format because it lacks a .h extension or has multiple extensions. The file extension will forcibly be changed to a .h in the Makefile",iterator->m_word);
            if(firstDot>-1)
            {
                firstDot++;
                check=initializeCharPtr(firstDot+1); //allocates enough memory to insert the null byte
                memcpy(check,iterator->m_word,firstDot); //copies known correct part of string over
            }
            else
            {
                firstDot=strlen(check);//gets length of the string
                check=initializeCharPtr(firstDot+3); //allocates enough memory for null byte and .h
                memcpy(check,iterator->m_word,firstDot); //copies everything in the string
                check[firstDot++]='.';//puts the .
                check[firstDot++]='h';//puts the h
            }
            check[firstDot]='\0'; //sets the null byte
            safeFree(iterator->m_word); //releases current word b/c it is no longer needed
            iterator->m_word=check; //sets the word to the correct word
            iterator=iterator->m_next;//increments the iterator
        }
    }

}

// position 0:language 1:compiler 2:headers 3:source files 4:flags 5:executable

void writeToMakefile(WordStream** allFields,FILE* dstFile)
{
    //fixFields(allFields);
    char** block=NULL;
    writeCompiler(allFields,block,dstFile);
    writeFlags(allFields,block,dstFile);
    writeExecutable(allFields,block,dstFile);
    writeSources(allFields,block,dstFile);
    writeObjects(allFields,block,dstFile);
    writeProgram(allFields,block,dstFile);
    writeDependencies(allFields,block,dstFile);
    writeClean(allFields,block,dstFile);
}

void writeCompiler(WordStream** allFields,char** block,FILE* dstFile)
{
    int blockSize=3;
    block=initializeBlock(blockSize);
    block[0]="COMPILER=";
    if(allFields[1]->m_size>0)
        block[1]=getWord(allFields[1],0);
    else if(strcmp(allFields[0]->m_head->m_word,"C"))
        block[1]="gcc";
    else
        block[1]="g++";
    block[2]=(line=='\r'?"\r":"\n");
    writeBlock(block,blockSize,dstFile);
    safeFree(block);
}

void writeFlags(WordStream** allFields,char** block,FILE* dstFile)
{
    int blockSize=allFields[4]->m_size*2;
    if(blockSize==0)
    {
        char* tmp[1];
        tmp[0]=(line=='\r'?"\r":"\n");
        writeBlock(tmp,1,dstFile);
        return;
    }
    char* space=" ";
    blockSize+=2;
    block=initializeBlock(blockSize);
    block[0]="FLAGS="; //writes the flags variable out
    int position=1;
    WordNode* iterator=allFields[4]->m_head->m_next; //goes through each flag in the wordstream
    while(iterator!=NULL) //uses the iterator for simplicity in checking whether it is done writing
    {
        block[position++]=space; //creates a space
        block[position++]=iterator->m_word;
        iterator=iterator->m_next;
    }
    block[blockSize-1]=(line=='\r'?"\r\r":"\n\n");
    writeBlock(block,blockSize,dstFile);
    safeFree(block);
}


void writeExecutable(WordStream** allFields,char** block,FILE* dstFile)
{
    int blockSize=3;
    if(allFields[5]->m_size!=1)
        return;
    block=initializeBlock(blockSize);
    block[0]="all: ";
    block[1]=getWord(allFields[5],0);
    block[2]=(line=='\r'?"\r\r":"\n\n");
    writeBlock(block,blockSize,dstFile);
    safeFree(block);
}

void writeSources(WordStream** allFields,char** block,FILE* dstFile)
{
    int blockSize=1+2*allFields[3]->m_size;
    block=initializeBlock(blockSize);
    char* backslashNewline=(line=='\r'?"\\\r":"\\\n");
    WordNode* iterator=allFields[3]->m_head->m_next; //goes through each flag in the wordstream
    int position=0;
    block[position++]=(line=='\r'?"SOURCES=\\\r":"SOURCES=\\\n");
    while(iterator!=NULL) //uses the iterator for simplicity in checking whether it is done writing
    {
        block[position++]=iterator->m_word;
        block[position++]=backslashNewline; //creates a backslash on a newline
        iterator=iterator->m_next;
    }
    block[blockSize-1]=(line=='\r'?"\r\r":"\n\n");
    writeBlock(block,blockSize,dstFile);
    safeFree(block);
}

void writeObjects(WordStream** allFields,char** block,FILE* dstFile)
{
    int blockSize=2;
    block=initializeBlock(blockSize);
    block[0]=(strcmp(allFields[0]->m_head->m_next->m_word,"C")?"OBJECTS = $(subst .c,.o,$(SOURCES))":
    "OBJECTS = $(subst .cpp,.o,$(SOURCES))");
    block[1]=(line=='\r'?"\r\r":"\n\n");
    writeBlock(block,blockSize,dstFile);
    safeFree(block);
}

void writeProgram(WordStream** allFields,char** block,FILE* dstFile)
{
    int blockSize=2;
    block=initializeBlock(blockSize);
    block[0]=allFields[5]->m_head->m_next->m_word;
    if(allFields[4]->m_size>0)
        block[1]=(line=='\r'?": $(OBJECTS)\r$(COMPILER) $(FLAGS) -o $@ $(OBJECTS)\r\r":
                  ": $(OBJECTS)\n$(COMPILER) $(FLAGS) -o $@ $(OBJECTS)\n\n");
    else
        block[1]=(line=='\r'?": $(OBJECTS)\r$(COMPILER) -o $@ $(OBJECTS)\r\r":
                  ": $(OBJECTS)\n$(COMPILER) -o $@ $(OBJECTS)\n\n");
    writeBlock(block,blockSize,dstFile);
    safeFree(block);
}

void writeDependencies(WordStream** allFields,char** block,FILE* dstFile)
{
    int blockSize=2*allFields[2]->m_size;
    if(blockSize<1)
    {
        char* tmp[1];
        tmp[0]=(line=='\r'?"\r":"\n");
        writeBlock(tmp,1,dstFile);
        return;
    }
    char* newLine=(line=='\r'?"\r":"\n");
    block=initializeBlock(blockSize);
    int position=0;
    WordNode* iterator=allFields[2]->m_head->m_next;
    while(iterator!=NULL) //uses the iterator for simplicity in checking whether it is done writing
    {
        block[position++]=iterator->m_word;
        block[position++]=newLine; //creates a backslash on a newline
        iterator=iterator->m_next;
    }
    block[blockSize-1]=(line=='\r'?"\r\r":"\n\n");
    writeBlock(block,blockSize,dstFile);
    safeFree(block);
}

void writeClean(WordStream** allFields,char** block,FILE* dstFile)
{
    int blockSize=2;
    block=initializeBlock(blockSize);
    block[0]=(line=='\r'?"clean:\rrm -fr *.o *~ *.core *.tmp ":"clean:\nrm -fr *.o *~ *.core *.tmp ");
    block[1]=allFields[5]->m_head->m_next->m_word;
    writeBlock(block,blockSize,dstFile);
    safeFree(block);
}