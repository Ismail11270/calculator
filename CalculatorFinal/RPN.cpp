#include "RPN.h"
#pragma warning(disable:4996)

RPN::RPN()
{
}

RPN::~RPN()
{

}

vector<Token> RPN::infixToPostfix(char *input)
{
	char *p;
	p = input;
	int n;
	char temp;

	double numTok;
	char opTok;
	char funTok[4];
	int order = 0;
	vector<Token> output;
	vector<Token> opStack;
	bool err = false;

	if (!isalnum(input[0]) && !isalpha(input[0]))
	{
		if (input[0] != '(' && input[0] != '-' && input[0] != '[') {
			err = true;
			cerr << "Error";
		}
		else if (input[0] == '(') err = false;
		else if (input[0] == '-') {
			sscanf(p, "%lf%n", &numTok, &n);
			p += n;
			output.push_back(Token{ to_string(numTok),Num,order });
			order++;
		}

	}
	while (int k = sscanf(p, "%c%n", &temp, &n) > 0 && err == false) {
		//if number
		if (temp == ' ')
		{
			p += n;
		}
		else if (isalnum(temp) && !isalpha(temp))
		{
			sscanf(p, "%lf%n", &numTok, &n);
			//cout << "Token is a number" << endl << numTok << endl;
			p += n;
			output.push_back(Token{ to_string(numTok),Num,order });
			order++;
		}
		//if a function or a variable or a constant
		else if (isalpha(temp))
		{
			char temp_[2];
			sscanf(p, "%3s", &funTok);
			int s = sscanf(p, "%2c", temp_);
			string funTok_ = string(funTok);
			if (funTok_ == "cos" || funTok_ == "sin" || funTok_ == "tan" || funTok_ == "srt" || funTok_ == "log") {
				opStack.push_back(Token{ funTok_,Func,order });
				p += 3;
				order++;
				//	cout << "11111\n";
			}
			//scan for the char + the next char

			else if ((s > 0 && (!isalnum(temp_[1]) && !isalpha(temp_[1]))))
			{
				if (!isalnum(temp_[1]) && !isalpha(temp_[1]))
				{
					if (temp == 'e') {
						//	cout << "A constant\n";
						output.push_back(Token{ "E",Constant,order });
						p++;
						order++;
					}
					else if (temp == 'p') {
						//	cout << "A constant\n";
						output.push_back(Token{ "P",Constant,order });
						p++;
						order++;
					}
					else {
						//	cout << "A variable\n";
						output.push_back(Token{ to_string(temp_[0]), Var, order });
						p++;
						order++;
					}
				}
				else throw "Error! Wrong Syntax!";
			}
			else if (s < 0)
			{
				if (temp == 'e') {
					//	cout << "A constant\n";
					output.push_back(Token{ "E",Constant,order });
					p++;
					order++;
				}
				else if (temp == 'p') {
					//		cout << "A constant\n";
					output.push_back(Token{ "P",Constant,order });
					p++;
					order++;
				}
				else {
					output.push_back(Token{ to_string(temp),Var,order });
					//	cout << "A variable\n";
					p++;
					order++;
				}
			}
			else throw "Error! Wrong Syntax!";
		}
		//if operator
		else if (temp == '+' || temp == '-' || temp == '/' || temp == '*' || temp == '^') {
			sscanf(p, "%c%n", &opTok, &n);
			while (!opStack.empty() && (opStack.back().type == Op || opStack.back().type == Func) && opStack.back().type != BrackL)
			{
				if (opStack.back().type == Op) {
					if (priority(opStack.back().tok) > priority(opTok) || (priority(opStack.back().tok) == priority(opTok) && asciiToChar(opStack.back().tok) != '^')) {
						output.push_back(opStack.back());
						opStack.pop_back();
					}
					else if (priority(opTok) > priority(opStack.back().tok)) break;
				}
				else if (opStack.back().type == Func) {
					output.push_back(opStack.back());
					opStack.pop_back();
				}
			}
			opStack.push_back(Token{ to_string(opTok), Op, order });   //../////
			p += n;
			order++;
		}
		else if (temp == '(') {
			int n_;
			char temp_;
			char temp__;
			double tempN_;		
			char tempN__;		//check for a const
			char *p_ = p;
			p_++;
			char *p__ = p_;

			int k_;
			int z;

			if (k_ = sscanf(p_, "%lf%n", &tempN_, &n_) > 0) {
				p_ += n_;
				sscanf(p_, "%c", &temp_);
			}
			else if (z = sscanf(p_, "%c", &tempN__))
			{
				p__++;
				sscanf(p__, "%c", &temp__);
			}
			
			if (k > 0 && temp_ == ')') {
				output.push_back(Token{ to_string(tempN_),Num,order });
				order++;
				p = p + n_ + 2;
			}
			else if (z > 0 && temp_ == ')' && (tolower(tempN__) == 'p' || tolower(tempN__) == 'e')) {
				output.push_back( Token{ to_string(tempN__), Constant, order });

			}
			else //if (temp == '(')
			{
				opStack.push_back(Token{ "(", BrackL, order });
				p += n;
				order++;
			}
		}
		//if BrckL

		//if BrckR
		else if (temp == ')')
		{
			while (opStack.back().type != BrackL)
			{
				output.push_back(opStack.back());
				opStack.pop_back();
				if (opStack.empty()) {
					throw "Error! Mismatched parenthesis!";
				}
			}
			opStack.pop_back();
			p += n;
		}
		else throw "Error! Wrong syntax!";

	}
	while (!opStack.empty()) {
		if (opStack.back().type == BrackL) throw "Missmached parenthesis error!";
		output.push_back(opStack.back());
		opStack.pop_back();
	}
	if (err) throw "Wrong Syntax!";
	cout << "Converted to RPN successfully" << endl;
	int count = 0;
	for (int i = 0; i < output.size(); i++)
	{
		if (output.at(i).type == Op || output.at(i).type == Func)
		{
			count++;
		}
	}
	if (count == 0) throw "Wrong expression, zero operators found!";
	return output;
}

