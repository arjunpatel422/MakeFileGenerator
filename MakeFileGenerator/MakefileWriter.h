//
//  FileWriter.h
//  MakeFileGenerator
//
//  Created by Arjun on 3/23/15.
//  Copyright (c) 2015 Arjun. All rights reserved.
//

#ifndef __MakeFileGenerator__FileWriter__
#define __MakeFileGenerator__FileWriter__

#include <stdio.h>
#include "WordStream.h"

void fixFields(WordStream** allFields);
void writeCompiler(WordStream** allFields,char** block,FILE* dstFile);
void writeFlags(WordStream** allFields,char** block,FILE* dstFile);
void writeExecutable(WordStream** allFields,char** block,FILE* dstFile);
void writeSources(WordStream** allFields,char** block,FILE* dstFile);
void writeObjects(WordStream** allFields,char** block,FILE* dstFile);
void writeProgram(WordStream** allFields,char** block,FILE* dstFile);
void writeDependencies(WordStream** allFields,char** block,FILE* dstFile);
void writeClean(WordStream** allFields,char** block,FILE* dstFile);
void writeToMakefile(WordStream** allFields,FILE* dstFile);

#endif /* defined(__MakeFileGenerator__FileWriter__) */
