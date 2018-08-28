/* Project8 <Blip.cpp>
 * Ryan Kim
 * jk39938
 * EE312 Summer 2018
 * Slip days used: 0
 */

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Parse.h"
#include "Blip.h"
#include "Tree.h"

std::map<std::string, int> varTable;
std::map<std::string, int>::iterator varIt;

void Interpret() {

	read_next_token();

	while (next_token_type != END) {
		std::string nextToken = next_token();

		if (nextToken == "//") {
			skip_line();
		}

		if (nextToken == "text") {
			read_next_token();
			std::cout << next_token();

		} else if (nextToken == "output") {
			std::cout << Evaluate();

		} else if (nextToken == "var") {
			read_next_token();
			nextToken = next_token();

			varIt = varTable.find(nextToken);
			if (varIt != varTable.end()) {
				std::cout << "variable " << nextToken << " incorrectly re-initialized" << std::endl;
			}
			varTable[nextToken] = Evaluate();

		} else if (nextToken == "set") {
			read_next_token();
			nextToken = next_token();

			varIt = varTable.find(nextToken);
			if (varIt == varTable.end()) {
				std::cout << "variable " << nextToken << " not declared" << std::endl;
			}
			varTable[nextToken] = Evaluate();
		}
		read_next_token();
	}
}

int Evaluate() {
	int binOptrCount = 0, oprndCount = 0;
	std::string nullStamp = "\0";
	std::vector<Node*> expr;

	read_next_token();
	std::string nextToken = next_token();

	Node* exprNode;
	while (oprndCount != binOptrCount + 1) {
		if (next_token_type == NAME) {
			exprNode = new Node(false, true, 0, nextToken, nullStamp);
			expr.push_back(exprNode);

			oprndCount++;

		} else if (next_token_type == SYMBOL) {
			exprNode = new Node(false, false, 0, nullStamp, nextToken);
			expr.push_back(exprNode);

			if (nextToken != "!" && nextToken != "~") {
				binOptrCount++;
			}

		} else if (next_token_type == NUMBER) {
			exprNode = new Node(true, false, std::stoi(nextToken), nullStamp, nullStamp);
			expr.push_back(exprNode);

			oprndCount++;

		}
		if (oprndCount == binOptrCount + 1) {
			break;
		}
		read_next_token();
		nextToken = next_token();
	}
	ExpTree expTree(expr);
	return expTree.parse();
}
