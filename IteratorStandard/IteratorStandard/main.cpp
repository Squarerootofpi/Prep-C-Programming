
#include "MyArray.h"

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK;
#endif

bool const isPrime(size_t number); //Calculates if number passed in is prime

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

	//Declare Class Array

	MyArray<size_t> numbers(MAX_ARRAY_SIZE);

	outputFile << "myArray:";
	size_t tempInt = 0;

	while (!inputFile.eof())
	{
		inputFile >> tempInt;
		numbers.push_back(tempInt);
	}

	outputFile << numbers << endl << endl; //This should output tostring, the whole length
	

	MyArray<size_t>::Iterator iter = numbers.begin(); //Create here so can  output the iterator toString
	outputFile << "ITERATORS:" << endl;
	outputFile << "begin(): " << numbers.begin();
	outputFile << "end(): " << numbers.end() << endl;


	outputFile << "SEQUENTIAL:" << endl;
	for (size_t i = 0; iter != numbers.end(); ++iter)
	{
		if (((i % 10) == 0) && (i != 0))
		{
			outputFile << endl;
		}
		outputFile << *iter << " ";
		++i;
	}
	outputFile << endl << endl;


	outputFile << "PRIME:" << endl;
	iter = numbers.begin();

	for (size_t i = 0; iter != numbers.end(); ++iter)
	{
		if ((*iter > 1) && isPrime(*iter)) 
		{
			if (((i % 10) == 0) && (i != 0))
			{
			outputFile << endl;
			}
		outputFile << *iter << " ";
		++i;
		}
	}
	outputFile << endl << endl;
	
	iter = numbers.begin();

	outputFile << "COMPOSITE:" << endl;
	for (size_t i = 0; iter != numbers.end(); ++iter)
	{
		if ((*iter >= 0) && (!isPrime(*iter)))
		{
			if (((i % 10) == 0) && (i != 0))
			{
				outputFile << endl;
			}
			outputFile << *iter << " ";
			++i;
		}
	}
	outputFile << endl << endl;


	inputFile.close();
	outputFile.close();

	return 0;
}
//Calculate if prime!
bool const isPrime(size_t number)
{
	bool isPrime = true;
	for (size_t i = 2; i <= number / 2; ++i)
	{
		if (number % i == 0)
		{
			isPrime = false;
			break;
		}
	}
	return isPrime;
}