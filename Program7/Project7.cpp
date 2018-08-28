// CRM2 <Project7.cpp>
// EE 312 Project 7 submission by
// Ryan Kim
// jk39938
// Slip days used: 0
// Summer 2018

#include <iostream>
#include <stdio.h>
#include "String.h"
#include "Customer.h"
#include "CustomerDB.h"

void readString(String&);
void readNum(int&);

CustomerDB database;

int num_bottles = 0;
int num_rattles = 0;
int num_diapers = 0;

/* clear the inventory and reset the customer database to empty */
void reset(void) {
	database.clear();
	num_bottles = 0;
	num_rattles = 0;
	num_diapers = 0;
}

/*
 * selectInventItem is a convenience function that allows you
 * to obtain a pointer to the inventory record using the item type name
 * word must be "Bottles", "Diapers" or "Rattles"
 * for example the expression *selectInventItem("Bottles") returns the 
 * current global variable for the number of bottls in the inventory
 */
int* selectInventItem(String word) {
	if (word == "Bottles") {
		return &num_bottles;
	} else if (word == "Diapers") {
		return &num_diapers;
	} else if (word == "Rattles") {
		return &num_rattles;
	}
	
	/* NOT REACHED */
	return 0;
}

/*
 * this overload of selectInventItem is similar to selectInventItem above, however
 * this overload takes a Customer as a second argument and selects the data member
 * of that Customer that matches "word". The function returns a pointer to one of the three data
 * members from the specified customer.
 */
int* selectInventItem(String word, Customer& cust) {
	if (word == "Bottles") {
		return &cust.bottles;
	} else if (word == "Diapers") {
		return &cust.diapers;
	} else if (word == "Rattles") {
		return &cust.rattles;
	}
	
	/* NOT REACHED */
	return 0;
}

/*
 * findMax searches through the CustomerDB "database" and returns the Customer
 * who has purchased the most items of the specified type.
 * type must be one of "Bottles", "Rattles" or "Diapers".
 * 
 * Note: if two or more Customers are tied for having purchased the most of that item type
 * then findMax returns the first Customer in the CustomerDB who has purchased that maximal
 * quantity.
 *
 * Note: in the special case (invalid case) where there are zero Customers in the 
 * CustomerDB, fundMax returns a null pointer (0)
 */
Customer* findMax(String type) {
	Customer* result = 0;
	int max = 0;
	for (int k = 0; k < database.size(); k += 1) {
		Customer& cust = database[k];
		int *p = selectInventItem(type, cust); 
		if (*p > max) {
			max = *p;
			result = &cust;
		}
	}
	
	return result;
}

void processPurchase() {
	int quantity;
	String person, item;
	String bottles = String("Bottles");
	String rattles = String("Rattles");
	String diapers = String("Diapers");

	readString(person);
	readString(item);
	readNum(quantity);

	if (quantity <= 0) {
		return;
	}

	if (item != bottles && item != rattles && item != diapers) {
		return;
	}

	if (item == bottles) {
		if (quantity > num_bottles) {
			std::cout << "Sorry " << person.c_str() << " we only have " << num_bottles << " Bottles" << std::endl;
			return;
		}
	} else if (item == rattles) {
		if (quantity > num_rattles) {
			std::cout << "Sorry " << person.c_str() << " we only have " << num_rattles << " Rattles" << std::endl;
			return;
		}
	} else if (item == diapers) {
		if (quantity > num_diapers) {
			std::cout << "Sorry " << person.c_str() << " we only have " << num_diapers << " Diapers" << std::endl;
			return;
		}
	}

	if (database.isMember(person)) {
		if (item == bottles) {
			database[person].bottles += quantity;
			num_bottles -= quantity;
		} else if (item == rattles) {
			database[person].rattles += quantity;
			num_rattles -= quantity;
		} else if (item == diapers) {
			database[person].diapers += quantity;
			num_diapers -= quantity;
		}
	} else {
		database[person];
		if (item == bottles) {
			database[person].bottles += quantity;
			num_bottles -= quantity;
		} else if (item == rattles) {
			database[person].rattles += quantity;
			num_rattles -= quantity;
		} else if (item == diapers) {
			database[person].diapers += quantity;
			num_diapers -= quantity;
		}
	}
}

void processSummarize() {
	Customer* person;
	String bottles = String("Bottles");
	String rattles = String("Rattles");
	String diapers = String("Diapers");

	std::cout << "There are " << num_bottles << " Bottles, " << num_diapers << " Diapers and "
			<< num_rattles << " Rattles in inventory" << std::endl;
	std::cout << "we have had a total of " << database.size() << " different customers" << std::endl;

	person = findMax(bottles);
	if (!person) {
		std::cout << "no one has purchased any Bottles" << std::endl;
	} else {
		std::cout << person->name.c_str() << " has purchased the most Bottles (" << person->bottles << ")" << std::endl;
	}

	person = findMax(diapers);
	if (!person) {
		std::cout << "no one has purchased any Diapers" << std::endl;
	} else {
		std::cout << person->name.c_str() << " has purchased the most Diapers (" << person->diapers << ")" << std::endl;
	}

	person = findMax(rattles);
	if (!person) {
		std::cout << "no one has purchased any Rattles" << std::endl;
	} else {
		std::cout << person->name.c_str() << " has purchased the most Rattles (" << person->rattles << ")" << std::endl;
	}
}

void processInventory() {
	int quantity;
	String item;
	String bottles = String("Bottles");
	String rattles = String("Rattles");
	String diapers = String("Diapers");

	readString(item);
	readNum(quantity);

	if (quantity < 0) {
		return;
	}

	if (item == bottles) {
		num_bottles += quantity;
	} else if (item == rattles) {
		num_rattles += quantity;
	} else if (item == diapers) {
		num_diapers += quantity;
	}
}
