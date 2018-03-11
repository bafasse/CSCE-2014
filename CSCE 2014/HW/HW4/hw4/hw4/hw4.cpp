// hw4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Stack.h"
#include "Vector.h"
#include <string>
#include <iostream>
using namespace std;

int getPrecedence(const string& str)
{
	if      (str == "*") return 2;
	else if (str == "/") return 2;
	else if (str == "+") return 1;
	else if (str == "-") return 1;
	else return 0;
}

bool shuntingYard(const Vector<string>& expression, Vector<string>& postfix)
{
	if (expression.getSize() == 0)
		return false;

	else
	{
		Stack<string> stack;
		for (int i = 0; i < expression.getSize(); ++i)
		{
			if (expression[i] == "(")
			{
				stack.push(expression[i]);
			}

			else if (expression[i] == ")")
			{
				string temp = stack.getTop();
				while (!stack.isEmpty() && stack.getTop() != "(")
				{
					postfix.pushBack(temp);
					stack.pop(temp);
				}
				stack.pop(temp);
			}

			else if (expression[i] == "+" || expression[i] == "-" || expression[i] == "/" || expression[i] == "*") // there is an operator
			{
				// As long as the stack is not empty and the precedence of the 
				// operator at the top of the stack >= precedence of expression[i]
				while (!stack.isEmpty() && getPrecedence(stack.getTop()) >= getPrecedence(expression[i]))
				{
					string temp = expression[i];
					stack.pop(temp);
				}

				stack.push(expression[i]);
			}

			else // There is a number
			{
				postfix.pushBack(expression[i]);
			}
		}
		while (!stack.isEmpty())
		{
			string top;
			stack.pop(top);
			postfix.pushBack(top);

		}
		return true;
	}
}

bool evaluatePostfix(const Vector<string>& postfix, double& result)
{
		Stack<double> stack;
		for (int i = 0; i < postfix.getSize(); ++i)
		{
			// If postfix[i] is an operator
			if (postfix[i] == "+" || postfix[i] == "-" || postfix[i] == "*" || postfix[i] == "/")
			{
				// Pop from the stack twice.
				double left;
				double right;

				if (!stack.pop(right))
					return false;
				else if (!stack.pop(left))
					return false;


				// Do the operation
				if (postfix[i] == "+")
					stack.push(left + right);
				else  if (postfix[i] == "-")
					stack.push(left - right);
				else if (postfix[i] == "*")
					stack.push(left * right);
				else if (postfix[i] == "/")
					stack.push(left / right);
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
	string token;
	cout << "Enter the equation: ";
	while (cin >> token) 
	{
		expression.pushBack(token); 
	}
	expression.print();

	Vector<string> postfix;
	if (shuntingYard(expression, postfix))
	{
		cout << "POSTFIX: ";
		postfix.print();
	}
	else cout << "EMPTY EXPRESSION" << endl;

	double result;
	if (evaluatePostfix(postfix, result))
	{
		cout << "RESULT: " << result << endl;
	}
	else cout << "MALFORMED EXPRESSION." << endl;

    return 0;
}

