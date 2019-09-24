#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK;
#endif


#include "Deque.h"
#include "Station.h"



int main(int argc, char* argv[])
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


	Station<size_t> theStation; //implementing as size_t, per instructions

	string inputLine; //inputFile

	while (inputFile >> inputLine)
	{
		try
		{
			if (inputLine == "Add:station")
			{
				outputFile << inputLine << " ";

				inputFile >> inputLine;
				outputFile << inputLine;
				outputFile << " " << theStation.addCar(stoi(inputLine)) << endl;
			}
			else if (inputLine == "Add:queue")
			{
				outputFile << inputLine << " ";
				outputFile << theStation.addQueue() << endl;
			}
			else if (inputLine == "Add:stack")
			{
				outputFile << inputLine << " ";
				outputFile << theStation.addStack() << endl;
			}
			else if (inputLine == "Remove:station")
			{
				outputFile << inputLine << " ";
				outputFile << theStation.removeCar() << endl;
			}
			else if (inputLine == "Remove:queue")
			{
				outputFile << inputLine << " ";
				outputFile << theStation.removeQueue() << endl;
			}
			else if (inputLine == "Remove:stack")
			{
				outputFile << inputLine << " ";
				outputFile << theStation.removeStack() << endl;
			}
			else if (inputLine == "Top:station")
			{
				outputFile << inputLine;
				outputFile << " " << theStation.topCar() << endl;
			}
			else if (inputLine == "Top:stack")
			{
				outputFile << inputLine << " ";
				outputFile << theStation.topStack() << endl;
			}
			else if (inputLine == "Top:queue")
			{
				outputFile << inputLine << " ";
				outputFile << theStation.topQueue() << endl;
			}
			else if (inputLine == "Size:queue")
			{
				outputFile << inputLine << " ";
				outputFile << theStation.sizeQueue() << endl;
			}
			else if (inputLine == "Size:stack")
			{
				outputFile << inputLine << " ";
				outputFile << theStation.sizeStack() << endl;
			}
			else if (inputLine.substr(0, 5) == "Find:")
			{
				outputFile << inputLine << " ";
				outputFile << theStation.find(stoi(inputLine.substr(5, 1))) << endl;
			}
			else if (inputLine == "Train:")
			{
				outputFile << inputLine;
				outputFile << " " << theStation.toString() << endl;
			}
			else
			{
				outputFile << "No such command." << endl;
			}
		}
		catch (std::string s)
		{
			outputFile << s << endl;
		}
	}





	/*
	Add:station
	Add:queue
	Add:stack
	
	Remove:station
	Remove:queue
	Remove:stack

	Top:station
Top:queue
Top:stack

Size:queue
Size:stack

Find: <data>

	Train car enters the station turntable. 
Train car is removed from the turntable and pushed to the Queue roundhouse. 
Train car is removed from the turntable and pushed to the Stack roundhouse.	OK 
Turntable empty! 
Turntable occupied!
	A train car is removed from the turntable and pushed into the train vector. 
A train car is removed from Queue roundhouse and moved to the station turntable. 
A train car is removed from Stack roundhouse and moved to the station turntable.	
OK 
Turntable empty! 
Turntable occupied! 
Queue empty! 
Stack empty!
	Display the current train car on station turntable, 
Display the train car at head of Queue roundhouse. 
Display the train car at head of Stack roundhouse.	 

	Output number of train cars in Queue/Stack roundhouse.	Size of Queue 
Size of Stack
	Find and display the current location and position of a car in the station data structures (turntable, queue, stack, or vector).	Turntable 
Queue[<index>] 
Stack[<index>] 
Train[<index>] 
Not Found!
Train:	Output the contents of the train vector.	List of train cars leaving the station.
	*/


	inputFile.close();
	outputFile.close();


	return 0;
}