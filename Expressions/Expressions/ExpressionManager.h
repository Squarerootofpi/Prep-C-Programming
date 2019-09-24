#ifndef EXPRESSIONMANAGER_H
#define EXPRESSIONMANAGER_H

#include "ExpressionManagerInterface.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>

using std::endl;
using std::cout;
using std::getline;
using std::istringstream;
using std::stringstream;
using std::stack;

class ExpressionManager : public ExpressionManagerInterface
{
private:
	string expression;
	string postfixValue;
	const string operators = "([{ -+  */% )]}";
	stack<string> tStack;
public:
	ExpressionManager(string inputString = "") : expression(inputString), postfixValue("") {} //constructor
	~ExpressionManager() {} //destructor

	void setExpression(string inputString) //sets expression (infix)
	{
		expression = inputString;
		postfixValue = "";
	}
	string getExpression() const //returns expression (infix)
	{
		return expression;
	}
	string getPostfix() const //returns postfixvalue
	{
		return postfixValue;
	}

	virtual std::string infix(void) //Infix function call
	{
		string returnStr;
		
		if (!isBalanced())
		{
			throw std::string("Unbalanced");
		}
		postfix(); 
		value();
		//The conversion to postfix throws all other errors, so I call it to reuse code
		returnStr = expression; //since no errors, expression is in infix already, so just output it...
		return returnStr;
	}
	
	virtual std::string postfix(void); //Returns Postfix expression, and also calculates and stores

	virtual int value(void); //Returns value of infix expression, cpp

	virtual std::string prefix(void) //Returns prefix expression
	{
		return " NOT IMPLEMENTED";
	}

	bool myPop() //pops stack, but makes sure it can before it does
	{
		if (tStack.size() == 0) return false;
		else
		{
			tStack.pop();
			return true;
		}
	}
	string myTop() //reads top of stack, but makes sure it can before it does
	{
		if (tStack.size() == 0) return "empty";
		else return tStack.top();
	}
	void emptyStack() //clears all items in stack, if any
	{
		for (int i = 0; i < tStack.size(); ++i)
		{
			tStack.pop();
		}
	}
	bool isOperator(string checkMe) //checks if input is an operator
	{
		if (operators.find(checkMe) == string::npos) return false;
		else return true;
	}
	bool isActiveOperator(string checkMe) //checks to see if it's not parentheses
	{
		if (precedence(checkMe) == 2 || precedence(checkMe) == 1) return true;
		else return false;
	}
	bool isNumber(string checkMe) //checks if input is a number
	{
		for (int i = 0; i < checkMe.size(); ++i)
		{
			if (!isdigit(checkMe.at(i))) return false;
		}
		return true;
	}
	int precedence(string checkMe) //returns the int precedence of an operator
	{
		return (operators.find(checkMe) / 4);
	}
	bool isOpeningParen(string checkMe) //checks if opening parentheses
	{
		if (precedence(checkMe) == 0) return true;
		else return false;
	}
	bool isClosingParen(string checkMe)
	{
		if (precedence(checkMe) == 3) return true;
		else return false;
	}
	bool isOperandOrOperator(string checkMe) //checks if closing parentheses
	{
		if (isOperator(checkMe) || (isNumber(checkMe))) return true;
		else return false;
	}
	/**
	Returns if expression is balanced
	*/
	bool isBalanced(); //checks if expression is balanced

	bool isPair(string left, string right) //checks if 2 parentheses are appropriate pairs
	{
		if ((operators.find(left) == 0 && operators.find(right) == 12) ||
			(operators.find(left) == 1 && operators.find(right) == 13) ||
			(operators.find(left) == 2 && operators.find(right) == 14))
		{
			return true;
		}
		else return false;
	}

	virtual std::string toString(void) const //toString, really not necessary for this lab
	{
		return expression;
	}
};




#endif