/*
 * TODO: remove and replace this file header comment
 * You will edit and turn in this file.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include <iostream>    // for cout, endl
#include "queue.h"
#include "testing/SimpleTest.h"
using namespace std;

/*
 * TODO: Replace this comment with a descriptive function
 * header comment.
 */
Queue<int> binaryMerge(Queue<int> a, Queue<int> b) {
    Queue<int> result;
    /* TODO: Implement this function. */
    while(!a.isEmpty()&&!b.isEmpty()){  //Neither is empty
        int A = a.peek();
        int B = b.peek();
        if(A<B) {
            result.enqueue(A);
            a.dequeue();
        } else if(A==B) {
            result.enqueue(A);
            result.enqueue(B);
            a.dequeue();
            b.dequeue();
        } else {
            result.enqueue(B);
            b.dequeue();
        }
    }
    if(a.isEmpty()){  //Queue a is empty
        while(!b.isEmpty()) {
            result.enqueue(b.dequeue());
        }
    } else if(b.isEmpty()) {  //Queue b is empty
        while(!a.isEmpty()){
            result.enqueue(a.dequeue());
        }
    }
    return result;
}

void sortedCheck(Queue<int> a, Queue<int> b){
    int len = a.size();
   if(len != 0 && len !=1){
        for(int i = 0; i < len-1; i++){
            int current = a.dequeue();
            if(current > a.peek()) {
                error("No sorted a Queue!!!");
            }
        }
    }
    len = b.size();
    if(len != 0 && len !=1){
        for(int i = 0; i < len-1; i++){
            int current = b.dequeue();
            if(current > b.peek()) {
                error("No sorted b Queue!!!");
            }
        }
    }

}
/*
 * This function assumes correct functionality of the previously
 * defined binaryMerge function and makes use of this function to
 * iteratively merge a collection of sequences, starting off with
 * an empty sequence and progressively merging in one sequence at
 * a time. This function is provided for you fully implemented –
 * it does not need to modified at all.
 */
Queue<int> naiveMultiMerge(Vector<Queue<int>>& all) {
    Queue<int> result;

    for (Queue<int>& q : all) {
        result = binaryMerge(q, result);
    }
    return result;
}

/*
 * TODO: Replace this comment with a descriptive function
 * header comment.
 */
Queue<int> recMultiMerge(Vector<Queue<int>>& all) {
    Queue<int> result;
    /* TODO: Implement this function. */
    int Vsize = all.size();
    if(Vsize == 0){
        return {};
    }else if(Vsize == 1) {
        return all[0];
    }
    int dividedsize = Vsize/2;
    Vector<Queue<int>> left = all.subList(0,dividedsize);
    Vector<Queue<int>> right = all.subList(dividedsize, Vsize - dividedsize);
    result = binaryMerge(recMultiMerge(left),recMultiMerge(right));
    return result;
}


/* * * * * * Test Cases * * * * * */

Queue<int> createSequence(int size);
void distribute(Queue<int> input, Vector<Queue<int>>& all);

//PROVIDED_TEST("binaryMerge, two short sequences") {
//    Queue<int> a = {2, 4, 5};
//    Queue<int> b = {1, 3, 3};
//    Queue<int> expected = {1, 2, 3, 3, 4, 5};
//    EXPECT_EQUAL(binaryMerge(a, b), expected);
//    EXPECT_EQUAL(binaryMerge(b, a), expected);
//}

//PROVIDED_TEST("naiveMultiMerge, small collection of short sequences") {
//    Vector<Queue<int>> all = {{3, 6, 9, 9, 100},
//        {1, 5, 9, 9, 12},
//        {5},
//        {},
//        {-5, -5},
//        {3402}
//    };
//    Queue<int> expected = {-5, -5, 1, 3, 5, 5, 6, 9, 9, 9, 9, 12, 100, 3402};
//    EXPECT_EQUAL(naiveMultiMerge(all), expected);
//}

//PROVIDED_TEST("recMultiMerge, compare to naiveMultiMerge") {
//    int n = 20;
//    Queue<int> input = createSequence(n);
//    Vector<Queue<int>> all(n);
//    distribute(input, all);
//    EXPECT_EQUAL(recMultiMerge(all), naiveMultiMerge(all));
//}

//PROVIDED_TEST("Time binaryMerge operation") {
//    int n = 1000000;
//    Queue<int> a = createSequence(n);
//    Queue<int> b = createSequence(n);
//    TIME_OPERATION(a.size() + b.size(), binaryMerge(a, b));
//}

//PROVIDED_TEST("Time naiveMultiMerge operation") {
//    int n = 11000;
//    int k = n/10;
//    Queue<int> input = createSequence(n);
//    Vector<Queue<int>> all(k);
//    distribute(input, all);
//    TIME_OPERATION(input.size(), naiveMultiMerge(all));
//}
//PROVIDED_TEST("Time recMultiMerge operation") {
//    int n = 90;
//    int k = n/10;
//    Queue<int> input = createSequence(n);
//    Vector<Queue<int>> all(k);
//    distribute(input, all);
//    TIME_OPERATION(input.size(), recMultiMerge(all));
//}


/* Test helper to fill queue with sorted sequence */
Queue<int> createSequence(int size) {
    Queue<int> q;
    for (int i = 0; i < size; i++) {
        q.enqueue(i);
    }
    return q;
}

/* Test helper to distribute elements of sorted sequence across k sequences,
   k is size of Vector */
void distribute(Queue<int> input, Vector<Queue<int>>& all) {
    while (!input.isEmpty()) {
        all[randomInteger(0, all.size()-1)].enqueue(input.dequeue());
    }
}

