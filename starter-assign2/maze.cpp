// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include <iostream>
#include <fstream>
#include "error.h"
#include "filelib.h"
#include "grid.h"
#include "maze.h"
#include "mazegraphics.h"
#include "queue.h"
#include "set.h"
#include "stack.h"
#include "vector.h"
#include "testing/SimpleTest.h"
using namespace std;


/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
Set<GridLocation> generateValidMoves(Grid<bool>& maze, GridLocation cur) {
    Set<GridLocation> neighbors;
    /* TODO: Fill in the remainder of this function. */

    int Nrow = cur.row - 1;
    if(Nrow >= 0) {
        if(maze[Nrow][cur.col]) { //If north can pass
            neighbors.add({Nrow,cur.col});
        }
    }

    Nrow = cur.row + 1;
    if(Nrow < maze.numRows()) {
        if(maze[Nrow][cur.col]) { //If south can pass
            neighbors.add({Nrow,cur.col});
        }
    }


    int Ncol = cur.col + 1;
    if(Ncol < maze.numCols()) {
        if(maze[cur.row][Ncol]) { //If east can pass
            neighbors.add({cur.row,Ncol});
        }
    }

    Ncol = cur.col - 1;
    if(Ncol >= 0) {
        if(maze[cur.row][Ncol]) { //If west can pass
            neighbors.add({cur.row,Ncol});
        }
    }
    return neighbors;
}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
void validatePath(Grid<bool>& maze, Stack<GridLocation> path) {
    GridLocation mazeExit = {maze.numRows()-1,  maze.numCols()-1};

    if (path.peek() != mazeExit) {
        error("Path does not end at maze exit");
    }
    /* TODO: Fill in the remainder of this function. */
    Set<GridLocation> Prepath;
    GridLocation mazeEntry = {0,0};
    GridLocation pathEntry;
    do {   //According the original code, resume the path can not be an empty
        GridLocation Current = path.pop();
        Set<GridLocation> ValidMoves = generateValidMoves(maze,Current);  //Generate valid moves
        if(!path.isEmpty()){
            if(!ValidMoves.contains(path.peek())) {
                error("Path is not valid");  //If path is not valid!!!
            }
        }
        else pathEntry = Current;  //Reserve the path entry
        if(Prepath.contains(Current)) {  //If path is accessed!!!
            error("Path is accessed");
        }
        Prepath.add(Current);  //Input the current location to Prepath
    } while(!path.isEmpty());
    if(pathEntry != mazeEntry) {  //If the entry is not the maze entry!!!!
        error("Entry is not the maze entry");
    }
    /* If you find a problem with the path, call error() to report it.
     * If the path is a valid solution, then this function should run to completion
     * without throwing any errors.
     */
}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
Stack<GridLocation> solveMaze(Grid<bool>& maze) {
    MazeGraphics::drawGrid(maze);
    Stack<GridLocation> path;
    /* TODO: Fill in the remainder of this function. */
    GridLocation mazeExit = {maze.numRows()-1,maze.numCols()-1};
    MazeGraphics::highlightPath(path,"green");
    path = {{0,0}};
    Queue<Stack<GridLocation>> Paths = {path};
    while(!Paths.isEmpty()){
        path = Paths.dequeue();
        MazeGraphics::highlightPath(path,"green");
        if(path.peek() == mazeExit) break;  //Check this is a solution
        Set<GridLocation> validMoves = generateValidMoves(maze,path.peek());  //Store the neighbors
        for(GridLocation each : validMoves){
            Stack<GridLocation> Test = path;
            Stack<GridLocation> Copy = path;
            int test = 1;
            while(!Test.isEmpty()){  //Check all generated moves are new
                if(Test.pop() == each){
                    test = 0;
                    break;
                }
            }
            if(test == 1) {  //If this is a new node, append to path and put the path in Queue.
                Copy.push(each);
                Paths.enqueue(Copy);
            }
        }
    }
    return path;
}

/*
 * The given readMazeFile function correctly reads a well-formed
 * maze from a file.
 *
 * This provided function is fully correct. You do not need to change
 * any of the code in this function.
 */
void readMazeFile(string filename, Grid<bool>& maze) {
    /* The following code reads data from the file into a Vector
     * of strings representing the lines of the file.
     */
    ifstream in;

    if (!openFile(in, filename))
        error("Cannot open file named " + filename);

    Vector<string> lines;
    readEntireFile(in, lines);

    /* Now that the file data has been read into the Vector, populate
     * the maze grid.
     */
    int numRows = lines.size();        // rows is count of lines
    int numCols = lines[0].length();   // cols is length of line
    maze.resize(numRows, numCols);     // resize grid dimensions

    for (int r = 0; r < numRows; r++) {
        if (lines[r].length() != numCols) {
            error("Maze row has inconsistent number of columns");
        }
        for (int c = 0; c < numCols; c++) {
            char ch = lines[r][c];
            if (ch == '@') {        // wall
                maze[r][c] = false;
            } else if (ch == '-') { // corridor
                maze[r][c] = true;
            } else {
                error("Maze location has invalid character: '" + charToString(ch) + "'");
            }
        }
    }
}

/* The given readSolutionFile correctly reads a path from a file.
 *
 * This provided function is fully correct. You do not need to change
 * any of the code in this function.
 */
void readSolutionFile(string filename, Stack<GridLocation>& soln) {
    ifstream in;

    if (!openFile(in, filename)) {
        error("Cannot open file named " + filename);
    }

    if (!(in >> soln)) {// if not successfully read
        error("Maze solution did not have the correct format.");
    }
}


