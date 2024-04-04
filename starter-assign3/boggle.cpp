/*
 * TODO: remove and replace this file header comment
 * You will edit and turn in this file.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include <iostream>    // for cout, endl
#include <string>      // for string class
#include "backtracking.h"
#include "gridlocation.h"
#include "grid.h"
#include "set.h"
#include "lexicon.h"
#include "testing/SimpleTest.h"
using namespace std;

Set<string> scoreBoardHelper(Grid<char>& board, Lexicon& lex, Set<string>& entireWords, GridLocation loc, string SoFar);
Set<GridLocation> generateValidMove(Grid<char>& board, GridLocation loc);

/*
 * TODO: Replace this comment with a descriptive function
 * header comment.
 */
int points(string str) {
    /* TODO: Implement this function. */
    int len = str.length();
    if(len == 1 || len == 2 || len == 3){
        return 0;
    } else {
        return len - 3;
    }
}

/*
 * TODO: Replace this comment with a descriptive function
 * header comment.
 */
int scoreBoard(Grid<char>& board, Lexicon& lex) {
    /* TODO: Implement this function. */
    int score = 0;
    Set<string> entireWords = {};
    for(int i = 0; i < board.numRows(); i++){
        for(int j = 0; j < board.numCols(); j++){
            if(board[i][j] != '_'){
                string begin = charToString(board[i][j]);
                entireWords = scoreBoardHelper(board, lex, entireWords, {i,j}, begin);
            }
        }
    }
    for(const string& each : entireWords){
        score += points(each);
    }
    return score;
}

Set<string> scoreBoardHelper(Grid<char>& board, Lexicon& lex, Set<string>& entireWords, GridLocation loc, string SoFar){
    if(!lex.containsPrefix(SoFar)){  //base1
        return entireWords;
    }
    int len = SoFar.length();
    if(len > 3){
        if(lex.contains(SoFar)){
            entireWords.add(SoFar);
        }
    }
    Set<GridLocation> ValidMoves = generateValidMove(board,loc);
    if(ValidMoves.isEmpty()){   //base2
        return entireWords;
    }
    //start recursive
    char temp = board[loc];   //store current letter
    board[loc] = '_';
    for(GridLocation each : ValidMoves){
        string next = SoFar + board[each];
        entireWords = scoreBoardHelper(board, lex, entireWords, each, next);
    }
    board[loc] = temp;
    return entireWords;
}

Set<GridLocation> generateValidMove(Grid<char>& board, GridLocation loc){
    if(board[loc] == '_'){
        error("loc is not Valid");
    }
    int up = loc.row - 1;
    int down = loc.row + 1;
    int left = loc.col - 1;
    int right = loc.col + 1;
    Set<GridLocation> ValidMove;
    bool UpOK = (up != -1);
    bool DownOK = (down != board.numRows());
    bool LeftOK = (left != -1);
    bool RightOK = (right != board.numCols());
    if(LeftOK) {
        if(board[loc.row][left] != '_') ValidMove.add({loc.row,left});
    }
    if(RightOK) {
        if(board[loc.row][right] != '_') ValidMove.add({loc.row,right});
    }
    if(DownOK){
        if(board[down][loc.col] != '_') ValidMove.add({down,loc.col});
        if(LeftOK){
            if(board[down][left] != '_') ValidMove.add({down,left});
        }
        if(RightOK){
            if(board[down][right] != '_') ValidMove.add({down,right});
        }
    }
    if(UpOK){
        if(board[up][loc.col] != '_') ValidMove.add({up,loc.col});
        if(LeftOK){
            if(board[up][left] != '_') ValidMove.add({up,left});
        }
        if(RightOK){
            if(board[up][right] != '_') ValidMove.add({up,right});
        }
    }
    return ValidMove;
}

/* * * * * * Test Cases * * * * * */

/* Test helper function to return shared copy of Lexicon. Use to
 * avoid (expensive) re-load of word list on each test case. */
static Lexicon& sharedLexicon() {
    static Lexicon lex("res/EnglishWords.txt");
    return lex;
}

//PROVIDED_TEST("Load shared Lexicon, confirm number of words") {
//    Lexicon lex = sharedLexicon();
//    EXPECT_EQUAL(lex.size(), 127145);
//}

//PROVIDED_TEST("Test point scoring") {
//    EXPECT_EQUAL(points("and"), 0);
//    EXPECT_EQUAL(points("quad"), 1);
//    EXPECT_EQUAL(points("quint"), 2);
//    EXPECT_EQUAL(points("sextet"), 3);
//    EXPECT_EQUAL(points("seventh"), 4);
//    EXPECT_EQUAL(points("supercomputer"), 10);
//}

PROVIDED_TEST("Test scoreBoard, board contains no words, score of zero") {
    Grid<char> board = {{'B','C','D','F'}, //no vowels, no words
                        {'G','H','J','K'},
                        {'L','M','N','P'},
                        {'Q','R','S','T'}};
    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 0);
}

PROVIDED_TEST("Test scoreBoard, board contains one word, score of 1") {
    Grid<char> board = {{'C','_','_','_'},
                        {'Z','_','_','_'},
                        {'_','A','_','_'},
                        {'_','_','R','_'}};
    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 1);
}

PROVIDED_TEST("Test scoreBoard, alternate paths for same word, still score of 1") {
    Grid<char> board = {{'C','C','_','_'},
                        {'C','Z','C','_'},
                        {'_','A','_','_'},
                        {'R','_','R','_'}};
    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 1);
}

PROVIDED_TEST("Test scoreBoard, small number of words in corner of board") {
    Grid<char> board = {{'L','I','_','_'},
                        {'M','E','_','_'},
                        {'_','S','_','_'},
                        {'_','_','_','_'}};
    Set<string> words = {"SMILE", "LIMES", "MILES", "MILE", "MIES", "LIME", "LIES", "ELMS", "SEMI"};

    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()),  2 + 2 + 2 + 1 + 1 + 1 + 1 + 1 + 1);
}

PROVIDED_TEST("Test scoreBoard, full board, small number of words") {
    Grid<char> board = {{'E','Z','R','R'},
                        {'O','H','I','O'},
                        {'N','J','I','H'},
                        {'Y','A','H','O'}};
    Set<string> words = { "HORIZON", "OHIA", "ORZO", "JOHN", "HAJI"};

    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 4 + 1 + 1 + 1 + 1);
}

PROVIDED_TEST("Test scoreBoard, full board, medium number of words") {
    Grid<char> board = {{'O','T','H','X'},
                        {'T','H','T','P'},
                        {'S','S','F','E'},
                        {'N','A','L','T'}};

    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 76);
}

PROVIDED_TEST("Test scoreBoard, full board, large number of words") {
    Grid<char> board = {{'E','A','A','R'},
                        {'L','V','T','S'},
                        {'R','A','A','N'},
                        {'O','I','S','E'}};

    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 234);
}

//STUDENT_TEST("generateValidMove()"){
//    Grid<char> board = {{'C','H','H','X'},
//                        {'T','_','_','P'},
//                        {'S','S','F','E'},
//                        {'N','A','L','T'}};
//    GridLocation loc = {2,2};
//    Set<GridLocation> expected = {{3,3},{3,2},{2,3},{2,1},{3,1},{1,3}};
//    EXPECT_EQUAL(generateValidMove(board,loc),expected);
//}

//STUDENT_TEST("Test scoreBoard, full board, large number of words") {
//    Grid<char> board = {{'A','_','_','S'},
//                        {'A','_','_','H'},
//                        {'H','_','_','A'},
//                        {'S','_','_','A'}};

//    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 1);
//}
