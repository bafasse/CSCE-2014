// hw5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Stack.h"
#include "Vector.h"
#include "Map.h"
#include <cmath>
#include <sstream>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;

int getPrecedence(const string& str)
{
	if (str == "sin") return 3;
	else if (str == "cos") return 3;
	else if (str == "tan") return 3;
	else if (str == "max") return 3;
	else if (str == "min") return 3;
	else if (str == "*") return 2;
	else if (str == "/") return 2;
	else if (str == "+") return 1;
	else if (str == "-") return 1;
	else return 0;
}


bool isBinaryOperator(const string& str)
{
	return str == "+" || str == "-" || str == "*" || str == "/" || str == "min" || str == "max";
}

bool isUnaryOperator(const string& str)
{
	return str == "sin" || str == "cos" || str == "tan";
}

bool isFunction(const string& str)
{
	return str == "sin" || str == "cos" || str == "tan" || str == "min" || str == "max";
}

bool shuntingYard(const Vector<string>& expression, const int startIndex, Vector<string>& postfix)
{
	if (expression.getSize() == 0)
		return false;

	else
	{
		Stack<string> shunt;
		string top;
		for (int i = startIndex; i < expression.getSize(); ++i)
		{
			// Left parenthesis - Push to operator shunt
			if (expression[i] == "(")
			{
				shunt.push(expression[i]);
			}

			// Right parenthesis - Pop from shunt until a matching "("
			// is found. 
			else if (expression[i] == ")")
			{
				while (shunt.top(top) && top != "(")
				{
					shunt.pop(top);
					postfix.pushBack(top);
				}

				// If we emptied the shunt, there was no matching "("
				if (shunt.isEmpty()) return false;

				// Otherwise, we found what we were looking for, so we can
				// pop the "(" from the shunt.
				else shunt.pop(top);
			}

			else if (isBinaryOperator(expression[i]) || isUnaryOperator(expression[i])) // there is an operator
			{
				// As long as the shunt is not empty and the precedence of the 
				// operator at the top of the shunt >= precedence of expression[i]
				while (!shunt.isEmpty() && getPrecedence(shunt.getTop()) >= getPrecedence(expression[i]))
				{
					shunt.pop(top);
					postfix.pushBack(top);
				}

				shunt.push(expression[i]);
			}

			else if (isUnaryOperator(expression[i]))
			{
				shunt.push(expression[i]);
			}

			else // There is a number
			{
				postfix.pushBack(expression[i]);
			}
		}
		while (shunt.pop(top))
		{
			// Check for mismatched parentheses
			if (top == "(") return false;

			postfix.pushBack(top);
		}
		return true;
	}
}

double applyBinaryOperator(const string& op, double left, double right)
{
	if (op == "+") return left + right;
	else if (op == "-") return left - right;
	else if (op == "*") return left * right;
	else if (op == "/") return left / right;
	else if (op == "min") return min(left, right);
	else if (op == "max") return max(left, right);
	else                return 0.0;
}

double applyTrig(const string& str, double left)
{
	if (str == "sin") return sin(left);
	else if (str == "cos") return cos(left);
	else if (str == "tan") return tan(left);
	else return 0.0;
}


bool evaluatePostfix(const Vector<string>& postfix, const Map<string, double>& variables, double& result)
{
	Stack<double> shunt;
	double temp;
	for (int i = 0; i < postfix.getSize(); ++i)
	{
		// If postfix[i] is an operator
		if (isBinaryOperator(postfix[i]))
		{
			double left;
			double right;

			// Pop from the shunt twice.
			if (!shunt.pop(right))
				return false;
			else if (!shunt.pop(left))
				return false;

			// Do the operation
			shunt.push(applyBinaryOperator(postfix[i], left, right));
		}

		else if (isUnaryOperator(postfix[i]))
		{
			double index;
			if (!shunt.pop(index))
				return false;
			shunt.push(applyTrig(postfix[i], index));

		}

		// postfix[i] is a variable
		else if (variables.search(postfix[i], temp))
		{
			shunt.push(temp);
		}

		else // postfix[i] is a number
		{
			shunt.push(stod(postfix[i]));
		}
	}

	// Result is on top of the shunt
	// Pop to take the result off the stsck and put it in 'result'
	return shunt.pop(result) && shunt.isEmpty();
}


int main()
{
	Map<string, double> map;
	
	while (true)
	{
		double result;
		string str;
		cout << "Enter a mathematical expression (press q to quit): ";
		getline(cin, str);

		if (str == "q") break;
		
		Vector<string> expression;
		stringstream ss(str);
		while (ss >> str)
			expression.pushBack(str);

		Vector<string> postfix;
		if (expression.getSize() >= 3 && expression[1] == "=")
		{
			if (shuntingYard(expression, 2, postfix))
			{
				if (evaluatePostfix(postfix, map, result))
				{
					map.insert(expression[0], result);
					cout << result << endl;
				}
				else
				{
					cout << "Malformed expression." << endl;
					continue;
				}
			}
			else
			{
				cout << "Mismatched parentheses." << endl;
				continue;
			}
		}

		else
		{
			if (!shuntingYard(expression, 0, postfix))
			{
				cout << "Mismatched parentheses!" << endl;
				continue;
			}

			if (!evaluatePostfix(postfix, map, result))
			{
				cout << "Expression was malformed." << endl;
				continue;
			}
			cout << result << endl;
		}
	}
	return 0;
}

