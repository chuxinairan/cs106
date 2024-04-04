#include "labyrinth.h"
#include "demo/MazeGenerator.h"
#include "testing/SimpleTest.h"
using namespace std;

/* Change kYourName constant to your full name.
 *
 * WARNING: Once you've set set this constant and started exploring your labyrinth,
 * do NOT edit the value of kYourName. Changing kYourName will change which
 * maze you get back, which might invalidate all your hard work!
 */
const string kYourName = "TODO";

/* Change this constant to the path out of your labyrinth. */
const string kPathOutOfNormalMaze = "TODO";

/**
 * Given a location in a maze, returns whether the given sequence of
 * steps will let you escape the maze.
 *
 * To escape the maze, you need to collect all items in the `needs` set.
 * You can only take steps in the four cardinal directions,
 * and you can't move in directions that don't exist in the maze.
 */

bool canGoNext(MazeCell*& loc, char nextStep){
    if(nextStep == 'E'){
        if(loc->east != nullptr){
            loc = loc->east;
        } else {
//            error("east is not valid");
            return false;
        }
    } else if(nextStep == 'N'){
        if(loc->north != nullptr){
            loc = loc->north;
        } else {
//            error("north is not valid");
            return false;
        }
    } else if(nextStep == 'W'){
        if(loc->west != nullptr){
            loc = loc->west;
        } else {
//            error("west is not valid");
            return false;
        }
    } else if(nextStep == 'S'){
        if(loc->south != nullptr){
            loc = loc->south;
        } else {
//            error("south is not valid");
            return false;
        }
    } else {
        error("not a legal character");
        return false;
    }
    return true;
}

void checkContent(MazeCell* loc, Set<string>& needs){
    if(needs.contains(loc->contents)){
        needs.remove(loc->contents);
    }
    return;
}

bool isPathToFreedom(MazeCell* start, string moves, Set<string> needs) {
    /* TODO: Your code here */
    // special case : if start is NULL
    if(start == nullptr){
        error("start is NULL");
    }
    checkContent(start, needs);
    //check every characters in moves
    for(char nextStep : moves){
        if(!canGoNext(start, nextStep)){
            return false;
        }
        checkContent(start, needs);
        if(needs.isEmpty()){
            return true;
        }
    }
    if(needs.isEmpty()){
        return true;
    } else{
        return false;
    }
}

/* * * * * * Test Cases Below This Point * * * * * */

PROVIDED_TEST("Check paths in the sample from writeup") {
    Set<string> allThree = {"Spellbook", "Potion", "Wand"};
    auto maze = toMaze({"* *-W *",
                        "| |   |",
                        "*-* * *",
                        "  | | |",
                        "S *-*-*",
                        "|   | |",
                        "*-*-* P"});

    /* These paths are the ones in the handout. They all work. */
    EXPECT(isPathToFreedom(maze[2][2], "ESNWWNNEWSSESWWN", allThree));
    EXPECT(isPathToFreedom(maze[2][2], "SWWNSEENWNNEWSSEES", allThree));
    EXPECT(isPathToFreedom(maze[2][2], "WNNEWSSESWWNSEENES", allThree));

    /* This path works to pick up just potion */
    EXPECT(isPathToFreedom(maze[2][2], "ESNW", {"Potion"}));

    /* This path doesn't work, since doesn't pick up all items. */
    EXPECT(!isPathToFreedom(maze[2][2], "ESNW", allThree));

    /* This path doesn't work, cannot walk through walls. */
    EXPECT(!isPathToFreedom(maze[2][2], "NNWWSSSEEE", allThree));
}

PROVIDED_TEST("Works when start on an item") {
    auto maze = toMaze({"P-S-W"});

    EXPECT(isPathToFreedom(maze[0][0], "E", {"Potion"}));
    EXPECT(isPathToFreedom(maze[0][1], "W", {"Potion", "Spellbook"}));
}

PROVIDED_TEST("Reports errors if given illegal characters") {
    auto maze = toMaze({"P-S-W"});

    EXPECT_ERROR(isPathToFreedom(maze[0][0], "Q", {"Wand"}));
    EXPECT_ERROR(isPathToFreedom(maze[0][0], "Ee", {"Wand"}));
}

PROVIDED_TEST("Escape from your personal labyrinth!") {
    Set<string> allThree = {"Spellbook", "Potion", "Wand"};
    /* A maze for you to escape from. This maze will be personalized
     * based on the constant kYourName.
     */
    EXPECT(kYourName != "TODO");
    MazeCell* startLocation = mazeFor(kYourName);

    /* Set a breakpoint here. As a reminder, the labyrinth you
     * get will be personalized to you, so don't start exploring the labyrinth
     * unless you've edited the constant kYourName to include your name(s)!
     * Otherwise, you'll be escaping the wrong labyrinth.
     */
    EXPECT(kPathOutOfNormalMaze != "TODO");
    EXPECT(isPathToFreedom(startLocation, kPathOutOfNormalMaze, allThree));
}

