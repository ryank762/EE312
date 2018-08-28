// String ADT Project3.cpp
// EE 312 Project 3 submission by
// Ryan Kim
// jk39938
// Slip days used: 0
// Summer 2018

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "String.h"

#define SIGNATURE (~0xdeadbeef)

/*
 * Helper macro to find the signature of a UTString
 * Treat this like a function that takes a UTString*
 * Accesses a uint32_t from where the signature should be located
 */
#define CHECK(s) (*(uint32_t*) ((s)->string + (s)->length + 1))

/*
 * Checks if a UTString is valid or not.
 */
bool isOurs(const UTString* s) {
    if (CHECK(s) == SIGNATURE) { return true; }
    else { return false; }
}

/* 
 * Allocate a utstring on the heap. 
 * Initialize the string correctly by copying src.
 * Return a pointer to the UTString.
 */
UTString* utstrdup(const char* src) {
	UTString* newStr = (UTString*) malloc(2*sizeof(int) + sizeof(char*));

	newStr->length = (int) strlen(src);
	newStr->capacity = (int) strlen(src);

	newStr->string = (char*) malloc(newStr->capacity + 1 + sizeof(SIGNATURE));
	char* strSave = newStr->string;
	while (*src) {
		*(newStr->string) = *src;
		(newStr->string)++;
		src++;
	}
	*newStr->string = '\0';
	newStr->string = strSave;

	int sig = SIGNATURE;
	memcpy(&newStr->string[newStr->length + 1], &sig, 4);  // copy sig over to the correct place.

	return newStr;
}

/* 
 * Returns the length of s.
 *  s must be a valid UTString.
 */
uint32_t utstrlen(const UTString* s) {
	assert(isOurs(s));

	UTString* sTemp = (UTString*) s;
	uint32_t length = 0;
	while (*(sTemp->string)) {
		sTemp->string++;
		length++;
	}

	return length;
}

/*
 * Append the string suffix to the UTString s.
 *  s must be a valid UTString.
 * Do not allocate any additional storage: only append as many characters
 *  as will actually fit in s. 
 * Update the length of s.
 * Return s with the above changes. */
UTString* utstrcat(UTString* s, const char* suffix) {
	assert(isOurs(s));
	char* strSave = s->string;

	s->string += s->length;
	while (*suffix && (s->length < s->capacity)) {
		*(s->string) = *suffix;
		s->string++; suffix++; s->length++;
	}
	*(s->string) = '\0';
	s->string = strSave;

	int sig = SIGNATURE;
	memcpy(&s->string[s->length + 1], &sig, 4);  // copy sig over to the correct place.

	return s;
}

/* 
 * Copy src into dst.
 *  dst must be a valid UTString. 
 *  src is an ordinary string.
 * Do not allocate any additional storage: only copy as many characters
 *  as will actually fit in dst.
 * Update the length of dst. 
 * Return dst with the above changes.
 */
UTString* utstrcpy(UTString* dst, const char* src) {
	assert(isOurs(dst));

	uint32_t i;
	char* dstStrSave = dst->string;

	for (i = 0; (*src) && (i < dst->capacity); i++) {
		*(dst->string) = *src;
		(dst->string)++;
		src++;
	}
	*(dst->string) = '\0';
	dst->string = dstStrSave;
	dst->length = i;

	int sig = SIGNATURE;
	memcpy(&dst->string[dst->length + 1], &sig, 4);  // copy sig over to the correct place.

//	dst->length = utstrlen(dst);

	return dst;
}

/*
 * Free all memory associated with the given UTString. 
 */
void utstrfree(UTString* self) {
	assert(isOurs(self));

	free(self->string);
	free(self);

}

/* 
 * Make s have at least as much capacity as new_capacity.
 *  s must be a valid UTString.
 * If s has enough capacity already, do nothing.
 * If s does not have enough capacity, then allocate enough capacity, 
 *  copy the old string and the null terminator, free the old string,
 *  and update all relevant metadata. 
 * Return s with the above changes.
 */
UTString* utstrrealloc(UTString* s, uint32_t new_capacity) {
	assert(isOurs(s));

	UTString* reUT;

	if (s->capacity < new_capacity) {
		reUT = (UTString*) malloc(2*sizeof(int) + sizeof(char*));
		reUT->length = 0;
		reUT->capacity = new_capacity;
		reUT->string = (char*) malloc(reUT->capacity + 1 + sizeof(SIGNATURE));

		char* tempStr1 = reUT->string;
		char* tempStr2 = s->string;
		while (*tempStr2) {
			*tempStr1 = *tempStr2;
			tempStr1++; tempStr2++;
			reUT->length++;
		}
		*tempStr1 = '\0';

		int sig = SIGNATURE;
		memcpy(&reUT->string[reUT->length + 1], &sig, 4);  // copy sig over to the correct place.

		utstrfree(s);

		return reUT;
	} else {
		return s;
	}
}
