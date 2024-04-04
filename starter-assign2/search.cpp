// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include <iostream>
#include <fstream>
#include "error.h"
#include "filelib.h"
#include "map.h"
#include "search.h"
#include "set.h"
#include "simpio.h"
#include "strlib.h"
#include "vector.h"
#include "testing/SimpleTest.h"
using namespace std;


// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
string cleanToken(string s)
{
    int len = s.length();
    int startPun = 0;
    int endPun = 0;
    for(int i = 0; i <= len; i++){
        if(ispunct(s[i])){
            startPun++;
        }
        if(isalpha(s[i]) || isdigit(s[i]))break;
    }
    if(startPun == len) return "";  //If string made of punctuations
    for(int i = len-1; i > startPun; i--){
        if(ispunct(s[i])){
            endPun++;
        }
        if(isalpha(s[i]) || isdigit(s[i]))break;
    }
    s = s.substr(startPun,len-startPun-endPun);
    int label = 0;
    for(int i = 0; i <= s.length(); i++){
        if(isalpha(s[i])){
            label = 1;
            break;
        }
    }
    if(label == 0) return "";  //If none of a character is alpha
    return toLowerCase(s);
}

// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
Set<string> gatherTokens(string text)
{
    Set<string> tokens;
    Vector<string> contains = stringSplit(text," ");
    for(string& each : contains){
        each = cleanToken(each);
        if(each != "") tokens.add(each);
    }
    return tokens;
}

// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
int buildIndex(string dbfile, Map<string, Set<string>>& index)
{
    // read the database file
    ifstream in;
    if (!openFile(in, dbfile))
        error("Cannot open file named " + dbfile);
    Vector<string> lines;
    readEntireFile(in, lines);

    int rowsNum = lines.size();
    for(int i = 1; i < rowsNum; i+=2){
        Set<string> keywords = gatherTokens(lines[i]);  //Split contents of every URL
        for(const string& each : keywords){
            if(index.containsKey(each)) {
                index[each].add(lines[i-1]);
            }
            else {
                index.put(each,{lines[i-1]});
            }
        }
    }
    return rowsNum / 2;
}

// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
Set<string> findQueryMatches(Map<string, Set<string>>& index, string query)
{
    Set<string> result;
    // TODO: your code here
    Vector<string> terms = stringSplit(query," ");
    Set<string> temp;
    for(string& each : terms){
        if(each[0] == '+'){  //select intersection
            each = cleanToken(each);
            temp *= index[each];
        }
        else if(each[0] == '-'){  //select diference
            each = cleanToken(each);
            temp -= index[each];
        }
        else {  //put selected results into finally result
            result += temp;
            each = cleanToken(each);
            temp = index[each];
        }
    }  //put last selested result into finally result
    result += temp;
    return result;
}

// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
void searchEngine(string dbfile)
{
    // TODO: your code here
    Map<string,Set<string>> index;
    int pagesNum = buildIndex(dbfile,index);
    int wordsNum = index.size();
    cout << "Indexd " << pagesNum << " containing " << wordsNum << " unique terms." << endl  << endl;
    string query = getLine("You can find what you want here!!!!");
    while(query != ""){
        Set<string> resultURLs = findQueryMatches(index,query);
        int matchNum = resultURLs.size();
        cout << "Found " << matchNum << " matching pages." << endl;
        cout << resultURLs << endl  << endl;
        query = getLine("You can find what you want here:");
    }
    cout << "All done!" << endl;
}

/* * * * * * Test Cases * * * * * */

//PROVIDED_TEST("cleanToken on strings with no punctuation at beginning or end") {
//    EXPECT_EQUAL(cleanToken("hello"), "hello");
//    EXPECT_EQUAL(cleanToken("WORLD"), "world");
//    EXPECT_EQUAL(cleanToken("CS*106B"), "cs*106b");
//}

//PROVIDED_TEST("cleanToken on strings with some punctuation at beginning and end") {
//    EXPECT_EQUAL(cleanToken("/hello/"), "hello");
//    EXPECT_EQUAL(cleanToken("~woRLD!"), "world");
//}

//PROVIDED_TEST("cleanToken on non-word strings (no letters)"){
//    EXPECT_EQUAL(cleanToken("106"), "");
//    EXPECT_EQUAL(cleanToken("~!106!!!"), "");
//}

//PROVIDED_TEST("gatherTokens from simple string") {
//    Set<string> expected = {"go", "gophers"};
//    EXPECT_EQUAL(gatherTokens("go go go gophers"), expected);
//}

//PROVIDED_TEST("gatherTokens correctly cleans tokens") {
//    Set<string> expected = {"i", "love", "cs*106b"};
//    EXPECT_EQUAL(gatherTokens("I _love_ CS*106B!"), expected);
//}