void RPN::printRPN(vector<Token> output) {
	for (int i = 0; i < output.size(); i++) {
		if (output.at(i).type == Op || output.at(i).type == Var) cout << asciiToChar(output.at(i).tok) << " ";
		else cout << output.at(i).tok << " ";
	}
	cout << endl;
}
//evaluate with var
double RPN::evaluate(vector<Token> output)			//throws
{
	for (int i = 0; i < output.size(); i++)
	{
		if (output.at(i).type == Var) {
			throw "Can't evaluate expressions with variables!";
		}
	}
	vector<double> result;
	for (int i = 0; i < output.size(); i++) {
		//if a number
		if (output.at(i).type == Num) {
			result.push_back(stoi(output.at(i).tok));
		}
		//if an operator
		else if (output.at(i).type == Op) {
			double a, b;
			if (result.size() < 2) throw "Error! Not enough operands to evaluate!";
			else {
				a = result.back();
				result.pop_back();
				b = result.back();
				result.pop_back();
				add(a, b);
				switch (asciiToChar(output.at(i).tok)) {
				case '+':
					result.push_back(add(a, b));
					//		cout << "Adding\n";
					break;
				case '-':
					result.push_back(substruct(a, b));
					//		cout << "Substructing\n";
					break;
				case '/':
					result.push_back(divide(a, b));
					//		cout << "Dividing\n";
					break;
				case '*':
					result.push_back(multiply(a, b));
					//	cout << "Multiplying\n";
					break;
				case '^':
					result.push_back(exponentiate(a, b));
					//		cout << "Exponentiation\n";
					break;
				default:
					throw "Wrong operator!";
				}
			}
		}
		//if a function
		else if (output.at(i).type == Func) {
			double functEvaluation;
			if (result.size() < 1) throw "Error! Not enough arguments for function evaluation\n";
			else {
				if (output.at(i).tok == "sin") {
					functEvaluation = Sin(result.back());
					result.pop_back();
					result.push_back(functEvaluation);
					//	cout << "Sin\n";
				}
				else if (output.at(i).tok == "cos") {
					functEvaluation = Cos(result.back());
					result.pop_back();
					result.push_back(functEvaluation);
					//		cout << "Cos\n";
				}
				else if (output.at(i).tok == "tan") {
					functEvaluation = Tan(result.back());
					result.pop_back();
					result.push_back(functEvaluation);
					//	cout << "Tan\n";
				}
				else if (output.at(i).tok == "srt") {
					functEvaluation = sqrt(result.back());
					result.pop_back();
					result.push_back(functEvaluation);
					//	cout << "Srt\n";
				}
				else if (output.at(i).tok == "log") {
					functEvaluation = log(result.back());
					result.pop_back();
					result.push_back(functEvaluation);
					//	cout << "Log\n";
				}
				else throw "Wrong function name!";
			}
		}
		//if a constant e / pi
		else if (output.at(i).type == Constant) {
			if (output.at(i).tok == "E") {
				result.push_back(M_E);
			}
			else if (output.at(i).tok == "P") {
				result.push_back(M_PI);
			}
		}
	}
	return result[0];
}
//evaluate without var
double RPN::evaluate(vector<Token> output, double x)
{
	if (!canBeEvaluatedForX(output)) throw "More than one or a wrong variable in use, use only 'x'!";
	vector<double> result;
	for (int i = 0; i < output.size(); i++) {
		//if a number
		if (output.at(i).type == Num) {
			result.push_back(stoi(output.at(i).tok));
		}
		//if an operator
		else if (output.at(i).type == Op) {
			double a, b;
			if (result.size() < 2) throw "Error! Not enough operands to evaluate!";
			else {
				a = result.back();
				result.pop_back();
				b = result.back();
				result.pop_back();
				add(a, b);
				switch (asciiToChar(output.at(i).tok)) {
				case '+':
					result.push_back(add(a, b));
					//		cout << "Adding\n";
					break;
				case '-':
					result.push_back(substruct(a, b));
					//		cout << "Substructing\n";
					break;
				case '/':
					result.push_back(divide(a, b));
					cout << "Dividing\n";
					break;
				case '*':
					result.push_back(multiply(a, b));
					//		cout << "Multiplying\n";
					break;
				case '^':
					result.push_back(exponentiate(a, b));
					//		cout << "Exponentiation\n";
					break;
				default:
					throw "Wrong operator!";
				}
			}
		}
		//if a function
		else if (output.at(i).type == Func) {
			double functEvaluation;
			if (result.size() < 1) throw "Error! Not enough arguments for function evaluation\n";
			else {
				if (output.at(i).tok == "sin") {
					functEvaluation = Sin(result.back());
					result.pop_back();
					result.push_back(functEvaluation);
					//	cout << "Sin\n";
				}
				else if (output.at(i).tok == "cos") {
					functEvaluation = Cos(result.back());
					result.pop_back();
					result.push_back(functEvaluation);
					//	cout << "Cos\n";
				}
				else if (output.at(i).tok == "tan") {
					functEvaluation = Tan(result.back());
					result.pop_back();
					result.push_back(functEvaluation);
					//	cout << "Tan\n";
				}
				else if (output.at(i).tok == "srt") {
					functEvaluation = sqrt(result.back());
					result.pop_back();
					result.push_back(functEvaluation);
					//	cout << "Srt\n";
				}
				else if (output.at(i).tok == "log") {
					functEvaluation = log(result.back());
					result.pop_back();
					result.push_back(functEvaluation);
					//	cout << "Log\n";
				}
				else throw "Wrong function name!";
			}
		}
		//if a constant e / pi
		else if (output.at(i).type == Constant) {
			if (output.at(i).tok == "E") {
				result.push_back(M_E);
			}
			else if (output.at(i).tok == "P") {
				result.push_back(M_PI);
			}
		}
		//if a variable (x)
		else if (output.at(i).type == Var)
		{
			result.push_back(x);
		}
	}

	return result[0];
}

