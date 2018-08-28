// CRM <Project4.cpp>
// EE 312 Project 4 submission by
// Ryan Kim
// jk39938
// Slip days used: 0
// Summer 2018

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "MyString.h"
#include "Invent.h"

#define MAX_CUSTOMERS 1000
Customer customers[MAX_CUSTOMERS];
int num_customers = 0;

/* you'll probably need several more global variables */
int inventBottles = 0;                                      // global var containing inventory bottle count
int inventDiapers = 0;                                      // global var containing inventory diaper count
int inventRattles = 0;                                      // global var containing inventory rattle count

/* and of course, you have a few functions to write */
int checkInventory(String* item, int* quantity);            // auxiliary function used as a condition check

/* clear the inventory and reset the customer database to empty */
void reset(void) {
	inventBottles = 0;                                      // reset all inventory items
	inventDiapers = 0;
	inventRattles = 0;
	while(num_customers) {                                  // runs until num_customers = 0
		StringDestroy(&customers[num_customers-1].name);    // clears name (String data type) of each customer
		num_customers--;
	}
}

void processSummarize() {
	int maxBottlesIdx = 0;                                  // set initial index of max values to 0
	int maxDiapersIdx = 0;
	int maxRattlesIdx = 0;
	int maxBottles = 0;                                     // set initial max values to 0
	int maxDiapers = 0;
	int maxRattles = 0;

	for (int i = 0; i < num_customers; i++) {               // finds index of customer with max of each purchase
		if (maxBottles < customers[i].bottles) {
			maxBottles = customers[i].bottles;
			maxBottlesIdx = i;
		}

		if (maxDiapers < customers[i].diapers) {
			maxDiapers = customers[i].diapers;
			maxDiapersIdx = i;
		}

		if (maxRattles < customers[i].rattles) {
			maxRattles = customers[i].rattles;
			maxRattlesIdx = i;
		}
	}

	printf("There are %d Bottles, %d Diapers and %d Rattles in inventory\n",
	       inventBottles, inventDiapers, inventRattles);                        // current inventory status
	printf("we have had a total of %d different customers\n", num_customers);   // current number of customers with
																				// meaningful purchases
	if (!maxBottles) {                                      // if no one bought bottles
		printf("no one has purchased any Bottles\n");
	} else {
		for (int i = 0; i < customers[maxBottlesIdx].name.len; i++) {
			putchar(customers[maxBottlesIdx].name.ptr[i]);
		}
		printf(" has purchased the most Bottles (%d)\n", maxBottles);
	}

	if (!maxDiapers) {                                      // if no one bought diapers
		printf("no one has purchased any Diapers\n");
	} else {
		for (int i = 0; i < customers[maxDiapersIdx].name.len; i++) {
			putchar(customers[maxDiapersIdx].name.ptr[i]);
		}
		printf(" has purchased the most Diapers (%d)\n", maxDiapers);
	}

	if (!maxRattles) {                                      // if no one bought rattles
		printf("no one has purchased any Rattles\n");
	} else {
		for (int i = 0; i < customers[maxRattlesIdx].name.len; i++) {
			putchar(customers[maxRattlesIdx].name.ptr[i]);
		}
		printf(" has purchased the most Rattles (%d)\n", maxRattles);
	}
}

