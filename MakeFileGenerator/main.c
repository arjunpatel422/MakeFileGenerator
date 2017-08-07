#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "Globals.h"
#include "Tags.h"
#include "WordStream.h"
#include "Buffer.h"
#include "MakefileWriter.h"

int main(int argc, char* args[])
{
	if(argc<2)
		exitProgram("This requires a file as input to generate the makefile",1);
    FILE* srcFile;
    FILE* dstFile;
	char* inputFileName=args[1];
	int position,fileSize;
	struct stat fileInput;
	int fileDescriptor=open(inputFileName,O_RDONLY);
	if(fileDescriptor==-1)
		exitProgram("The file could not be found or is not readable",2);
	srcFile=fdopen(fileDescriptor,"r");
	if(fstat(fileDescriptor,&fileInput)==-1)
		exitProgram("There was a problem getting the file information",3);
    WordStream** allFields;
	char* body=initializeCharPtr(fileInput.st_size);
	srcFile=fdopen(fileDescriptor,"r");
	fread(body,fileInput.st_size,1,srcFile);
    fileSize=fileInput.st_size;
    fclose(srcFile);
	char* tagNames[7];
    setTagNames(tagNames);
    Tags openingTags,closingTags;
    setOpeningTags(&openingTags,&tagNames);
    setClosingTags(&closingTags,&tagNames);
    allFields=malloc( sizeof(WordStream*)*6);
    for(position=0;position<openingTags.m_size;position++)
    {
        allFields[position]=getTags(body,fileSize,openingTags.m_fields[position],closingTags.m_fields[position]);
    }
    releaseTags(&openingTags);
    releaseTags(&closingTags);
    safeFree(body);
    for(position=0;position<openingTags.m_size;position++)
        printWordStream(allFields[position]);
    dstFile=fopen("Makefile","w");
    writeToMakefile(allFields,dstFile);
    fclose(dstFile);
    for(position=0;position<openingTags.m_size;position++)
    {
        freeWordStream(allFields[position]);
        safeFree(allFields[position]);
    }
    safeFree(allFields);
    return 0;
}
