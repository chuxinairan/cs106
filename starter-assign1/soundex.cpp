/*
 * TODO: remove and replace this file header comment
 * This is a .cpp file you will edit and turn in.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include <cctype>
#include <fstream>
#include <string>
#include "console.h"
#include "strlib.h"
#include "filelib.h"
#include "simpio.h"
#include "vector.h"
#include "SimpleTest.h" // IWYU pragma: keep (needed to quiet spurious warning)
using namespace std;

/* This function is intended to return a string which
 * includes only the letter characters from the original
 * (all non-letter characters are excluded)
 *
 * WARNING: The provided code is buggy!
 *
 * Use test cases to identify which inputs to this function
 * are incorrectly handled. Then, remove this comment and
 * replace it with a description of the bug you fixed.
 */
string lettersOnly(string s) {
    string result;
    for (int i = 0; i <= s.length(); i++) {
        if (isalpha(s[i])) {
            result += s[i];
        }
    }
    return result;
}

string letterTodigit(string s){
    string result;
    s = toLowerCase(s);
    for(char& ch : s){
        switch(ch){
            case 'a':case 'e':case 'i':case'o':case'u':case'h':case'w':case'y':result+='0';break;
            case 'b':case 'f':case 'p':case 'v':result+='1';break;
            case 'c':case 'g':case 'j':case'k':case'q':case's':case'x':case'z':result+='2';break;
            case 'd':case 't':result+='3';break;
            case 'l':result+='4';break;
            case 'm':case 'n':result+='5';break;
            case 'r':result+='6';break;
        }
    }
    return result;
}

string removeDuDig(string s){
    string result;
    for(int i = 0; i < s.length(); i++){
        if(s[i] == s[i+1]){}
        else {
            result += s[i];
        }
    }
    return result;
}

string substitute(string dig, string org){
    dig[0] = toupper(org[0]);
    return dig;
}

string removeZero(string s){
    string result;
    for(char& ch : s){
        if(ch != '0') result += ch;
    }
    return result;
}

string truncateOraddZero(string s){
    string result;
    int len = s.length();
    if(len > 4) result = s.substr(4);
    else if(len == 4) result = s;
    else result = s.append(4-len,'0');
    return result;
}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */


string soundex(string s) {
    /* TODO: Fill in this function. */
    string dig= removeDuDig(letterTodigit(lettersOnly(s)));
    string sub = substitute(dig,s);
    string result = truncateOraddZero(removeZero(sub));
    return result;
}


/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
void soundexSearch(string filepath) {
    // This provided code opens the specified file
    // and reads the lines into a vector of strings
    ifstream in;
    Vector<string> allNames;

    if (openFile(in, filepath)) {
        readEntireFile(in, allNames);
    }
    cout << "Read file " << filepath << ", "
         << allNames.size() << " names found." << endl;

    // The names read from file are now stored in Vector allNames
    /* TODO: Fill in the remainder of this function. */
    string name = getLine("Please input your surname here!!!(Enter to quit): ");
    while(name != ""){
        string usrSD = soundex(name);
        Vector<string> matchNames;
        cout << "Soundex code is " << usrSD << endl;
        for(string each : allNames){  //Lterate the vector
            string eachSD = soundex(each);
            if(usrSD == eachSD) matchNames.add(each);
        }
        matchNames.sort();
        cout << "Matching from database: " << matchNames << endl << endl;
        name = getLine("Please input your surname here!!!(Enter to quit): ");
    }
}


/* * * * * * Test Cases * * * * * */


//PROVIDED_TEST("Test exclude of punctuation, digits, and spaces") {
//    string s = "O'Hara";
//    string result = lettersOnly(s);
//    EXPECT_EQUAL(result, "OHara");
//    s = "Planet9";
//    result = lettersOnly(s);
//    EXPECT_EQUAL(result, "Planet");
//    s = "tl dr";
//    result = lettersOnly(s);
//    EXPECT_EQUAL(result, "tldr");
//}


//PROVIDED_TEST("Sample inputs from handout") {
//    EXPECT_EQUAL(soundex("Curie"), "C600");
//    EXPECT_EQUAL(soundex("O'Conner"), "O256");
//}

