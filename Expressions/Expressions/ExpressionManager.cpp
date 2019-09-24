#include "ExpressionManager.h"

bool ExpressionManager::isBalanced() //returns if balanced
{
	if (expression == "") return true;
	else
	{
		emptyStack();
		string tempExpr = expression;
		string evaluOper; //operator or operand to be evaluated
		istringstream iss(tempExpr);
		while (iss >> evaluOper) //while extracting more characters
		{
			if (!isOperator(evaluOper)) continue;
			if (isActiveOperator(evaluOper)) continue;
			else if (tStack.size() == 0 && precedence(evaluOper) == 3) return false; //if closing and size is 0;
			else if (precedence(evaluOper) == 3) //compare closing and most recent opening paren.
			{
				if (isPair(tStack.top(), evaluOper))
				{
					tStack.pop();
					continue;
				}	//if pair
				else return false; 
			}
			else //it is an opening parentheses, put on stack
			{
				tStack.push(evaluOper);
			}
		}
		if (tStack.size() > 0)
		{
			emptyStack();
			return false;
		}
		else return true;
	}
}
std::string ExpressionManager::postfix(void) //Returns postfix expression, and throws errors in conversion
{
	//if (postfixValue != "") return postfixValue;
	bool success = true;
	istringstream infix(expression);
	string toEval;
	string lastEval;
	emptyStack();
	if (!isBalanced())
	{
		postfixValue = "Unbalanced";
		throw std::string("Unbalanced");
	}
	while (infix >> toEval)
	{
		if (isNumber(toEval))
		{
			postfixValue += " " + toEval;
		}
		else if (isOpeningParen(toEval))
		{
			tStack.push(toEval);
		}
		else if (isClosingParen(toEval))
		{
			/*if (tStack.size() == 0)
			{
				postfixValue = "Unbalanced";
				throw std::string("Unbalanced");
			}*/
			while (tStack.size() != 0 && (!isPair(myTop(), toEval)))
			{
				postfixValue += " " + myTop();
				myPop();
			}
			if (isPair(myTop(), toEval)) myPop();
			else
			{
				postfixValue = "Unbalanced";
				throw std::string("Unbalanced");
			}
		}
		else if (isOperator(toEval))
		{

			while (tStack.size() != 0 && (precedence(toEval) <= precedence(myTop())))
			{
				postfixValue += " " + myTop();
				myPop();

				//break;
			}
			tStack.push(toEval);
			//if (tStack.size() == 0) tStack.push(toEval);
		}
		else
		{
			postfixValue = "Illegal Operator";
			throw std::string("Illegal Operator");
		}
	}
	while (tStack.size() != 0)
	{
		postfixValue += " " + myTop();
		myPop();
	}
	return postfixValue;
}

int ExpressionManager::value(void) //Returns value of infix expression
{
	if (getPostfix() == "") postfix();
	if (getPostfix() == "Illegal Operator") throw postfixValue;
	istringstream iss(postfixValue);
	string evaluOper = "";
	string lastOper = "";
	emptyStack();
	string leftStr;
	string rightStr;
	while (iss >> evaluOper)
	{

		if (isNumber(evaluOper)) //it's an operand
		{
			tStack.push(evaluOper);
		}
		else //it's an operator
		{
			if (myTop() == "empty")
			{
				postfixValue = "Missing Operand";
				throw std::string("Missing Operand");
			}
			else
			{
				rightStr = myTop();
				myPop();
			}
			if (myTop() == "empty")
			{
				postfixValue = "Missing Operand";
				throw std::string("Missing Operand");
			}
			else
			{
				leftStr = myTop();
				myPop();
			}
			char oper = evaluOper.at(0);
			int theInt;

			stringstream ss;
			string str;
			//string illegalOperator = "Illegal Operator";
			if (oper == '-') theInt = stoi(leftStr) - stoi(rightStr);
			else if (oper == '+') theInt = stoi(leftStr) + stoi(rightStr);
			else if (oper == '*') theInt = stoi(leftStr) * stoi(rightStr);
			else if (oper == '/') theInt = stoi(leftStr) / stoi(rightStr);
			else if (oper == '%') theInt = stoi(leftStr) % stoi(rightStr);

			//push the int onto the stack.
			ss << theInt;
			str = ss.str();
			tStack.push(str);

		}
		//lastOper = evaluOper; //This is so I can make sure no
	}
	if (tStack.size() != 1)
	{
		postfixValue = "Missing Operator";
		throw std::string("Missing Operator");
	}

	return stoi(myTop());
}