//STUDENT_TEST("binaryMerge") {
//    Queue<int> a = {1,2,3};
//    Queue<int> b = {1,2,5};
//    Queue<int> expected = {1,1,2,2,3,5};
//    sortedCheck(a,b);
//    EXPECT_EQUAL(binaryMerge(a, b), expected);
//    EXPECT_EQUAL(binaryMerge(b, a), expected);
//}
//STUDENT_TEST("binaryMerge time test(1)") {
//    Queue<int> a = createSequence(10000);
//    Queue<int> b = createSequence(15000);
//    sortedCheck(a,b);
//    TIME_OPERATION(10000+15000,binaryMerge(a,b));
//}
//STUDENT_TEST("binaryMerge time test(2)") {
//    Queue<int> a = createSequence(100000);
//    Queue<int> b = createSequence(150000);
//    sortedCheck(a,b);
//    TIME_OPERATION(100000+150000,binaryMerge(a,b));
//}
//STUDENT_TEST("binaryMerge time test(3)") {
//    Queue<int> a = createSequence(1000000);
//    Queue<int> b = createSequence(1500000);
//    sortedCheck(a,b);
//    TIME_OPERATION(1000000+1500000,binaryMerge(a,b));
//}
//STUDENT_TEST("binaryMerge time test(4)") {
//    Queue<int> a = createSequence(10000000);
//    Queue<int> b = createSequence(15000000);
//    sortedCheck(a,b);
//    TIME_OPERATION(10000000+15000000,binaryMerge(a,b));
//}

//STUDENT_TEST("naiveMultiMerge") {
//    Vector<Queue<int>> all = {{},{},{}};
//    Queue<int> expected = {};
//    EXPECT_EQUAL(naiveMultiMerge(all), expected);
//}
//STUDENT_TEST("naiveMultiMerge time test") {     //naive time test
//    int n = 100000;
//    int k = 10;
//    Vector<Queue<int>> all(k);
//    Queue<int> input = createSequence(n);
//    distribute(input, all);
//    TIME_OPERATION(input.size(),naiveMultiMerge(all));
//}
//STUDENT_TEST("naiveMultiMerge time test") {
//    int n = 1000000;
//    int k = 10;
//    Vector<Queue<int>> all(k);
//    Queue<int> input = createSequence(n);
//    distribute(input, all);
//    TIME_OPERATION(input.size(),naiveMultiMerge(all));
//}
//STUDENT_TEST("naiveMultiMerge time test") {
//    int n = 10000000;
//    int k = 10;
//    Vector<Queue<int>> all(k);
//    Queue<int> input = createSequence(n);
//    distribute(input, all);
//    TIME_OPERATION(input.size(),naiveMultiMerge(all));
//}
//STUDENT_TEST("naiveMultiMerge time test") {    //naive time test2
//    int n = 10000;
//    int k = 10;
//    Vector<Queue<int>> all(k);
//    Queue<int> input = createSequence(n);
//    distribute(input, all);
//    TIME_OPERATION(all.size(),naiveMultiMerge(all));
//}
//STUDENT_TEST("naiveMultiMerge time test") {
//    int n = 10000;
//    int k = 100;
//    Vector<Queue<int>> all(k);
//    Queue<int> input = createSequence(n);
//    distribute(input, all);
//    TIME_OPERATION(all.size(),naiveMultiMerge(all));
//}
//STUDENT_TEST("naiveMultiMerge time test") {
//    int n = 10000;
//    int k = 1000;
//    Vector<Queue<int>> all(k);
//    Queue<int> input = createSequence(n);
//    distribute(input, all);
//    TIME_OPERATION(all.size(),naiveMultiMerge(all));
//}

STUDENT_TEST("recMultiMerge") {
    Vector<Queue<int>> all = {{},{},{}};
    Queue<int> expected = {};
    EXPECT_EQUAL(recMultiMerge(all), expected);
}
//STUDENT_TEST("recMultiMerge time test") {       //rec time test
//    int n = 100000;
//    int k = 10;
//    Vector<Queue<int>> all(k);
//    Queue<int> input = createSequence(n);
//    distribute(input, all);
//    TIME_OPERATION(input.size(),recMultiMerge(all));
//}
//STUDENT_TEST("recMultiMerge time test") {
//    int n = 1000000;
//    int k = 10;
//    Vector<Queue<int>> all(k);
//    Queue<int> input = createSequence(n);
//    distribute(input, all);
//    TIME_OPERATION(input.size(),recMultiMerge(all));
//}
//STUDENT_TEST("recMultiMerge time test") {
//    int n = 10000000;
//    int k = 10;
//    Vector<Queue<int>> all(k);
//    Queue<int> input = createSequence(n);
//    distribute(input, all);
//    TIME_OPERATION(input.size(),recMultiMerge(all));
//}
STUDENT_TEST("recMultiMerge time test") {       //rec time test2
    int n = 100000;
    int k = 10;
    Vector<Queue<int>> all(k);
    Queue<int> input = createSequence(n);
    distribute(input, all);
    TIME_OPERATION(all.size(),recMultiMerge(all));
}
STUDENT_TEST("recMultiMerge time test") {
    int n = 100000;
    int k = 100;
    Vector<Queue<int>> all(k);
    Queue<int> input = createSequence(n);
    distribute(input, all);
    TIME_OPERATION(all.size(),recMultiMerge(all));
}
STUDENT_TEST("recMultiMerge time test") {
    int n = 100000;
    int k = 1000;
    Vector<Queue<int>> all(k);
    Queue<int> input = createSequence(n);
    distribute(input, all);
    TIME_OPERATION(all.size(),recMultiMerge(all));
}

