#include "MazeRunner.h"

/**MazeRunner constructor.  Allocates space for the array.
@param height of maze.
@param width of maze.
@param layer count of maze.
*/
MazeRunner::MazeRunner(int height, int width, int layers) : mazeHeight(height), mazeWidth(width), 
 layerCount(layers), topLayer(new pathway ** [layers])
{
	for(int layer = 0; layer < layerCount; layer++)
	{
		topLayer[layer] = new pathway *[mazeHeight]; //creates the two dimensions

		for(int row = 0; row < mazeHeight; row++)
		{
			topLayer[layer][row] = new pathway[mazeWidth]; //creates the one dimension
		}
	}
}

/**MazeRunner deconstructor.  Deallocates the internal array.
*/
MazeRunner::~MazeRunner()
{
	if(topLayer == NULL)
	{
		return;
	}

	for(int layer = 0; layer < layerCount; layer++)
	{
		for(int tall = 0; tall < mazeHeight; tall++)
		{
			delete[] topLayer[layer][tall]; //deletes a row
		}
		delete[] topLayer[layer]; //deletes a layer
	}

	delete[] topLayer; //deletes layer stack
	topLayer = NULL;
}

/** Set maze value at a certain location.
@parm height
@parm width
@parm layer
@parm value
*/
void MazeRunner::setValue(int height, int width, int layer, int value)
{
	if(value != 1 && value != 0)
	{
		throw(string("Invalid value!"));
	}

	if(value == 1) //if it is a 1
	{
		topLayer[layer][height][width] = BLOCKED;
	}
	else//if it is a 0
	{
		topLayer[layer][height][width] = OPEN;
	}

}

/**Initializes the maze based on input from a stream.
@param theIn an istream object pointing at a file with a maze.
*/
void MazeRunner::initializeMaze(std::istream & theIn)
{
	int data = 0;

	for(int layer = 0; layer < layerCount; layer++)
	{
		for(int row = 0; row < mazeHeight; row++)
		{
			for(int location = 0; location < mazeWidth; location++)
			{
				theIn >> data;

				setValue(row, location, layer, data);
			}
		}
	}

}


/** Solve maze, recursive wrapper function.
@return true if solveable, else false
*/
bool MazeRunner::find_maze_path()
{
	if(find_maze_path(0, 0, 0))
	{
		return true;
	}
	return false;
}

/**Solve maze recursively.
@param layer of location to inspect.
@param row of location to inspect.
@param location of location to inspect.
@return false if location is out of bounds, blocked, or a dead end.
@return true if exit is found.
*/
bool MazeRunner::find_maze_path(const int & layer, const int & row, const int & location)
{
	const int ONE_DIFFERENCE = 1;

	// is outside
	if(layer >= layerCount || row >= mazeHeight || location >= mazeWidth
	   || layer < 0 || row < 0 || location < 0)
	{
		return false;
	}
	// is blocked //or have been there already
	else if(topLayer[layer][row][location] != OPEN)
	{
		return false;
	}
	// is end
	else if(layer == layerCount - ONE_DIFFERENCE && row == mazeHeight - ONE_DIFFERENCE && location == mazeWidth - ONE_DIFFERENCE)
	{
		topLayer[layer][row][location] = EXIT;
		return true;
	}
		
	topLayer[layer][row][location] = TEMPORARY;

	// recursive call//right, left, up, down, in, out
	if(find_maze_path(layer, row, location + ONE_DIFFERENCE))
	{
		topLayer[layer][row][location] = RIGHT;
		return true;
	}
	else if(find_maze_path(layer, row, location - ONE_DIFFERENCE))
	{
		topLayer[layer][row][location] = LEFT;
		return true;
	}
	else if(find_maze_path(layer, row - ONE_DIFFERENCE, location))
	{
		topLayer[layer][row][location] = UP;
		return true;
	}
	else if(find_maze_path(layer, row + ONE_DIFFERENCE, location))
	{
		topLayer[layer][row][location] = DOWN;
		return true;
	}
	else if(find_maze_path(layer + ONE_DIFFERENCE, row, location))
	{
		topLayer[layer][row][location] = IN;
		return true;
	}
	else if(find_maze_path(layer - ONE_DIFFERENCE, row, location))
	{
		topLayer[layer][row][location] = OUT;
		return true;
	}
	else //dead end
	{
		return false;
	}
}


/** Output maze (same order as input maze)
@return string of 2D layers
*/
string MazeRunner::toString() const
{
	std::stringstream theInfo;
	const int ONE_LESS = 1;
	pathway rightHere;
	const char OUT_VALUES[] = { '_', 'X', '?', 'P', 'E', 'U', 'D', 'L', 'R', 'I', 'O' }; 
	//{ OPEN, BLOCKED, TEMPORARY, PATH, EXIT, UP, DOWN, LEFT, RIGHT, IN, OUT };


	for(int layer = 0; layer < layerCount; layer++) //iterate through maze
	{
		theInfo << "Layer ";
		theInfo << layer + ONE_LESS << std::endl;

		for(int row = 0; row < mazeHeight; row++)
		{
			for(int location = 0; location < mazeWidth; location++)
			{
				rightHere = topLayer[layer][row][location];
		
				switch(rightHere)
				{
					case OPEN: //waterfalls through
					case TEMPORARY:
						theInfo << OUT_VALUES[OPEN];
						break;
					default: //otherwise
						theInfo << OUT_VALUES[rightHere];
						break;
				}

				if(location < mazeWidth - ONE_LESS) //no extra hanging space
				{
					theInfo << ' ';
				}

			}
			theInfo << std::endl;
		}

	}

	return theInfo.str();
}
