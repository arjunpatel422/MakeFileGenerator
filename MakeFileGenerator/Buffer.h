/*
 * Buffer.h
 *
 *  Created on: Mar 21, 2015
 *      Author: Arjun
 */

#ifndef BUFFER_H_
#define BUFFER_H_

typedef struct Buffer
{
	int m_size;
	char* m_word;
	int m_position;
}Buffer;

void initializeBuffer(Buffer* buffer);
void addCharacterToBuffer(Buffer* buffer,char value);
void resizeBuffer(Buffer* buffer);
char* convertBufferToWord(Buffer* buffer);
void freeBuffer(Buffer* buffer);
void resetBuffer(Buffer* buffer);

#endif /* BUFFER_H_ */
