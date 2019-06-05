#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include <cctype>
#include <conio.h>
#include "Evaluator.h"
#include <windows.h>

#define ERROR_MESSAGE cout << endl << msg << "\nTry again!" << endl;
#define MAX_INPUT_SIZE 255
#define PAUSE cout << "\n\nPress any button to repeat the process\n'M' to go to main menu or 'Q' to quit: ";char option = getche();

using namespace std;

#pragma warning(disable:4996)
 
enum tokType {
	Num, Func, Op, Constant, Var, BrackL, BrackR
};
struct Token
{
	tokType type;
	string tok;
	int order;
	Token(string tok_, tokType type_, int order_) : tok(tok_), type(type_), order(order_) { }
};

class RPN : public Evaluator
{
public:
	unsigned int priority(string op);
	unsigned int priority(char op);
	vector<Token> infixToPostfix(char *input);
	double evaluate(vector<Token> output);
	double evaluate(vector<Token> output, double x);
	double evaluate(char *input);
	double evaluate(char *input, double x);
	vector<double> evaluate(char *input, double xLower, double xUpper, double step);
	bool canBeEvaluatedForX(vector<Token> postfixExpression);
	void printRPN(vector<Token>);
	char asciiToChar(string a);
	RPN();
	~RPN();
};


