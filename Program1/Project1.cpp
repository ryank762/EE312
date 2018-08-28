/*
 * Project1.cpp
 * 
 * Name: Ryan Kim
 * EE312 Summer 2018
 * SpellCheck
 * Slip days used: <1>          (I'm using a slip day on this assignment)
 */

#include <stdio.h> // provides declarations for printf and putchar
#include <stdint.h> // provides declarations for int32_t uint32_t and the other (new) standard C types

/* All of your code must be in this file. Please no #includes other than standard system headers (ie.., stdio.h, stdint.h)
 *
 * Many students find it helpful to declare global variables (often arrays). You are welcome to use
 * globals if you find them helfpul. Global variables are by no means necessary for this project.
 */

/* You must write this function (spellCheck). Do not change the way the function is declared (i.e., it has
 * exactly two parameters, each parameter is a standard (mundane) C string (see SpellCheck.pdf).
 * You are expected to use reasonable programming style. I *insist* that you indent
 * reasonably and consistently in your code. I strongly encourage you to avoid big functions
 * So, plan on implementing spellCheck by writing two or three other "support functions" that
 * help make the actual spell checking easier for you.
 * There are no explicit restictions on using functions from the C standard library. However,
 * for this project you should avoid using functionality from the C++ standard libary. You will
 * almost certainly find it easiest to just write everything you need from scratch!
 */

int isInDictionary(char artWord[], char searchDict[]);                  // checks if artWord is in searchDict
int isALetter(char character);                                          // checks if character is an alphabetical letter
int isSameLetter(char letter1, char letter2);                           // checks for capitalization

void spellCheck(char article[], char dictionary[]) {
	int i, j,tempI, wordLength;
	for (i = 0; article[i]; i++) {
		wordLength = 0;
		if (isALetter(article[i])) {                                    // searches article for letter
			for (tempI = i; isALetter(article[tempI]); tempI++) {
				wordLength++;                                           // find word length to allocate memory
			}
			if (wordLength == 1) {
				continue;
			}
			char articleWord[wordLength + 1];                           // allocate array (string)
			for (j = 0; j < wordLength; j++) {
				articleWord[j] = article[i];
				i++;
			}
			articleWord[j] = 0;
			if (!isInDictionary(articleWord, dictionary)) {
				printf("%s\n", articleWord);                            // prints to console of word is not in dict
			}
			if (!article[i]) {                                          // end for-loop if article ends
				break;
			}
		}
	}
}

int isInDictionary(char artWord[], char searchDict[]) {                 // return 1 if word is found in dictionary, 0 else
	int i, j, iSave;
	for (i = 0; searchDict[i]; i++) {
		iSave = i;
		j = 0;
		if (isSameLetter(searchDict[i], artWord[j])) {                  // find first common letter
			if (!iSave || searchDict[iSave-1] == '\n') {
				iSave++; j++;
				while (isSameLetter(searchDict[iSave], artWord[j])) {   // do-while loop to navigate through dictionary
					iSave++; j++;
				}
				if (!isALetter(artWord[j]) && (searchDict[iSave] == '\n') || (searchDict[iSave] == '\0')) {
					return 1;                                           // returns 1 if word in article ends, and word in dictionary ends
				}
			}
		}
	}
	return 0;                                                           // not in dictionary
}

int isALetter(char character) {                                         // return 1 if character is a letter, 0 else
	if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z')) {
		return 1;
	}
	else {
		return 0;
	}
}

int isSameLetter(char letter1, char letter2) {                          // return 1 if character is same (capital of another), 0 else
	if (letter1 == 0 || letter2 == 0) {
		return 0;
	}
	if (isALetter(letter1) && isALetter(letter2)) {
		if (letter1 == letter2) {                       // same letter
			return 1;
		} else if (letter1 == letter2 - 32) {           // lower case vs upper case
			return 1;
		} else if (letter1 == letter2 + 32) {           // upper case vs lower case
			return 1;
		}
	}
	return 0;
}