/* * * * * * Test Cases * * * * * */

//PROVIDED_TEST("generateValidMoves on location in the center of 3x3 grid with no walls") {
//    Grid<bool> maze = {{true, true, true},
//                       {true, true, true},
//                       {true, true, true}};
//    GridLocation center = {1, 1};
//    Set<GridLocation> expected = {{0, 1}, {1, 0}, {1, 2}, {2, 1}};

//    EXPECT_EQUAL(generateValidMoves(maze, center), expected);
//}

//PROVIDED_TEST("generateValidMoves on location on the side of 3x3 grid with no walls") {
//    Grid<bool> maze = {{true, true, true},
//                       {true, true, true},
//                       {true, true, true}};
//    GridLocation side = {0, 1};
//    Set<GridLocation> expected = {{0,0}, {0,2}, {1, 1}};

//    EXPECT_EQUAL(generateValidMoves(maze, side), expected);
//}

//PROVIDED_TEST("generateValidMoves on corner of 2x2 grid with walls") {
//    Grid<bool> maze = {{true, false},
//                       {true, true}};
//    GridLocation corner = {0, 0};
//    Set<GridLocation> expected = {{1, 0}};

//    EXPECT_EQUAL(generateValidMoves(maze, corner), expected);
//}

//PROVIDED_TEST("validatePath on correct solution") {
//    Grid<bool> maze = {{true, false},
//                       {true, true}};
//    Stack<GridLocation> soln = { {0 ,0}, {1, 0}, {1, 1} };

//    EXPECT_NO_ERROR(validatePath(maze, soln));
//}

//PROVIDED_TEST("validatePath on correct solution loaded from file for medium maze") {
//    Grid<bool> maze;
//    Stack<GridLocation> soln;
//    readMazeFile("res/5x7.maze", maze);
//    readSolutionFile("res/5x7.soln", soln);

//    EXPECT_NO_ERROR(validatePath(maze, soln));
//}

//PROVIDED_TEST("validatePath on correct solution loaded from file for large maze") {
//    Grid<bool> maze;
//    Stack<GridLocation> soln;
//    readMazeFile("res/25x33.maze", maze);
//    readSolutionFile("res/25x33.soln", soln);

//    EXPECT_NO_ERROR(validatePath(maze, soln));
//}

//PROVIDED_TEST("validatePath on invalid path should raise error") {
//    Grid<bool> maze = {{true, false},
//                       {true, true}};
//    Stack<GridLocation> not_end_at_exit = { {1, 0}, {0, 0} };
//    Stack<GridLocation> not_begin_at_entry = { {1, 0}, {1, 1} };
//    Stack<GridLocation> go_through_wall = { {0 ,0}, {0, 1}, {1, 1} };
//    Stack<GridLocation> teleport = { {0 ,0}, {1, 1} };
//    Stack<GridLocation> revisit = { {0 ,0}, {1, 0}, {0, 0}, {1, 0}, {1, 1} };

//    EXPECT_ERROR(validatePath(maze, not_end_at_exit));
//    EXPECT_ERROR(validatePath(maze, not_begin_at_entry));
//    EXPECT_ERROR(validatePath(maze, go_through_wall));
//    EXPECT_ERROR(validatePath(maze, teleport));
//    EXPECT_ERROR(validatePath(maze, revisit));
//}

PROVIDED_TEST("solveMaze on file 5x7") {
    Grid<bool> maze;
    readMazeFile("res/5x7.maze", maze);
    Stack<GridLocation> soln = solveMaze(maze);

    EXPECT_NO_ERROR(validatePath(maze, soln));
}

PROVIDED_TEST("solveMaze on file 21x23") {
    Grid<bool> maze;
    readMazeFile("res/21x23.maze", maze);
    Stack<GridLocation> soln = solveMaze(maze);

    EXPECT_NO_ERROR(validatePath(maze, soln));
}

// TODO: add your test cases here

//STUDENT_TEST("generateValidMoves() to test"){
//    Grid<bool> maze = {{true,true,true},
//                       {true,true,true},
//                       {true,true,true}};
//    GridLocation example = {0,2};
//    Set<GridLocation> expected = {{1,2},{0,1}};
//    EXPECT_EQUAL(expected,generateValidMoves(maze,example));
//}

//STUDENT_TEST("validatePath() to test"){
//    Grid<bool> maze = {{true,true,true},
//                        {true,false,false},
//                        {true,true,true}};
//    Stack<GridLocation> path1 = {{0,0},{1,0},{2,0},{2,1},{2,2}};
//    EXPECT_NO_ERROR(validatePath(maze,path1));
//}
//STUDENT_TEST("validatePath() to test"){
//    Grid<bool> maze = {{true,true,true},
//                       {true,true,false},
//                       {false,false,true}};
//    Stack<GridLocation> path1 = {{0,0},{1,1},{2,2}};
//    EXPECT_ERROR(validatePath(maze,path1));
//}

//STUDENT_TEST("solveMaze on file 21x23") {
//    Grid<bool> maze;
//    readMazeFile("res/21x23.maze", maze);
//    TIME_OPERATION(1,solveMaze(maze));
//}
//STUDENT_TEST("solveMaze on file 21x23") {
//    Grid<bool> maze;
//    readMazeFile("res/21x23.maze", maze);
//    TIME_OPERATION(2,solveMaze2(maze));
//}
