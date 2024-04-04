#include "listnode.h"
#include "vector.h"
#include "testing/SimpleTest.h"
using namespace std;

/*
 * TODO: Replace this comment with a descriptive function
 * header comment about your implementation of the function.
 */

void partition(ListNode*& list, ListNode*& less, ListNode*& equal, ListNode*& greater){
    if(list == nullptr){
        return;
    }
    if(list->next == nullptr){
        return;
    }
    ListNode* lessHelper;
    ListNode* equalHelper;
    ListNode* greaterHelper;
    int target = list->data;
    for(ListNode* cur = list; cur != nullptr; cur = list){
        if(cur->data < target){
            list = list->next;
            cur->next = nullptr;
            if(less == nullptr){
                less = cur;
                lessHelper = less;
            } else{
                lessHelper->next = cur;
                lessHelper = lessHelper->next;
            }
        } else if(cur->data == target){
            list = list->next;
            cur->next = nullptr;
            if(equal == nullptr){
                equal = cur;
                equalHelper = equal;
            } else{
                equalHelper->next = cur;
                equalHelper = equalHelper->next;
            }
        } else if(cur->data > target){
            list = list->next;
            cur->next = nullptr;
            if(greater == nullptr){
               greater = cur;
               greaterHelper = greater;
            } else{
                greaterHelper->next = cur;
                greaterHelper = greaterHelper->next;
            }
        }
    }
    return;
}

void concatenate(ListNode*& list, ListNode*& less, ListNode*& equal, ListNode*& greater){
    ListNode* con;
    if(less != nullptr){
        list = less;
        con = less;
        while(con->next != nullptr){
            con = con->next;
        }
        con->next = equal;
    } else {
        list = equal;
    }
    con = equal;
    if(greater != nullptr){
        while(con->next != nullptr){
            con = con->next;
        }
        con->next = greater;
    }
}

void quickSort(ListNode*& front) {
    /* TODO: Implement this function. */
    if(front == nullptr){
        return;
    }
    if(front->next == nullptr){
        return;
    }
    ListNode* less = nullptr;
    ListNode* equal = nullptr;
    ListNode* greater = nullptr;
    partition(front,less,equal,greater);
    quickSort(less);
    quickSort(greater);
    concatenate(front,less,equal,greater);
}


/* * * * * * Test Code Below This Point * * * * * */

/* TODO: Write your own student tests below to test your sorting helper
 * functions and overall sorting algorithm correctness. We have provided
 * the skeleton of some tests below to help you get started with this
 * process.
 */

/*
 * We have provided this utility function as a convenience. This
 * function traverses the linked list represented by the provided
 * front pointer and prints out the data stored in the list along
 * the way in a convenient format. You may find it to be helpful to
 * use this function as a debugging aid.
 */
void printList(ListNode* front) {
   cout << "{";
   for (ListNode *cur = front; cur != nullptr; cur = cur->next) {
       cout << cur->data;
       if (cur->next != nullptr){
           cout << ", ";
       }
   }
   cout << "}" << endl;
}

/*
 * This utility function deallocates the memory for all the nodes in a
 * given linked list. It can be used to recycle the memory allocated
 * during a test case and avoid memory leaks.
 */
void deallocateList(ListNode* front) {
    /* TODO: Implement this function. */
   ListNode* prev = front;
   while(front != nullptr){
       front = front->next;
       delete prev;
       prev = front;
   }
   return;
}

/*
 * This utility function is given a vector of values and constructs
 * an equivalent linked list containing the same values in the same order.
 * It can be used to construct a linked list to use as an input to
 * a function being tested.
 */
ListNode* createList(Vector<int> values){
    /* TODO: Implement this function. */
   int maxIndex = values.size() - 1;
   ListNode* list = nullptr;
   for(int i = maxIndex; i >= 0; i--){
       ListNode* New = new ListNode(values[i],list);
       list = New;
   }
    return list;
}

/*
 * This utility function compares a linked list and a vector for
 * equivalence and returns true if both contain the same values in the
 * same order. It can be used to confirm a linked list's contents match
 * the expected.
 */
