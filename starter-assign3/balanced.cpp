/*
 * TODO: remove and replace this file header comment
 * You will edit and turn in this file.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include <iostream>    // for cout, endl
#include <string>      // for string class
#include "recursion.h"
#include "testing/SimpleTest.h"

using namespace std;

/*
 * TODO: Replace this comment with a descriptive function
 * header comment.
 */
string operatorsFrom(string str) {
    /* TODO: Implement this function. */
    if(str == "") return "";
    if(str[0] == '{' || str[0] == '}' ||
       str[0] == '[' || str[0] == ']' ||
       str[0] == '(' || str[0] == ')' ) {
        return str[0] + operatorsFrom(str.substr(1));
    } else return operatorsFrom(str.substr(1));
}

/*
 * TODO: Replace this comment with a descriptive function
 * header comment.
 */
bool operatorsAreMatched(string ops) {
    /* TODO: Implement this function. */
    if (ops == ""){
        return true;
    } else if (ops.find("()") != -1) {
        ops.replace(ops.find("()") ,2 ,"");
        return operatorsAreMatched(ops);
    } else if (ops.find("{}") != -1) {
        ops.replace(ops.find("{}") ,2 ,"");
        return operatorsAreMatched(ops);
    } else if (ops.find("[]") != -1) {
        ops.replace(ops.find("[]") ,2 ,"");
        return operatorsAreMatched(ops);
    } else {
        return false;
    }
}

/*
 * The isBalanced function assumes correct implementation of
 * the above two functions operatorsFrom and operatorsMatch.
 * It uses operatorsFrom to extract the operator characters
 * from the input string and then confirms that those
 * operators are balanced by using operatorsMatch.
 * You should not modify the provided code in the isBalanced
 * function.  If the previous two functions have been implemented
 * correctly, the provided isBalanced will correctly report whether
 * the input string has balanced bracketing operators.
 */
bool isBalanced(string str) {
    string ops = operatorsFrom(str);
    return operatorsAreMatched(ops);
}


/* * * * * * Test Cases * * * * * */

//PROVIDED_TEST("operatorsFrom on simple example") {
//    EXPECT_EQUAL(operatorsFrom("vec[3]"), "[]");
//}

//PROVIDED_TEST("operatorsAreMatched on simple example") {
//    EXPECT(operatorsAreMatched("{}"));
//}

//PROVIDED_TEST("isBalanced on example from writeup") {
//    string example ="int main() { int x = 2 * (vec[2] + 3); x = (1 + random()); }";
//    EXPECT(isBalanced(example));
//}

//PROVIDED_TEST("isBalanced on non-balanced examples from writeup") {
//    EXPECT(!isBalanced("( ( [ a ] )"));
//    EXPECT(!isBalanced("3 ) ("));
//    EXPECT(!isBalanced("{ ( x } y )"));
//}

//STUDENT_TEST("op"){
//    EXPECT_EQUAL(operatorsFrom("123{[dda}"),"{[}");
//    EXPECT_EQUAL(operatorsFrom(""),"");
//}
//STUDENT_TEST("operatorsAreMatched") {
//    EXPECT(!operatorsAreMatched("{}][")); //too much right parentheses
//    EXPECT(!operatorsAreMatched("((){}"));  //too much left parentheses
//    EXPECT(!operatorsAreMatched("[(}]"));  //bad match
//    EXPECT(!operatorsAreMatched("[a]"));  //other char
//    EXPECT(operatorsAreMatched("[(){}]"));  //match true
//}
