#pragma once
#include <string>
#include <vector>

using namespace std;
class Evaluator
{
public:
	double Sin(double);
	double Cos(double);
	double Tan(double);
	double add(double, double);
	double substruct(double, double);
	double multiply(double, double);
	double divide(double, double);
	double exponentiate(double, double);
	vector<double> getStepVec(double xLower, double xUpper, double step);
	Evaluator();
	~Evaluator();
};

