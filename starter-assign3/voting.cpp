// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include <iostream>    // for cout, endl
#include <string>      // for string class
#include "voting.h"
#include "testing/SimpleTest.h"
using namespace std;

int computePowerIndexesHelper(Vector<int>& blocks, int& total, int target, int otherSum, int index);

// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
Vector<int> computePowerIndexes(Vector<int>& blocks)
{
    Vector<int> result;
    // TODO your code here
    int total = 0;
    for(int& i : blocks){
        total += i;
    }
//    blocks.sort();  //Assume already soeted
    result.add(computePowerIndexesHelper(blocks, total, 0, 0, 0));
    for(int i = 1; i < blocks.size(); i++){
        if(blocks[i] == blocks[i-1]) {
            result.add(result[i-1]);
        } else{
            result.add(computePowerIndexesHelper(blocks, total, i, 0, 0));
        }
    }
    int totalC = 0;  //caculate total of all critical votes
    for(int& i : result){
        totalC += i;
    }
    for(int i = 0; i < result.size(); i++){
        result[i] = result[i]*100/totalC;
    }
    return result;
}

int computePowerIndexesHelper(Vector<int>& blocks, int& total, int target, int otherSum, int index){
    if(index == blocks.size()){
        return 0;
    }
    int exclude = 0;
    int include = 0;
    //exclude [index]
    exclude += computePowerIndexesHelper(blocks, total, target, otherSum, index+1);
    //include [index]
    if(target != index) {
        otherSum += blocks[index];
        if(2*otherSum <= total && 2*(otherSum+blocks[target]) > total) {
            include++;
        }
        include += computePowerIndexesHelper(blocks, total, target, otherSum, index+1);
    }
    return exclude + include;
}
/* * * * * * Test Cases * * * * * */

//PROVIDED_TEST("Test power index, blocks 50-49-1") {
//    Vector<int> blocks = {50, 49, 1};
//    Vector<int> expected = {60, 20, 20};
//    EXPECT_EQUAL(computePowerIndexes(blocks), expected);
//}

//PROVIDED_TEST("Test power index, blocks Hempshead 1-1-3-7-9-9") {
//    Vector<int> blocks = {1, 1, 3, 7, 9, 9};
//    Vector<int> expected = {0, 0, 0, 33, 33, 33};
//    EXPECT_EQUAL(computePowerIndexes(blocks), expected);
//}

//PROVIDED_TEST("Test power index, blocks CA-TX-NY 55-38-39") {
//    Vector<int> blocks = {55, 38, 29};
//    Vector<int> expected = {33, 33, 33};
//    EXPECT_EQUAL(computePowerIndexes(blocks), expected);
//}

//PROVIDED_TEST("Test power index, blocks CA-TX-GA 55-38-16") {
//    Vector<int> blocks = {55, 38, 16};
//    Vector<int> expected = {100, 0, 0};
//    EXPECT_EQUAL(computePowerIndexes(blocks), expected);
//}

//PROVIDED_TEST("Test power index, blocks EU post-Nice") {
//    // Estonia is one of those 4s!!
//    Vector<int> blocks = {29,29,29,29,27,27,14,13,12,12,12,12,12,10,10,10,7,7,7,7,7,4,4,4,4,4,3};
//    Vector<int> expected = {8, 8, 8, 8, 7, 7, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0};
//    TIME_OPERATION(blocks.size(), computePowerIndexes(blocks));
//    EXPECT_EQUAL(computePowerIndexes(blocks), expected);
//}

//PROVIDED_TEST("Time power index operation") {
//    Vector<int> blocks;
//    for (int i = 0; i < 15; i++) {
//        blocks.add(randomInteger(1, 10));
//    }
//    TIME_OPERATION(blocks.size(), computePowerIndexes(blocks));
//}


STUDENT_TEST("Time power index operation") {
    Vector<int> blocks;
    for (int i = 0; i < 20; i++) {
        blocks.add(randomInteger(1, 15));
    }
    blocks.sort();
    TIME_OPERATION(blocks.size(), computePowerIndexes(blocks));
}

STUDENT_TEST("Time power index operation") {
    Vector<int> blocks;
    for (int i = 0; i < 30; i++) {
        blocks.add(randomInteger(1, 5));
    }
    blocks.sort();
    TIME_OPERATION(blocks.size(), computePowerIndexes(blocks));
}
