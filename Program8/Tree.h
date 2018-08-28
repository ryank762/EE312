#include <iostream>
#include <vector>
#include <map>
#include <string>


class Node {
public:
	bool isOperand;
	bool isVar;
	int operand;
	std::string var;
	std::string optr;
	Node* left;
	Node* right;

	Node(bool isOperand, bool isVar, int operand, std::string var, std::string& optr) {
		left = nullptr;
		right = nullptr;
		this->isOperand = isOperand;
		this->isVar = isVar;
		this->operand = operand;
		this->var = var;
		this->optr = optr;
	}
};

class ExpTree {
private:
	Node* overallRoot;
	int parse(Node* root) {
		if (root->isOperand) {
			return root->operand;
		} else if (root->isVar) {
			return varTable.find(root->var)->second;
		}

		if (root->optr == "~") {
			return parse(root->left) * -1;
		} else if (root->optr == "!") {
			return !parse(root->left);
		}

		int arg1 = parse(root->left);
		int arg2 = parse(root->right);

		if (root->optr == "+") {
			return arg1 + arg2;
		} else if (root->optr == "-") {
			return arg1 - arg2;
		} else if (root->optr == "*") {
			return arg1 * arg2;
		} else if (root->optr == "/") {
			return arg1 / arg2;
		} else if (root->optr == "%") {
			return arg1 % arg2;
		} else if (root->optr == "&&") {
			return (arg1 && arg2) ? 1 : 0;
		} else if (root->optr == "||") {
			return (arg1 || arg2) ? 1 : 0;
		} else if (root->optr == "<") {
			return (arg1 < arg2) ? 1 : 0;
		} else if (root->optr == ">") {
			return (arg1 > arg2) ? 1 : 0;
		} else if (root->optr == "==") {
			return (arg1 == arg2) ? 1 : 0;
		} else if (root->optr == "!=") {
			return (arg1 != arg2) ? 1 : 0;
		} else if (root->optr == "<=") {
			return (arg1 <= arg2) ? 1 : 0;
		} else if (root->optr == ">=") {
			return (arg1 >= arg2) ? 1 : 0;
		}

	}
	Node* add(Node* root, std::vector<Node*>& expr) {
		Node* first = expr[0];
		expr.erase(expr.begin());
		root = first;
		if (!first->isOperand && !first->isVar) {
			root->left = add(root->left, expr);
			if (first->optr != "~" && first->optr != "!") {
				root->right = add(root->right, expr);
			}
		}
		return root;
	}
public:
	int parse() {
		parse(overallRoot);
	}
	ExpTree(std::vector<Node*>& expr) {             // constructor
		overallRoot = add(overallRoot, expr);
	}
};