// personal touch

//memory leak checker
#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

//other includes
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

//other defines
#include "MazeInterface.h"
#include "MazeRunner.h"

//using declaration
using namespace std;

//other functions for main
void openInOut(const int argCount, char* argVec[], std::ifstream& theInStream, std::ofstream& theOutStream);

//lab07_in_01.txt lab07_out_01.txt
//lab07_in_02.txt lab07_out_02.txt
//lab07_in_03.txt lab07_out_03.txt
//lab07_in_04.txt lab07_out_04.txt
//lab07_in_05.txt lab07_out_05.txt


int main(int argc, char* argv[])
{
//check for leaks
	VS_MEM_CHECK

	ifstream inny;
	ofstream outy;

	try
	{
		openInOut(argc, argv, inny, outy);
	}
	catch(exception & e) //if there was a problem...deal with it.
	{
		cout << e.what() << endl;
	}


	int height, width, layers;
	inny >> height;
	inny >> width;
	inny >> layers;
	
	MazeRunner mazeSolver(height, width, layers);
	mazeSolver.initializeMaze(inny);

	outy << "Solve Maze:" << endl;
	outy << mazeSolver << endl;

	
	outy << "There is ";
	if(!mazeSolver.find_maze_path())
	{
		outy << "not a path!" << endl;
	}
	else
	{
		outy << "a path!" << endl;

		outy << mazeSolver;
	}


	mazeSolver.~MazeRunner();
	inny.close();
	outy.close();

	return 0;
}


/**Opens the in and out streams. Requires that argVec has a listed input and output stream to open.
If not, throws exception!
@param argCount count of arguments for use in looking through argVec
@param argVec an array of pointers to characters, *should* hold input and output filenames
@param theInStream address of already created ifstream object
@param theOutStream address of already created ofstream object
*/
void openInOut(const int argCount, char * argVec[], std::ifstream & theInStream, std::ofstream & theOutStream)
{

	//open in and out file streams
	if(argCount != 3) //check if three arguments//if so, uh-oh!
	{
		std::cerr << "Hey!  I need the input *and* output files!" << std::endl;
		throw(std::invalid_argument("Give 3 arguments"));
	}

	std::cout << "The input file is: " << argVec[1] << std::endl;
	theInStream.open(argVec[1]);

	if(!theInStream) //if it did not open correctly, uh-oh!
	{
		std::cerr << "I can't open this-->" << argVec[1] << std::endl;
		throw(std::invalid_argument("Cannot open input file"));
	}

	std::cout << "The output file is: " << argVec[2] << std::endl;
	theOutStream.open(argVec[2]);


	if(!theOutStream) //if did not open correctly, uh-oh!
	{
		theInStream.close();
		std::cerr << "I can't out to this-->" << argVec[2] << std::endl;
		throw(std::invalid_argument("Cannot open output file"));

	}

}
