#include <stdio.h>
#include <stdint.h>

int gcd (int x, int y);

int main() {
	int a, b;

	a = 48; b = 18;
	printf("GCD of %d and %d is: %d\n", a, b, gcd(a,b));

	a = 144; b = 60;
	printf("GCD of %d and %d is: %d\n", a, b, gcd(a,b));

	a = 65; b = 12;
	printf("GCD of %d and %d is: %d\n", a, b, gcd(a,b));

	a = 179; b = 7;
	printf("GCD of %d and %d is: %d\n", a, b, gcd(a,b));

	// *********** test cases ***********
	/*
	a = 1; b = 1;
	printf("GCD of %d and %d is: %d\n", a, b, gcd(a,b));

	a = 36; b = 36;
	printf("GCD of %d and %d is: %d\n", a, b, gcd(a,b));

	a = 8; b = 1;
	printf("GCD of %d and %d is: %d\n", a, b, gcd(a,b));

	a = 7; b = 1;
	printf("GCD of %d and %d is: %d\n", a, b, gcd(a,b));

	a = 2; b = 3;
	printf("GCD of %d and %d is: %d\n", a, b, gcd(a,b));

	a = 36; b = 24;
	printf("GCD of %d and %d is: %d\n", a, b, gcd(a,b));

	a = 1500; b = 128;
	printf("GCD of %d and %d is: %d\n", a, b, gcd(a,b));

	a = 128; b = 64;
	printf("GCD of %d and %d is: %d\n", a, b, gcd(a,b));
	 */

	return 0;
}


int gcd(int x, int y) {                 // recursive function inspired by the Euclidean algorithm
	int quo;
	for (quo = 0; x >= y; quo++) {
		x -= y;
	}                                   // x becomes remainder after executing for-loop
	if (!x) {
		return y;
	} else {
		gcd(y, x);                      // perform Euclidean algorithm again, but with divisor and remainder as inputs
	}
}
