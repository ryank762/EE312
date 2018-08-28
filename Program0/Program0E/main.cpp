#include <stdio.h>
#include <stdlib.h>

int count;
int sum;
int bound;

int isPrime(int num) {
	if (num <= 1) {
		return 0;
	}
	if (num % 2 == 0 && num > 2) {
		return 0;
	}
	for( int i = 3; i < num / 2; i += 2) {
		if ( num % i == 0 ) {
			return 0;
		}
	}
	return 1;
}

int findSum() {
	for (count; count < bound; count++) {       // run until count >= bound
		if (isPrime(count)) {
			sum += count;                       // if count is a prime number, then accumulate into sum
		}
	}
	if (count >= bound) {                       // exit condition
		return 0;
	} else {                                    // run until exit condition is met
		findSum();
	}
}


int main()
{
	bound = 0;
	count = 0;
	sum = 0;
	printf("Please indicate the boundary of your search: \n");
	scanf("%d", &bound);
	findSum();
	printf("The sum of the prime numbers up to %d is %d\n",bound, sum);
	return 0;
}
