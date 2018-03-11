// hw5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Stack.h"
#include "Vector.h"
#include <cmath>
#include <sstream>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;

int getPrecedence(const string& str)
{
	if (str == "*") return 2;
	else if (str == "/") return 2;
	else if (str == "+") return 1;
	else if (str == "-") return 1;
	else return 0;
}

bool isOperator(const string& str)
{
	return str == "+" || str == "-" || str == "*" || str == "/";
}

bool isTrig(const string& str)
{
	return str == "sin" || str == "cos" || str == "tan";
}

bool isMaxMin(const string& str)
{
	return str == "max" || str == "min";
}

bool shuntingYard(const Vector<string>& expression, Vector<string>& postfix)
{
	if (expression.getSize() == 0)
		return false;

	else
	{
		Stack<string> stack;
		string top;
		for (int i = 0; i < expression.getSize(); ++i)
		{
			// Left parenthesis - Push to operator stack
			if (expression[i] == "(")
			{
				stack.push(expression[i]);
			}

			// Right parenthesis - Pop from stack until a matching "("
			// is found. 
			else if (expression[i] == ")")
			{
				while (stack.top(top) && top != "(")
				{
					stack.pop(top);
					postfix.pushBack(top);
				}

				// If we emptied the stack, there was no matching "("
				if (stack.isEmpty()) return false;

				// Otherwise, we found what we were looking for, so we can
				// pop the "(" from the stack.
				else stack.pop(top);
			}

			else if (isOperator(expression[i])) // there is an operator
			{
				// As long as the stack is not empty and the precedence of the 
				// operator at the top of the stack >= precedence of expression[i]
				while (!stack.isEmpty() && getPrecedence(stack.getTop()) >= getPrecedence(expression[i]))
				{
					stack.pop(top);
					postfix.pushBack(top);
				}

				stack.push(expression[i]);
			}

			else if (isTrig(expression[i]))
			{
				stack.push(expression[i]);
			}

			else if (isMaxMin(expression[i]))
				stack.push(expression[i]);

			else // There is a number
			{
				postfix.pushBack(expression[i]);
			}
		}
		while (stack.pop(top))
		{
			// Check for mismatched parentheses
			if (top == "(") return false;

			postfix.pushBack(top);
		}
		return true;
	}
}

double applyOperator(const string& op, double left, double right)
{
	if (op == "+") return left + right;
	else if (op == "-") return left - right;
	else if (op == "*") return left * right;
	else if (op == "/") return left / right;
	else                return 0.0;
}

double applyTrig(const string& str, double left)
{
	if (str == "sin") return sin(left);
	else if (str == "cos") return cos(left);
	else if (str == "tan") return tan(left);
	else return 0.0;
}

double applyMaxMin(const string& str, double left, double right)
{
	if (str == "max") return max(left, right);
	else if (str == "min") return min(left, right);
	else return 0.0;
}

bool evaluatePostfix(const Vector<string>& postfix, double& result)
{
	Stack<double> stack;
	for (int i = 0; i < postfix.getSize(); ++i)
	{
		// If postfix[i] is an operator
		if (isOperator(postfix[i]))
		{
			double left;
			double right;

			// Pop from the stack twice.
			if (!stack.pop(right))
				return false;
			else if (!stack.pop(left))
				return false;


			// Do the operation
			stack.push(applyOperator(postfix[i], left, right));
		}

		else if (isTrig(postfix[i]))
		{
			double index;
			if (!stack.pop(index))
				return false;
			stack.push(applyTrig(postfix[i], index));

		}

		else if (isMaxMin(postfix[i]))
		{
			double left;
			double right;

			if (!stack.pop(right))
				return false;
			else if (!stack.pop(left))
				return false;
			stack.push(applyMaxMin(postfix[i], left, right));
		}

		else if (postfix[i] == "(" || postfix[i] == ")")
			continue;

		else // postfix[i] is a number
		{
			stack.push(stoi(postfix[i]));
		}
	}

	// Result is on top of the stack
	// Pop to take the result off the stsck and put it in 'result'
	stack.pop(result);
	return true;
}

int main()
{
	Vector<string> expression; 
	string str; 
	cout << "Enter a mathematical expression: ";
	getline(cin, str);          
	
	stringstream ss(str); 
	while (ss >> str)     
		expression.pushBack(str);

	cout << endl << "Expression: ";
	expression.print();
	Vector<string> postfix;
	if (shuntingYard(expression, postfix))
	{
		cout << "Postfix:    ";
		postfix.print();
	}
	else
	{
		cout << "Mismatched parentheses!" << endl;
		return 1;
	}

	double result;
	if (evaluatePostfix(postfix, result))
		cout << "Result:     " << result << endl;
	else
	{
		cout << "Expression was malformed." << endl;
		return 1;
	}
	return 0;
}

