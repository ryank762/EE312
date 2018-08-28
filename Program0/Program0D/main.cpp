#include <stdio.h>

void printMultTableInt(int n);
void printMultTableFrac(int n);

int main(void){

	// You can change this to test your code
	int size = 10;

	printMultTableInt(size);
	printMultTableFrac(size);

	return 0;

}

// Prints multiplication table of integers from 1 to n
void printMultTableInt(int n){
	int i,j;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			printf("%d ", i*j);             // prints product of row and column for each (i,j) entry
		}
		printf("\n");                       // new line for new row
	}
	printf("\n");                           // new line to finish printMultTableInt
}

// Prints multiplication table for fractions from 1, 1/2, 1/3 to 1/n
void printMultTableFrac(int n){
	double i,j;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			printf("%0.2f ", 1/(i*j));      // prints multiplicative inverse of the product of row and column
		}
		printf("\n");                       // new line for new row
	}
	printf("\n" );                          // new lien to finish printMultTableFrac
}