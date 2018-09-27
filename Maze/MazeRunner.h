//personal touch
#ifndef MAZE_RUNNER_H_
#define MAZE_RUNNER_H_

#include "MazeInterface.h"
#include <sstream>
#include <stdexcept>

class MazeRunner : public MazeInterface
{
private:
	enum pathway { OPEN, BLOCKED, TEMPORARY, PATH, EXIT, UP, DOWN, LEFT, RIGHT, IN, OUT };

	int mazeHeight;
	int mazeWidth;
	int layerCount;

	pathway *** topLayer; //first point to layers, then to two-dimensions, then to one location

	bool find_maze_path(const int & layer, const int & row, const int & location);

public:
	MazeRunner(int height, int width, int layers);
	~MazeRunner();

	void setValue(int height, int width, int layer, int value);
	void initializeMaze(std::istream & theIn);
	bool find_maze_path();

	string toString() const;

	/**Required friend ostream insertion operator.
	allows output through insertion.
	@param theOut address of ostream object.
	@param theRunner address of MazeRunner object.
	@return modified ostream object.
	*/
	friend std::ostream & operator<< (std::ostream & theOut, MazeRunner & theRunner)
	{
		theOut << theRunner.toString();
		return theOut;
	}
};


#endif