//PROVIDED_TEST("hanrahan is in lowercase") {
//    EXPECT_EQUAL(soundex("hanrahan"), "H565");
//}

//PROVIDED_TEST("DRELL is in uppercase") {
//    EXPECT_EQUAL(soundex("DRELL"), "D640");
//}

//PROVIDED_TEST("Liu has to be padded with zeros") {
//    EXPECT_EQUAL(soundex("Liu"), "L000");
//}

//PROVIDED_TEST("Tessier-Lavigne has a hyphen") {
//    EXPECT_EQUAL(soundex("Tessier-Lavigne"), "T264");
//}

//PROVIDED_TEST("Au consists of only vowels") {
//    EXPECT_EQUAL(soundex("Au"), "A000");
//}

//PROVIDED_TEST("Egilsdottir is long and starts with a vowel") {
//    EXPECT_EQUAL(soundex("Egilsdottir"), "E242");
//}

//PROVIDED_TEST("Jackson has three adjcaent duplicate codes") {
//    EXPECT_EQUAL(soundex("Jackson"), "J250");
//}

//PROVIDED_TEST("Schwarz begins with a pair of duplicate codes") {
//    EXPECT_EQUAL(soundex("Schwarz"), "S620");
//}

//PROVIDED_TEST("Van Niekerk has a space between repeated n's") {
//    EXPECT_EQUAL(soundex("Van Niekerk"), "V526");
//}

//PROVIDED_TEST("Wharton begins with Wh") {
//    EXPECT_EQUAL(soundex("Wharton"), "W635");
//}

//PROVIDED_TEST("Ashcraft is not a special case") {
//    // Some versions of Soundex make special case for consecutive codes split by hw
//    // We do not make this special case, just treat same as codes split by vowel
//    EXPECT_EQUAL(soundex("Ashcraft"), "A226");
//}

// TODO: add your test cases here



//STUDENT_TEST("Special test for lettersOnly()"){
//    string s = ".,-=+";
//    string result = lettersOnly(s);
//    EXPECT_EQUAL(result,"");
//    s = "=Nick";
//    result = lettersOnly(s);
//    EXPECT_EQUAL(result,"Nick");
//}
//STUDENT_TEST("Special test for lettersOnly()"){
//    string s = "=+Nick";
//    string result = lettersOnly(s);
//    EXPECT_EQUAL(result,"Nick");
//}

//STUDENT_TEST("Test for letterTodigit()"){
//    string s = "=Nick";
//    s=lettersOnly(s);
//    string result = letterTodigit(s);
//    EXPECT_EQUAL(result,"5022");
//    s = "";
//    s=lettersOnly(s);
//    result = letterTodigit(s);
//    EXPECT_EQUAL(result,"");
//}

//STUDENT_TEST("Test for removeDuDig()"){
//    string s = letterTodigit(lettersOnly("Curie"));
//    string result = removeDuDig(s);
//    EXPECT_EQUAL(result,"2060");
//}

//STUDENT_TEST("Test for substitute()"){
//    string name = "Nick Curie";
//    string dig= removeDuDig(letterTodigit(lettersOnly(name)));
//    string result = substitute(dig,name);
//    EXPECT_EQUAL(result,"N02060");
//}

//STUDENT_TEST("Test for removeZero()"){
//    string name = "Nick Curie";
//    string dig= removeDuDig(letterTodigit(lettersOnly(name)));
//    string sub = substitute(dig,name);
//    string result = removeZero(sub);
//    EXPECT_EQUAL(result,"N26");
//}

//STUDENT_TEST("Test for truncateOraddZero()"){
//    string name = "Zelenski";
//    string dig= removeDuDig(letterTodigit(lettersOnly(name)));
//    string sub = substitute(dig,name);
//    string result = truncateOraddZero(removeZero(sub));
//    EXPECT_EQUAL(dig,"502");
//    EXPECT_EQUAL(sub,"N02");
//    EXPECT_EQUAL(result,"N200");
//}

//STUDENT_TEST("Test for soundex()"){
//    string name = "Zelenski";
//    EXPECT_EQUAL(soundex(name),"C000");
//}

STUDENT_TEST("TIMETEST"){
    TIME_OPERATION(1,soundexSearch("res/surnames.txt"));
}
