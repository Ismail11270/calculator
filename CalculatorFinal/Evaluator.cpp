#define _USE_MATH_DEFINES
#include "Evaluator.h"
#include <vector>

using namespace std;

double Evaluator::Sin(double angle)
{
	return sin(angle*(M_PI / 180));
}
double Evaluator::Cos(double angle)
{
	return cos(angle*(M_PI / 180));
}
double Evaluator::Tan(double angle)
{
	return tan(angle*(M_PI / 180));
}


vector<double> Evaluator::getStepVec(double xLower, double xUpper, double step)
{
	const double n = abs(xLower - xUpper) / step;
	std::vector<double> stepVec(n + 1);
	for (int i = 0; i < int(n + 1); i++)
	{
		stepVec[i] = xLower + step*i;
	}
	//stepVec.push_back(xUpper);
	return stepVec;
}


double Evaluator::add(double a, double b)
{
	return a + b;
}

double Evaluator::substruct(double a, double b)
{
	return b - a;
}

double Evaluator::multiply(double a, double b)
{
	return a * b;
}

double Evaluator::divide(double a, double b)
{
	if (a == 0) throw "Division by zeor error!";
	else return b / a;
}

double Evaluator::exponentiate(double a, double b)
{
	return pow(b, a);
}


Evaluator::Evaluator()
{
}


Evaluator::~Evaluator()
{
}
