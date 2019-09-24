#ifndef MAZE_H
#define MAZE_H



#include "MazeInterface.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <istream>


using std::endl;
using std::cout;
using std::string;
using std::ostringstream;

class Maze : MazeInterface
{
private:
	int HEIGHT; //Storing so that it knows how big it is.
	int WIDTH; 
	int LAYER;
	int*** maze;
	enum blockType { OPEN = 0, BLOCKED = 1, PATH = 2, EXIT = 3, TEMPORARY = 4};

public:
	Maze(int height, int width, int layers) : HEIGHT(height), WIDTH(width), LAYER(layers) //constructor
	{
		maze = new int**[height];
		for (int i = 0; i < height; ++i) //height
		{
			maze[i] = new int*[width]; //width
			for (int z = 0; z < width; ++z) //layers
			{
				maze[i][z] = new int[layers];
			}
		}
	}
	~Maze() //destructor
	{
		for (int i = 0; i < HEIGHT; ++i) //HEIGHT
		{
			for (int z = 0; z < WIDTH; ++z) //laters
			{
				delete [] maze[i][z];
			}
			delete[] maze[i];
		}
		delete[] maze;
	}

	/** Set maze value
	   @parm height
	   @parm width
	   @parm layer
	   @parm value
	*/
	virtual void setValue(int height, int width, int layer, int value) //sets the value
	{
		maze[height][width][layer] = value;
	}

	/** Solve maze
	   @return true if solveable, else false
	*/
	virtual bool find_maze_path() //recursive wrapper
	{
		if (!find_maze_path(0, 0, 0)) throw std::string("No Solution Exists!"); 
		return true; //otherwise it is fine!
	}

	bool find_maze_path(int height, int width, int layer); //recursive function for maze

	virtual std::string toString() const; //Tostring for maze: outputs maze

};

#endif // !MAZE_H
