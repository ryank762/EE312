/* Project8 <main.cpp>
 * Ryan Kim
 * jk39938
 * EE312 Summer 2018
 * Slip days used: 0
 */

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "Parse.h"
#include "Blip.h"

void run() {
	Interpret();
}

int main() {

	set_input("test_grader.blip");
	run();

	/*
	std::cout << "Test 1" << std::endl;
	set_input("test1.blip");
	run();

	std::cout << "Test 2" << std::endl;
	set_input("test2.blip");
	run();

	std::cout << "Test 3" << std::endl;
	set_input("test3.blip");
	run();

	std::cout << "Test 4" << std::endl;
	set_input("test4.blip");
	run();
	 */

	return 0;
}