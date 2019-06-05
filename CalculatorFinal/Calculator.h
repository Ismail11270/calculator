#pragma once
#include "RPN.h"
#include "SFML\Graphics.hpp"
#include "button.h"


class Calculator
{
private:
	int counter = 0;
	RPN rpn;
	bool active;
	bool running;
	const string menuPrinter = "\n\n\n\n\t\t*****************CALCULATOR*****************\n\n"
		"\t*********Press 'A' to evaluate a simple expression ***********\n\n"
		"\t*********Press 'B' to evaluate y(x) function for x ***********\n\n"
		"\t*********Press 'C' to plot y(x) for range of x\t  ***********\n\n"
		"\t    ******** Press 'Q' to quit the program    ********\n"
		"\t    ******** Press 'M' to display user manual ********\n\n";
	const string manualPrinter =
		"\n	User's Manual: \n"
		"\n	1. Possible operations are : + , - , * , / , ^  including brackets:\n"
		"\n			\"5+(1-3)/5*5\" - Correct syntax."
		"\n			\"6abc-dsa/gd=d\" - Wrong syntax.\n"
		"\n	2. Power must be an INTEGER (non floating number). \n"
		"\n			\"5^3\" - Correct syntax."
		"\n			\"5^3.3\" - Wrong syntax.\n"
		"\n	3. Inputting multiple operators for 1 operation will cause an error: \n"
		"			\"5/*-3*-5\" - Wrong syntax\n"
		"\n	4. For floating numbers use '.' not ',' (1.1 2,2) \n"
		"\n	5. Sound signal notifies that an error has occured. \n";
public:


	
	void run();
	void run(sf::RenderWindow *window, sf::Font font);
	void printMenu();
	void printManual();
	char simpleExpressionEvaluation();
	double simpleExpressionEvaluation(char *input_);
	double evaluateFunction(char *input_, double x);
	void plotFunction(char *input_, string range, double step);
	Calculator();
	~Calculator();
};