double RPN::evaluate(char *input, double x)
{
	vector<Token> output;
	try {
		output = infixToPostfix(input);
	}
	catch (char *msg) {
		throw msg;
	}
	return evaluate(output, x);
}

double RPN::evaluate(char *input)		//throws
{
	try {
		return evaluate(infixToPostfix(input));
	}
	catch (char *msg) {
		throw msg;
	}
}

vector<double> RPN::evaluate(char *input, double xLower, double xUpper, double step)
{
	vector<Token> input_;
	vector<double> stepVec = getStepVec(xLower, xUpper, step);
	vector<double> results(stepVec.size());
	try {
		input_ = infixToPostfix(input);
	}
	catch (char *msg) {
		throw msg;
	}
	for (int i = 0; i < stepVec.size(); i++) {
		results[i] = evaluate(input_, stepVec[i]);
	}
	return results;
}

bool RPN::canBeEvaluatedForX(vector<Token> postfixExpression)
{
	for (int i = 0; i < postfixExpression.size(); i++) {
		if (postfixExpression.at(i).type == Var) {
			if (asciiToChar(postfixExpression.at(i).tok) != 'x') {
				return false;
			}
		}
	}
	return true;
}

char RPN::asciiToChar(string a)
{
	char b = stoi(a);
	return b;
}

unsigned int RPN::priority(string op)
{
	char op_ = asciiToChar(op);
	switch (op_) {
	case '+':
		return 1;
		break;
	case '-':
		return 1;
		break;
	case '*':
		return 2;
		break;
	case '/':
		return 2;
		break;
	case '^':
		return 3;
		break;
	default:
		return 0;
		break;
	}
	return 1;
}

unsigned int RPN::priority(char op) {
	switch (op) {
	case '+':
		return 1;
		break;
	case '-':
		return 1;
		break;
	case '*':
		return 2;
		break;
	case '/':
		return 2;
		break;
	case '^':
		return 3;
		break;
	default:
		return 0;
		break;
	}
	return 1;
}