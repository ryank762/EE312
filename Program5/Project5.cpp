// Set <Project5.cpp>
// EE 312 Project 5 submission by
// Ryan Kim
// jk39938
// Slip days used: 0
// Summer 2018
// Copy-Paste the above lines at the top of your submitted files.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Set.h"

/*
 * Several of the required functions have been written already
 * You may use these functions as-is or you may modify them in any way. 
 * Please NOTE, you are responsible for ensuring that the functions work correctly in 
 * your project solution. Just because the function works correctly in my solution does 
 * NOT mean that the function will work correctly in yours. 
 */

/*
 * Design NOTES:
 *
 * The design provided in this starter kit assumes
 * (1) empty sets will be represented with length == 0 and elements == nullptr (i.e., address 0)
 * (2) amortized doubling is not used, and capacity is ignored/unused. Functions should assume that 
 * the amount of storage available in the elements[] array is equal to length
 */



/* done for you already */
void destroySet(Set* self) {
	free(self->elements);
}

/* done for you already */
void createEmptySet(Set* self) {
	self->len = 0;
	self->elements = 0;
}

/* done for you already */
void createSingletonSet(Set* self, int x) {
	self->elements = (int*) malloc(sizeof(int));
	self->elements[0] = x;
	self->len = 1;
}

/* done for you already */
void createCopySet(Set* self, const Set* other) {
	self->elements = (int*) malloc(other->len * sizeof(int));
	for (int k = 0; k < other->len; k += 1) {
		self->elements[k] = other->elements[k];
	}
	self->len = other->len;	
}

/* done for you already */
void assignSet(Set* self, const Set* other) {
	if (self == other) { return; }
	
	destroySet(self);
	createCopySet(self, other);
}

/* return true if x is an element of self */
bool isMemberSet(const Set* self, int x) {
	int start = 0;
	int end = self->len - 1;
	int mid = end / 2;

	if (self->len == 0) {
		return false;
	}

	while (start <= end) {
		if (x == self->elements[mid]) {
			return true;

		} else if (x > self->elements[mid]) {
			start = mid + 1;
			mid = (start + end) / 2;

		} else if (x < self->elements[mid]) {
			end = mid - 1;
			mid = (start + end) / 2;
		}
	}
	return false;
}

/*
 * add x as a new member to this set. 
 * If x is already a member, then self should not be changed
 * Be sure to restore the design invariant property that elemnts[] remains sorted
 * (yes, you can assume it is sorted when the function is called, that's what an invariant is all about)
 */
void insertSet(Set* self, int x) {
	if (isEmptySet(self)) {
		createSingletonSet(self, x);

	} else {
		if (!isMemberSet(self, x)) {
			int i, j;

			Set* tempArray = (Set*) malloc(sizeof(Set));
			tempArray->elements = (int*) malloc(sizeof(int) * (self->len + 1));
			tempArray->len = self->len + 1;

			for (i = 0; i < self->len && x > self->elements[i]; i++);
			for (j = 0; j < i; j++) {
				tempArray->elements[j] = self->elements[j];
			}
			tempArray->elements[i] = x;
			j++;
			for(j; j < self->len + 1; j++) {
				tempArray->elements[j] = self->elements[i];
				i++;
			}
			assignSet(self, tempArray);
			destroySet(tempArray);
			free(tempArray);

		}
	}
}


/*
 * don't forget: it is OK to try to remove an element
 * that is NOT in the set.  
 * If 'x' is not in the set 'self', then
 * removeSet should do nothing (it's not an error)
 * Otherwise, ('x' IS in the set), remove x. Be sure to update self->length
 * It is not necessary (nor recommended) to call malloc -- if removing an element means the 
 * array on the heap is "too big", that's almost certainly OK, and reallocating a smaller array 
 * is almost definitely NOT worth the trouble
 */
void removeSet(Set* self, int x) {
	if (isMemberSet(self, x)) {
		int i;

		self->len--;

		for (i = 0; self->elements[i] != x; i++);
		for (i; i < self->len; i++) {
			self->elements[i] = self->elements[i + 1];
		}
	}
}

/* done for you already */
void displaySet(const Set* self) {
	int k;
	
	printf("{");

	if (self->len == 0) { 
		printf("}"); 
	}
	else {
		for (k = 0; k < self->len; k += 1) {
			if (k < self->len - 1) {
				printf("%d,", self->elements[k]);
			} else {
				printf("%d}", self->elements[k]);
			}
		}
	}
}