bool areEquivalent(ListNode* front, Vector<int> v){
    /* TODO: Implement this function. */
    ListNode* ind = front;
    for(int i = 0; i < v.size(); i++){
       if(ind == nullptr){
           return false;
       }
       if(ind->data != v[i]){
           return false;
       }
       ind = ind->next;
    }
    if(ind != nullptr){
       return false;
    }
    return true;
}

STUDENT_TEST("This is a skeleton to demonstrate an end-to-end student test."){
    /* Initialize vector to sequence of values */
    Vector<int> values = {1, 2, 3, 4};
    /* Create equivalent list to use as test input */
    ListNode* list = createList(values);

    /* Sort the list */
    quickSort(list);

    /* Sort the equivalent vector */
    values.sort();

    /* Confirm sorted list matches sorted vector */
    EXPECT(areEquivalent(list, values));

    /* Avoid memory leaks by deallocating list */
    deallocateList(list);
}

//PROVIDED_TEST("This tests some of the testing helper functions you are recommended to implement."){
//    /* Creates a small test list containing the values 1->2->3. */
//    ListNode* testList = nullptr;
//    testList = new ListNode(3, testList);
//    testList = new ListNode(2, testList);
//    testList = new ListNode(1, testList);

//    /* Test equality comparison function. */
//    EXPECT(areEquivalent(testList, {1, 2, 3}));
//    EXPECT(!areEquivalent(testList, {1, 2}));
//    EXPECT(!areEquivalent(testList, {1, 2, 3, 4}));
//    EXPECT(!areEquivalent(testList, {1, 3, 2}));

//    /* Test create list function. */
//    ListNode* studentList = createList({1, 2, 3, 4});
//    printList(studentList);
//    ListNode* cur = studentList;
//    for (int i = 1; i <= 4; i++){
//        EXPECT(cur != nullptr);
//        EXPECT_EQUAL(cur->data, i);
//        cur = cur->next;
//    }

//    /* Test deallocate list functions. There should be no memory leaks from this test. */
//    deallocateList(studentList);
//    deallocateList(testList);
//}

/*
 * The provided test case demonstrates a comparsion between the same
 * algorithm (quicksort) operating on a linked list versus a vector.
 */
PROVIDED_TEST("Time linked list quicksort vs vector quicksort") {
    int startSize = 50000;

    for(int n = startSize; n < 10*startSize; n *= 2) {
        Vector<int> v(n);
        ListNode* list = nullptr;

        /* Create linked list and vector with the same random sequence. */
        for (int i = n-1; i >= 0; i--) {
            v[i] = randomInteger(-10000, 10000);
            list = new ListNode(v[i], list);
        }

        /* NOTE: This test does not check correctness of the linked list sort
         * function. It only times the two operations to compare relative speed. */
        TIME_OPERATION(n, quickSort(list));
        TIME_OPERATION(n, v.sort());        /* Standard vector sort operation is backed
                                               with quicksort algorithm. */

        deallocateList(list);
    }
}

//STUDENT_TEST("partition"){
//    int n;
//    Vector<int> creator = {2,4,1,3,5,4,1,3};
//    ListNode* list = createList(creator);
//    ListNode* less = nullptr;
//    ListNode* equal = nullptr;
//    ListNode* greater = nullptr;
//    partition(list,less,equal,greater);
//    EXPECT(areEquivalent(less,{1,1}));
//    EXPECT(areEquivalent(equal,{2}));
//    EXPECT(areEquivalent(greater,{4,3,5,4,3}));
//    deallocateList(less);
//    deallocateList(equal);
//    deallocateList(greater);
//}

//STUDENT_TEST("concatence"){
//    Vector<int> creator = {2,4,2,3,5,4,2,3};
//    ListNode* list = createList(creator);
//    ListNode* less = nullptr;
//    ListNode* equal = nullptr;
//    ListNode* greater = nullptr;
//    partition(list,less,equal,greater);
//    EXPECT(areEquivalent(less,{}));
//    EXPECT(areEquivalent(equal,{2,2,2}));
//    EXPECT(areEquivalent(greater,{4,3,5,4,3}));
//    EXPECT(list == nullptr);
//    concatenate(list,less,equal,greater);
//    EXPECT(areEquivalent(list,{2,2,2,4,3,5,4,3}));
//    deallocateList(list);
//}
