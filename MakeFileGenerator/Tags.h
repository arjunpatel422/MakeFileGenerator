/*
 * Tags.h
 *
 *  Created on: Mar 19, 2015
 *      Author: Arjun
 */

#ifndef TAGS_H_
#define TAGS_H_

typedef struct TagNames
{
    char* m_fields[6];
    int m_size;
}Tags;

struct WordStream* getTags(char* body,int size,char* openingTag,char* closingTag);

char* initializeOpeningTag(char* tagName);
char* initializeClosingTag(char* tagName);

void setTagNames(char** tagNames);
void setOpeningTags(Tags* openingTags,char** tagNames);
void setClosingTags(Tags* closingTags,char** tagNames);
void releaseTags(Tags* tags);

#endif /* TAGS_H_ */
