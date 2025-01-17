/*
 * TODO: remove and replace this file header comment
 * This is a .cpp file you will edit and turn in.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include "console.h"
#include <iostream>
#include <cmath>
#include "SimpleTest.h" // IWYU pragma: keep (needed to quiet spurious warning)
using namespace std;

/* The divisorSum function takes one argument `n` and calculates the
 * sum of proper divisors of `n` excluding itself. To find divisors
 * a loop iterates over all numbers from 1 to n-1, testing for a
 * zero remainder from the division using the modulus operator %
 *
 * Note: the C++ long type is a variant of int that allows for a
 * larger range of values. For all intents and purposes, you can
 * treat it like you would an int.
 */
long divisorSum(long n) {
    long total = 0;
    for (long divisor = 1; divisor < n; divisor++) {
        if (n % divisor == 0) {
            total += divisor;
        }
    }
    return total;
}

/* The isPerfect function takes one argument `n` and returns a boolean
 * (true/false) value indicating whether or not `n` is perfect.
 * A perfect number is a non-zero positive number whose sum
 * of its proper divisors is equal to itself.
 */
bool isPerfect(long n) {
    return (n != 0) && (n == divisorSum(n));
}

/* The findPerfects function takes one argument `stop` and performs
 * an exhaustive search for perfect numbers over the range 1 to `stop`.
 * Each perfect number found is printed to the console.
 */
void findPerfects(long stop) {
    for (long num = 1; num < stop; num++) {
        if (isPerfect(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
    }
    cout << endl << "Done searching up to " << stop << endl;
}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
long smarterSum(long n) {
    /* TODO: Fill in this function. */
    long total = 0;
    if(n==1)return 0;
    for (long divisor = 1; divisor <= sqrt(n); divisor++) {
        if (n % divisor == 0) {
            total += divisor ;
            long other_div=n/divisor;
            if(divisor!=1 && divisor!=other_div)
                total += other_div;
        }
    }
    return total;
}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
bool isPerfectSmarter(long n) {
    /* TODO: Fill in this function. */
    return (n != 0) && (n == smarterSum(n));
}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
void findPerfectsSmarter(long stop) {
     /* TODO: Fill in this function. */
    for(long num = 1; num <= stop; num++){
        if(isPerfectSmarter(num)){
            cout << "Found perfect number:" << num << endl;
        }
        if(num % 10000 == 0)cout << "." << endl;
    }
    cout << endl << "Done searching up to " << stop << endl;
}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
long findNthPerfectEuclid(long n) {
    /* TODO: Fill in this function. */
    long nth;
    long i=0,k=1;
    while(i<=n){
        k++;
        long m = pow(2,k) - 1;
        if(smarterSum(m)==1){
            i++;
            long PerEuclid = pow(2,k-1)*m;
            cout << i << ")Exponent is:" << k << " Perfect Euclid:" << PerEuclid << endl;
            if(i==n) nth = PerEuclid;
        }
    }
    return nth;
}


/* * * * * * Test Cases * * * * * */

/* Note: Do not add or remove any of the PROVIDED_TEST tests.
 * You should add your own STUDENT_TEST tests below the
 * provided tests.
 */

PROVIDED_TEST("Confirm divisorSum of small inputs") {
    EXPECT_EQUAL(divisorSum(1), 0);
    EXPECT_EQUAL(divisorSum(6), 6);
    EXPECT_EQUAL(divisorSum(12), 16);
}

PROVIDED_TEST("Confirm 6 and 28 are perfect") {
    EXPECT(isPerfect(6));
    EXPECT(isPerfect(28));
}

PROVIDED_TEST("Confirm 12 and 98765 are not perfect") {
    EXPECT(!isPerfect(12));
    EXPECT(!isPerfect(98765));
}

PROVIDED_TEST("Test oddballs: 0 and 1 are not perfect") {
    EXPECT(!isPerfect(0));
    EXPECT(!isPerfect(1));
}

PROVIDED_TEST("Confirm 33550336 is perfect") {
    EXPECT(isPerfect(33550336));
}

PROVIDED_TEST("Time trial of findPerfects on input size 1000") {
    TIME_OPERATION(1000, findPerfects(1000));
}

// TODO: add your student test cases here

/*
 * Below is a suggestion of how to use a loop to set the input sizes
 * for a sequence of time trials.
 *
 *
STUDENT_TEST("Multiple time trials of findPerfects on increasing input sizes") {

    int smallest = 1000, largest = 8000;

    for (int size = smallest; size <= largest; size *= 2) {
        TIME_OPERATION(size, findPerfects(size));
    }
}

*/

STUDENT_TEST("Sum test"){
    EXPECT_EQUAL(divisorSum(25),smarterSum(25));
    EXPECT_EQUAL(divisorSum(1),smarterSum(1));
    EXPECT_EQUAL(divisorSum(10020),smarterSum(10020));
}

//STUDENT_TEST("Just a test2"){
//    TIME_OPERATION(2,smarterSum(3000000));
//    TIME_OPERATION(1,divisorSum(3000000));
//}

//STUDENT_TEST("Perfect test"){
//    EXPECT_EQUAL(isPerfect(0),isPerfectSmarter(0));
//    EXPECT_EQUAL(isPerfect(500020),isPerfectSmarter(500020));
//}
//STUDENT_TEST("Perfect test2"){
//    EXPECT_EQUAL(0,isPerfectSmarter(496));
//}

//STUDENT_TEST("FindPNumber1"){
//    TIME_OPERATION(5000,findPerfects(5000));
//    TIME_OPERATION(5000,findPerfectsSmarter(5000));
//}
//STUDENT_TEST("FindPNumber2"){
//    TIME_OPERATION(10000,findPerfects(10000));
//    TIME_OPERATION(10000,findPerfectsSmarter(10000));
//}
//STUDENT_TEST("FindPNumber3"){
//    TIME_OPERATION(15000,findPerfects(15000));
//    TIME_OPERATION(15000,findPerfectsSmarter(15000));
//}
//STUDENT_TEST("FindPNumber4"){
//    TIME_OPERATION(20000,findPerfects(20000));
//    TIME_OPERATION(20000,findPerfectsSmarter(20000));
//}

STUDENT_TEST("FindNthPE"){
    isPerfectSmarter(findNthPerfectEuclid(2));
}