//PROVIDED_TEST("gatherTokens from seuss, 5 unique words, mixed case, punctuation") {
//    Set<string> tokens = gatherTokens("One Fish Two Fish *Red* fish Blue fish ** 10 RED Fish?");
//    EXPECT_EQUAL(tokens.size(), 5);
//    EXPECT(tokens.contains("fish"));
//    EXPECT(!tokens.contains("Fish"));
//    EXPECT_EQUAL(tokens,{"one","fish","two","red","blue"});
//}

//PROVIDED_TEST("buildIndex from tiny.txt, 4 pages, 11 unique tokens") {
//    Map<string, Set<string>> index;
//    int nPages = buildIndex("res/tiny.txt", index);
//    EXPECT_EQUAL(nPages, 4);
//    EXPECT_EQUAL(index.size(), 11);
//    EXPECT(index.containsKey("fish"));
//}

//PROVIDED_TEST("findQueryMatches from tiny.txt, single word query") {
//    Map<string, Set<string>> index;
//    buildIndex("res/tiny.txt", index);
//    Set<string> matchesRed = findQueryMatches(index, "red");
//    EXPECT_EQUAL(matchesRed.size(), 2);
//    EXPECT(matchesRed.contains("www.dr.seuss.net"));
//    Set<string> matchesHippo = findQueryMatches(index, "hippo");
//    EXPECT(matchesHippo.isEmpty());
//}

//PROVIDED_TEST("findQueryMatches from tiny.txt, compound queries") {
//    Map<string, Set<string>> index;
//    buildIndex("res/tiny.txt", index);
//    Set<string> matchesRedOrFish = findQueryMatches(index, "red fish");
//    EXPECT_EQUAL(matchesRedOrFish.size(), 4);
//    Set<string> matchesRedAndFish = findQueryMatches(index, "red +fish");
//    EXPECT_EQUAL(matchesRedAndFish.size(), 1);
//    Set<string> matchesRedWithoutFish = findQueryMatches(index, "red -fish");
//    EXPECT_EQUAL(matchesRedWithoutFish.size(), 1);
//}


// TODO: add your test cases here

//STUDENT_TEST("cleanToken()") {
//    EXPECT_EQUAL(cleanToken("H  "), "h");
//}

//STUDENT_TEST("gatherTokens()") {
//    Set<string> expected = {"cs","a5*0","mit"};
//    EXPECT_EQUAL(gatherTokens("{CS a5*0 ---Mit---}"), expected);
//}

//STUDENT_TEST("buildIndex()") {
//    Map<string, Set<string>> index;
//    buildIndex("res/tiny.txt", index);
//    Vector<string> keys = {"milk","fish","bread","5lb_m&ms","red","green","blue","one","two","i","eat"};
//    keys.sort();
//    EXPECT_EQUAL(keys,index.keys());
//    Set<string> URLs = {"www.shoppinglist.com","www.dr.seuss.net","www.bigbadwolf.com"};
//    EXPECT_EQUAL(URLs,index["fish"]);
//}
//STUDENT_TEST("buildIndex from tiny.txt, 4 pages, 11 unique tokens") {
//    Map<string, Set<string>> index;
//    int nPages;
//    TIME_OPERATION(1,buildIndex("res/website.txt", index));
//    nPages = buildIndex("res/website.txt", index);
//    EXPECT_EQUAL(nPages, 34);
//    EXPECT(index.containsKey("single-stepping"));
//    Set<string> URLs = {"http://cs106b.stanford.edu/class/cs106b/assignments/2-adt/warmup.html"};
//    EXPECT_EQUAL(URLs,index["single-stepping"]);
//}

//STUDENT_TEST("findQueryMatches()") {
//    Map<string, Set<string>> index;
//    buildIndex("res/website.txt", index);
//    Set<string> matchesRedOrFish = findQueryMatches(index, "Single-stepping Programming +Abstractions -abstraction");
//    Set<string> expected = {"http://cs106b.stanford.edu/class/cs106b/assignments/2-adt/warmup.html"};
//    EXPECT_EQUAL(matchesRedOrFish, expected);
//}

//STUDENT_TEST("searchEngine()") {
//    Map<string, Set<string>> index;
//    buildIndex("res/website.txt", index);
//    Set<string> matchesRedOrFish = findQueryMatches(index, "cs107 stanford -qt");
//    Set<string> expected = {"http://cs106b.stanford.edu/class/cs106b/assignments/2-adt/warmup.html"};
//    EXPECT_EQUAL(matchesRedOrFish, expected);
//}
