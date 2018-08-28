#include <stdio.h>
#include <assert.h>

#define SIZE 26

int are_anagrams(char[], char[]);

int main() {
	printf("running test 'iceman' and 'cinema'...\n");
	char iceman[] = "iceman";
	char cinema[] = "cinema";

	assert(are_anagrams(iceman, cinema));
	printf("passed!\n");

	printf("running test 'raganam' and 'anagram'...\n");
	char raganam[] = "raganam";
	char anagram[] = "anagram";

	assert(are_anagrams(raganam, anagram));
	printf("passed!\n");

	printf("running test 'listen' and 'silent'...\n");
	char listen[] = "listen";
	char silent[] = "silent";

	assert(are_anagrams(listen, silent));
	printf("passed!\n");

	printf("running test 'mole' and 'meal'...\n");
	char mole[] = "mole";
	char meal[] = "meal";

	assert(!are_anagrams(mole, meal));
	printf("passed!\n");

	printf("running test 'happy' and 'sad'...\n");
	char happy[] = "happy";
	char sad[] = "sad";

	assert(!are_anagrams(happy, sad));
	printf("passed!\n");

	// ********** test cases ************
	/*
	printf("running test 'mold' and 'molt'...\n");
	char mold[] = "mole";
	char molt[] = "molt";

	assert(!are_anagrams(mold, molt));
	printf("passed!\n");

	printf("running test 'empty1' and 'empty2'...\n");
	char empty1[] = "";
	char empty2[] = "";

	assert(are_anagrams(empty1, empty2));
	printf("passed!\n");

	printf("running test 'space1' and 'space2'...\n");
	char space1[] = " ";
	char space2[] = " ";

	assert(are_anagrams(space1, space2));
	printf("passed!\n");

	printf("running test 'a1' and 'a2'...\n");
	char a1[] = "a";
	char a2[] = "a";

	assert(are_anagrams(a1, a2));
	printf("passed!\n");

	printf("running test 'candy' and 'frying'...\n");
	char candy[] = "candy";
	char frying[] = "frying";

	assert(!are_anagrams(candy, frying));
	printf("passed!\n");
	 */
}

int string_length(char string[]) {                  // returns length of a string
	int length = 0;
	int i;

	for (i = 0; (string[i] >= 'a') && (string[i] <= 'z'); i++)  {   // assuming only lowercase letters
		length++;
	}
	return length;
}

void copy_string(char *copy, char *source) {        // creates a copy of source string
	while (*source != 0) {
		*copy = *source;
		copy++; source++;
	}
	*copy = 0;
}

int are_anagrams(char first_word[], char second_word[]) {       // checks if two lowercase strings are anagrams
	char temp;                      // temporary variable that is used to swap elements in a string
	char sortStr[SIZE] = "";        // initially empty string that we will sort
	int i, j;                       // index variables
	if (string_length(first_word) != string_length(second_word)) {
		return 0;                   // not an anagram if letter count is different
	}
	else {
		copy_string(sortStr, second_word);
		for (i = 0; i < string_length(first_word); i++) {
			for (j = i; j < string_length(first_word); j++) {
				if (first_word[i] == sortStr[j]) {      // sorts string and to construct first_word from second_word
					if (i != j) {
						temp = sortStr[i];
						sortStr[i] = sortStr[j];
						sortStr[j] = temp;
					}
					break;
				}
			}
			if (j == string_length(first_word)) {       // not an anagram if letter in first_word is not found in
				return 0;                               //      second word
			}
		}
		return 1;                                       // is an anagram if no negative conditions are passed
	}
}