/* return true if self and other have exactly the same elements */
bool isEqualToSet(const Set* self, const Set* other) {
	if (self->len != other->len) {
		return false;

	} else {
		for (int i = 0; i < self->len; i++) {
			if (self->elements[i] != other->elements[i]) {
				return false;
			}
		}
		return true;
	}
}

/* return true if every element of self is also an element of other */
bool isSubsetOf(const Set* self, const Set* other) {
	if (self->len == 0 && other->len == 0) {
		return true;

	} else if (self->len > other->len) {
		return false;

	} else {
		int i = 0, j = 0;
		while (i <= self->len && j <= other->len) {
			if (i == self->len) {
				return true;

			} else if (j == other->len) {
				return false;

			} else if (self->elements[i] == other->elements[j]) {
				i++; j++;

			} else if (self->elements[i] > other->elements[j]) {
				j++;
			} else if (self->elements[i] < other->elements[j]) {
				return false;

			}
		}
		return false;
	}
}

/* done for you */
bool isEmptySet(const Set* self) {
	return self->len == 0;
}

/* remove all elements from self that are not also elements of other */
void intersectFromSet(Set* self, const Set* other) {
	int i = 0, j = 0;
	Set* intersectionSet = (Set*) malloc(sizeof(Set));
	if (self->len >= other->len) {
		intersectionSet->elements = (int *) malloc(sizeof(int) * other->len);
	} else {
		intersectionSet->elements = (int *) malloc(sizeof(int) * self->len);
	}
	intersectionSet->len = 0;

	while (i < self->len && j < other->len) {
		if (self->elements[i] == other->elements[j]) {
			intersectionSet->elements[intersectionSet->len] = self->elements[i];
			i++; j++; intersectionSet->len++;

		} else if (self->elements[i] > other->elements[j]) {
			j++;

		} else if (self->elements[i] < other->elements[j]) {
			i++;

		}
	}

	assignSet(self, intersectionSet);
	destroySet(intersectionSet);
	free(intersectionSet);
}

/* remove all elements from self that are also elements of other */
void subtractFromSet(Set* self, const Set* other) {
	int i = 0, j = 0;

	if (!self->len || !other->len) {
		return;
	}

	Set *subtractionSet = (Set *) malloc(sizeof(Set));

	if (self->len >= other->len) {
		subtractionSet->elements = (int *) malloc(sizeof(int) * self->len);
	} else {
		subtractionSet->elements = (int *) malloc(sizeof(int) * other->len);
	}
	subtractionSet->len = 0;

	while (i < self->len && j <= other->len) {
		if (j == other->len) {
			while (i < self->len) {
				subtractionSet->elements[subtractionSet->len] = self->elements[i];
				i++;
				subtractionSet->len++;
			}
		} else if (self->elements[i] == other->elements[j]) {
			i++; j++;

		} else if (self->elements[i] > other->elements[j]) {
			j++;

		} else if (self->elements[i] < other->elements[j]) {
			subtractionSet->elements[subtractionSet->len] = self->elements[i];
			i++; subtractionSet->len++;

		}
	}

	assignSet(self, subtractionSet);
	destroySet(subtractionSet);
	free(subtractionSet);
}

/* add all elements of other to self (obviously, without creating duplicate elements) */
void unionInSet(Set* self, const Set* other) {
	int i = 0, j = 0;

	if (!other->len) {
		return;
	} else if (!self->len) {
		assignSet(self, other);
		return;
	}

	Set* unionSet = (Set*) malloc(sizeof(Set));
	unionSet->elements = (int*) malloc (sizeof(int) * (self->len + other->len));
	unionSet->len = 0;

	while (i < self->len && j <= other->len) {
		if (j == other->len) {
			while (i < self->len) {
				unionSet->elements[unionSet->len] = self->elements[i];
				i++;
				unionSet->len++;
			}
		} else if (self->elements[i] == other->elements[j]) {
			unionSet->elements[unionSet->len] = self->elements[i];
			i++; j++; unionSet->len++;

		} else if (self->elements[i] > other->elements[j]) {
			unionSet->elements[unionSet->len] = other->elements[j];
			j++; unionSet->len++;

		} else if (self->elements[i] < other->elements[j]) {
			unionSet->elements[unionSet->len] = self->elements[i];
			i++; unionSet->len++;

		}
	}
	if (i == self->len && j < other->len) {
		while (j < other->len) {
			unionSet->elements[unionSet->len] = other->elements[j];
			j++;
			unionSet->len++;
		}
	}

	assignSet(self, unionSet);
	destroySet(unionSet);
	free(unionSet);
}
