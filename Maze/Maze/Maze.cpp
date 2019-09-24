#include "Maze.h"

std::string Maze::toString() const //tostring for the maze, outputs maze
{
	ostringstream oss;
	for (int l = 0; l < LAYER; ++l)
	{
		oss << "Layer " << l + 1 << endl;
		for (int h = 0; h < HEIGHT; ++h)
		{
			for (int w = 0; w < WIDTH; ++w)
			{
				if (maze[h][w][l] == OPEN || maze[h][w][l] == TEMPORARY)
				{
					oss << "_ ";
				}
				else if (maze[h][w][l] == BLOCKED)
				{
					oss << "X ";
				}
				else if (maze[h][w][l] == PATH)
				{
					oss << "2 ";
				}
				else
				{
					oss << maze[h][w][l] << " "; //exit
				}
			}
			oss << endl;
		}
	}
	return oss.str();
}
bool Maze::find_maze_path(int height, int width, int layer) //recursive findmaze function
{
	if (height < 0 || width < 0 || layer < 0 ||
		height >= HEIGHT || width >= WIDTH || layer >= LAYER)
	{
		return false; //out of bounds
	}
	else if (maze[height][width][layer] != OPEN) return false; // Cell is on barrier or dead end.
	else if (height == HEIGHT - 1 && width == WIDTH - 1 && layer == LAYER - 1) //if exit
	{
		maze[height][width][layer] = EXIT; //this is the path!
		return true; //this is the maze exit
	}
	else
	{
		maze[height][width][layer] = PATH; //assume you are on the path
	//left (width - 1), right (width + 1), 
	//up (height - 1), down (height + 1), 
	//out (layer - 1), and in (layer + 1)
		if (
			find_maze_path(height, width - 1, layer) ||
			find_maze_path(height, width + 1, layer) ||
			find_maze_path(height - 1, width, layer) ||
			find_maze_path(height + 1, width, layer) ||
			find_maze_path(height, width, layer - 1) ||
			find_maze_path(height, width, layer + 1)
			)
		{
			return true;
		}
		else
		{
			maze[height][width][layer] = TEMPORARY; //dead end
			return false;
		}
	}
	return false; //if all else fails...
}