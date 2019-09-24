#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK;
#endif




#include "Maze.h"



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

	int height;
	int width;
	int layers;
	
	inputFile >> height; 
	inputFile >> width;
	inputFile >> layers;
	
	Maze maze(height, width, layers);


	int inputLine; //inputFile

	//read into maze
	for (int l = 0; l < layers; ++l)
	{
		//outputFile << "Layer " << l << endl;
		for (int h = 0; h < height; ++h)
		{
			for (int w = 0; w < width; ++w)
			{
				inputFile >> inputLine;
				maze.setValue(h, w, l, inputLine);
			}
		}
	}

	outputFile << "Solve Maze:" << endl;
	outputFile << maze.toString();

	try 
	{
		maze.find_maze_path();
		outputFile << endl << "Solution:" << endl;
		outputFile << maze.toString();
	}
	catch (std::string s)
	{
		outputFile << s << endl;
	}
	catch (std::exception ex)
	{
		outputFile << endl << ex.what();
	}
	catch (...)
	{
		outputFile << endl << "Unknown error";
	}

	inputFile.close();
	outputFile.close();


	return 0;
}