#include "Globals.h"
#include "Buffer.h"

void initializeBuffer(Buffer* buffer)
{
	buffer->m_position=0;
	buffer->m_word=initializeCharPtr(20);
	buffer->m_size=20;
}

void addCharacterToBuffer(Buffer* buffer,char value)
{
  if(buffer->m_position==buffer->m_size)
	  resizeBuffer(buffer);
  buffer->m_word[buffer->m_position]=value;
  buffer->m_position++;
}

void resizeBuffer(Buffer* buffer)
{
	buffer->m_size*=2;
	buffer->m_word=(char*)realloc(buffer->m_word,buffer->m_size);
}

char* convertBufferToWord(Buffer* buffer)
{
	return copyString(buffer->m_word);
}

void freeBuffer(Buffer* buffer)
{
	if(buffer==NULL)
		return;
	buffer->m_position=0;
	buffer->m_size=0;
	safeFree(buffer->m_word);
}

void resetBuffer(Buffer* buffer)
{
	buffer->m_position=0;
	memset(buffer,'\0',buffer->m_size);
}
