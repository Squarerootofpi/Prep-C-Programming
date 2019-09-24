
#include "ExpressionManager.h"

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK;
#endif

//Most #includes are inside the ExpressionManager.h file


int main(int argc, char * argv[])
{
	VS_MEM_CHECK


		std::ifstream inputFile(argv[1]);
	if (!inputFile)
	{
		std::cout << "input opening error" << std::endl;
		return 1;
	}
	std::ofstream outputFile(argv[2]);
	if (!outputFile)
	{
		std::cout << "output opening error" << std::endl;
		return 1;
	}

	ExpressionManager exprMan;

	string tempOutputString;
	string infixInput;
	//int finalValue = 0; 

	
	string line, command;
	while (getline(inputFile, line))
	{
		try
		{
			if (line.size() == 0) continue;
			istringstream iss(line);
			iss >> command;
			
			//outputFile << iss.str() << " this is the iss string" << endl; //fixme
			if (command == "Expression:")
			{
				outputFile << "Expression:";
				//infixInput = iss.str();
				getline(iss, infixInput);
				exprMan.setExpression(infixInput);
				outputFile << exprMan.getExpression() << endl;
				
				continue;
			}
			else if (command == "Infix:")
			{
				outputFile << "Infix:";
				outputFile << exprMan.infix() << endl; //FIXINPUT with function call
			}
			else if (command == "Value:")
			{
				outputFile << "Value:";
				outputFile << " " << exprMan.value() << endl /*<< exprMan.getExpression()*/ << endl; //FIXME
			}
			else if (command == "Postfix:")
			{
				outputFile << "Postfix:";
				outputFile << " " << exprMan.getPostfix() << endl; //FIXINPUT with function call
			}
			else if (command == "Prefix:")
			{
				outputFile << "Prefix:";
				outputFile << exprMan.prefix() << endl; //FIXINPUT with function call
			}
			else
			{
				outputFile << "I have no idea what you want me to do." << endl;
			}
		}
		catch (std::string s) //Catches exceptions, allows program to continue to run.
		{
			outputFile << " " << s << endl;
			if (command == "Value:") outputFile << endl;
		}
	}
	
	inputFile.close();
	outputFile.close();

	return 0;
}