// CRM2 <CustomerDB.cpp>
// EE 312 Project 7 submission by
// Ryan Kim
// jk39938
// Slip days used: 0
// Summer 2018

#include <iostream>
#include <cassert>
#include "String.h"
#include "CustomerDB.h"

using namespace std;

const int default_capacity = 1;

Customer::Customer(String name) { // done, please do not edit
	this->bottles = 0;
	this->rattles = 0;
	this->diapers = 0;
	this->name = name;
}

CustomerDB::CustomerDB(void) { // done, please do not edit
	this->capacity = default_capacity;
	this->data = new Customer[this->capacity];
	this->length = 0;
}

int CustomerDB::size(void) { // done, please do not edit
	return this->length;
}

CustomerDB::~CustomerDB(void) { // done, please do not edit
	delete[] this->data;
}

void CustomerDB::clear(void) { // done, please do not edit
	delete[] this->data;
	this->capacity = default_capacity;
	this->data = new Customer[this->capacity];
	this->length = 0;
}

Customer& CustomerDB::operator[](int k) { // done, please do not edit
	assert(k >= 0 && k < this->length);
	return this->data[k];
}

Customer& CustomerDB::operator[](String name) { // not done, your effort goes here
	if (this->isMember(name)) {                         // is in database
		int i;
		for (i = 0; this->data[i].name != name; i++);
		return this->data[i];

	} else {                                            // is not in database
		if (this->length == this->capacity) {           // capacity is full
			Customer* newArray = new Customer[this->capacity*2];
			for (int i = 0; i < this->length; i++) {
				newArray[i].name = this->data[i].name;
				newArray[i].bottles = this->data[i].bottles;
				newArray[i].rattles = this->data[i].rattles;
				newArray[i].diapers = this->data[i].diapers;
			}
			delete[] this->data;
			this->data = newArray;
			this->capacity *= 2;

		}

		this->data[this->length].name = name;
		this->data[this->length].bottles = 0;
		this->data[this->length].rattles = 0;
		this->data[this->length].diapers = 0;
		this->length++;

	}
}

bool CustomerDB::isMember(String name) { // not done, your effort goes here
	int i;

	for (i = 0; i < this->length; i++) {
		if (this->data[i].name == name) {
			return true;
		}
	}

	return false;


}
