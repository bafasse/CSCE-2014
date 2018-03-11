// hw5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include "Stack.h"
//#include "Vector.h"
#include <cmath>
#include <stack>
#include <vector>
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

bool shuntingYard(const vector<string>& expression, vector<string>& postfix)
{
		stack<string> stack;
		string top;
		for (int i = 0; i < expression.size(); ++i)
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
				while (!stack.empty() && stack.top() != "(")
				{
					stack.pop();
					postfix.push_back(top);
				}

				// If we emptied the stack, there was no matching "("
				if (stack.empty())
				{
					cout << "herre" << endl; // not here
					return false;
				}

				// Otherwise, we found what we were looking for, so we can
				// pop the "(" from the stack.
				else stack.pop();
			}

			else if (isOperator(expression[i])) // there is an operator
			{
				// As long as the stack is not empty and the precedence of the 
				// operator at the top of the stack >= precedence of expression[i]
					while (!stack.empty() && getPrecedence(stack.top()) >= getPrecedence(expression[i]))
					{
						postfix.push_back(stack.top());
						stack.pop();
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
				postfix.push_back(expression[i]);
			}
		}
		while (!stack.empty())
		{
			top = stack.top();
			stack.pop();

			// Check for mismatched parentheses
			if (top == "(") return false;
			postfix.push_back(top);
		}
		return true;
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

bool evaluatePostfix(const vector<string>& postfix, double& result)
{
	stack<double> stack;
	for (int i = 0; i < postfix.size(); ++i)
	{
		// If postfix[i] is an operator
		if (isOperator(postfix[i]))
		{
			if (stack.size() >= 2)
			{
				double right = stack.top();
				stack.pop();
				double left = stack.top();
				stack.pop();

				// Pop from the stack twice.
				// Do the operation
				stack.push(left + right);
			}
			else return false;
		}

		else if (isTrig(postfix[i]))
		{
			if (stack.size() >= 1)
			{
				double index = stack.top();
				stack.pop();
				stack.push(applyTrig(postfix[i], index));
			}
			else return false;

		}

		else if (isMaxMin(postfix[i]))
		{
			if (stack.size() >= 1)
			{
				double left = stack.top();
				stack.pop();
				double right = stack.top();
				stack.pop();
				stack.push(applyMaxMin(postfix[i], left, right));
			}
			else return false;
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
	stack.pop();
	return true;
}

void print(vector<string> str, int size)
{
	for (int i = 0; i < size; ++i)
		cout << str[i] << " ";
	cout << endl;
}

int main()
{
	vector<string> expression; 
	string str; 
	cout << "Enter a mathematical expression: ";
	getline(cin, str);          
	
	stringstream ss(str); 
	while (ss >> str)     
		expression.push_back(str);

	cout << endl << "Expression: ";
	print(expression, expression.size());
	vector<string> postfix;
	if (shuntingYard(expression, postfix))
	{
		cout << "Postfix:    ";
		print(postfix, postfix.size());
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