void processPurchase() {
	int customerNumber, quantity;            // index of customers array ------------ used in readNum
	int isInDatabase = 0;                    // flag set after checking if customer is question is in customers array

	String person, item, bottles, diapers, rattles;

	readString(&person);
	for (customerNumber = 0; customerNumber < num_customers; customerNumber++) {    // checks if customer is in array
		if (StringIsEqualTo(&person, &customers[customerNumber].name))  {
			isInDatabase = 1;
			break;                          // break to preserve customerNumber
		}
	}

	readString(&item);                      // update item
	readNum(&quantity);                     // update quantity of item

	bottles = StringCreate("Bottles");      // allocate String data
	diapers = StringCreate("Diapers");
	rattles = StringCreate("Rattles");

	if(!isInDatabase) {
		if (quantity > 0) {                                                 // create new entry in customers[]
			if (StringIsEqualTo(&item, &bottles)) {
				if (checkInventory(&item, &quantity)) {                     // checks if request can be fulfilled
					customers[num_customers].name = StringDup(&person);     // copy name (String data type)
					customers[num_customers].bottles = 0;                   // initialize items purchased
					customers[num_customers].diapers = 0;
					customers[num_customers].rattles = 0;
					customers[num_customers].bottles += quantity;           // update bottles quantity purchased
					inventBottles -= quantity;                              // update bottles quantity removed from inv
					num_customers++;                                        // count of indices containing useful info
				} else {
					printf("Sorry ");                                       // print the following if the purchase
					for (int j = 0; j < person.len; j++) {                  // request cannot be fulfilled
						putchar(person.ptr[j]);
					}
					printf(", we only have %d ", inventBottles);
					for (int j = 0; j < bottles.len; j++) {
						putchar(bottles.ptr[j]);
					}
					printf("\n");

				}

			} else if (StringIsEqualTo(&item, &diapers)) {
				if (checkInventory(&item, &quantity)) {                     // checks if request can be fulfilled
					customers[num_customers].name = StringDup(&person);     // copy name (String data type)
					customers[num_customers].bottles = 0;                   // initialize items purchased
					customers[num_customers].diapers = 0;
					customers[num_customers].rattles = 0;
					customers[num_customers].diapers += quantity;           // update diapers quantity purchased
					inventDiapers -= quantity;                              // update diapers quantity removed from inv
					num_customers++;                                        // count of indices containing useful info
				} else {
					printf("Sorry ");                                       // print the following if the purchase
					for (int j = 0; j < person.len; j++) {                  // request cannot be fulfilled
						putchar(person.ptr[j]);
					}
					printf(", we only have %d ", inventDiapers);
					for (int j = 0; j < diapers.len; j++) {
						putchar(diapers.ptr[j]);
					}
					printf("\n");

				}

			} else if (StringIsEqualTo(&item, &rattles)) {
				if(checkInventory(&item, &quantity)) {                      // checks if request can be fulfilled
					customers[num_customers].name = StringDup(&person);     // copy name (String data type)
					customers[num_customers].bottles = 0;                   // initialize items purchased
					customers[num_customers].diapers = 0;
					customers[num_customers].rattles = 0;
					customers[num_customers].rattles += quantity;           // update rattles quantity purchased
					inventRattles -= quantity;                              // update rattles quantity removed from inv
					num_customers++;                                        // count of indices containing useful info
				} else {
					printf("Sorry ");                                       // print the following if the purchase
					for (int j = 0; j < person.len; j++) {                  // request cannot be fulfilled
						putchar(person.ptr[j]);
					}
					printf(", we only have %d ", inventRattles);
					for (int j = 0; j < rattles.len; j++) {
						putchar(rattles.ptr[j]);
					}
					printf("\n");

				}

			}
		}

	} else {                                                                // case if customer is in database
		if (quantity > 0) {                                                 // verify that customer wants to buy 1+
			if (StringIsEqualTo(&item, &bottles)) {
				if(checkInventory(&item, &quantity)) {
					customers[customerNumber].bottles += quantity;          // add to existing purchase count
					inventBottles -= quantity;                              // decrease from inventory
				} else {
					printf("Sorry ");                                       // error statement
					for (int j = 0; j < customers[customerNumber].name.len; j++) {
						putchar(customers[customerNumber].name.ptr[j]);
					}
					printf(", we only have %d ", inventBottles);
					for (int j = 0; j < bottles.len; j++) {
						putchar(bottles.ptr[j]);
					}
					printf("\n");

				}

			} else if (StringIsEqualTo(&item, &diapers)) {
				if(checkInventory(&item, &quantity)) {
					customers[customerNumber].diapers += quantity;          // add to existing purchase count
					inventDiapers -= quantity;                              // decrease from inventory
				} else {
					printf("Sorry ");                                       // error statement
					for (int j = 0; j < customers[customerNumber].name.len; j++) {
						putchar(customers[customerNumber].name.ptr[j]);
					}
					printf(", we only have %d ", inventDiapers);
					for (int j = 0; j < diapers.len; j++) {
						putchar(diapers.ptr[j]);
					}
					printf("\n");

				}

			} else if (StringIsEqualTo(&item, &rattles)) {
				if(checkInventory(&item, &quantity)) {
					customers[customerNumber].rattles += quantity;          // add to existing purchase count
					inventRattles -= quantity;                              // decrease from inventory
				} else {
					printf("Sorry ");                                       // error statement
					for (int j = 0; j < customers[customerNumber].name.len; j++) {
						putchar(customers[customerNumber].name.ptr[j]);
					}
					printf(", we only have %d ", inventRattles);
					for (int j = 0; j < rattles.len; j++) {
						putchar(rattles.ptr[j]);
					}
					printf("\n");

				}

			}
		}
	}

	StringDestroy(&bottles);                        // deallocate all String data to avoid memory leaks
	StringDestroy(&diapers);
	StringDestroy(&rattles);
	StringDestroy(&person);
	StringDestroy(&item);

}

void processInventory() {
	String item, bottles, diapers, rattles;         // item used in readString
	int quantity;                                   // used in readNum

	bottles = StringCreate("Bottles");              // allocate String data
	diapers = StringCreate("Diapers");
	rattles = StringCreate("Rattles");

	readString(&item);
	if (StringIsEqualTo(&item, &bottles)) {
		readNum(&quantity);
		if (quantity >= 0) {
			inventBottles += quantity;                   // add import to inventory
		}

	} else if (StringIsEqualTo(&item, &diapers)) {
		readNum(&quantity);
		if (quantity >= 0) {
			inventDiapers += quantity;                   // add import to inventory
		}

	} else if (StringIsEqualTo(&item, &rattles)) {
		readNum(&quantity);
		if (quantity >= 0) {
			inventRattles += quantity;                   // add import to inventory
		}
	}

	StringDestroy(&item);                           // deallocate all String data to avoid memory leaks
	StringDestroy(&bottles);
	StringDestroy(&diapers);
	StringDestroy(&rattles);
}

int checkInventory(String* item, int* quantity) {   // auxiliary function that checks if there is enough stock of
	String bottles, diapers, rattles;               // requested item in the inventory
	int inventFlag = 0;                             // output parameter (0 = do not fulfill, 1 = ok to fulfill)

	bottles = StringCreate("Bottles");              // allocate String data
	diapers = StringCreate("Diapers");
	rattles = StringCreate("Rattles");

	if (StringIsEqualTo(item, &bottles)) {
		if (inventBottles - *quantity >= 0) {       // verifies if inventory goes negative upon fulfilling request
			inventFlag = 1;
		} else {
			inventFlag = 0;
		}

	} else if (StringIsEqualTo(item, &diapers)) {   // verifies if inventory goes negative upon fulfilling request
		if (inventDiapers - *quantity >= 0) {
			inventFlag = 1;
		} else {
			inventFlag = 0;
		}

	} else if (StringIsEqualTo(item, &rattles)) {   // verifies if inventory goes negative upon fulfilling request
		if (inventRattles - *quantity >= 0) {
			inventFlag = 1;
		} else {
			inventFlag = 0;
		}
	}

	StringDestroy(&bottles);                        // deallocate all String data to avoid memory leaks
	StringDestroy(&diapers);
	StringDestroy(&rattles);

	return inventFlag;
}
