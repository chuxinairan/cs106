#include "bits.h"
#include "treenode.h"
#include "huffman.h"
#include "map.h"
#include "vector.h"
#include "priorityqueue.h"
#include "strlib.h"
#include "string"
#include "testing/SimpleTest.h"
using namespace std;

/**
 * Given a Queue<Bit> containing the compressed message bits and the encoding tree
 * used to encode those bits, decode the bits back to the original message text.
 *
 * You can assume that tree is a well-formed non-empty encoding tree and
 * messageBits queue contains a valid sequence of encoded bits.
 *
 * Your implementation may change the messageBits queue however you like. There
 * are no requirements about what it should look like after this function
 * returns. The encoding tree should be unchanged.
 *
 * TODO: Add any additional information to this comment that is necessary to describe
 * your implementation.
 */
string decodeText(EncodingTreeNode* tree, Queue<Bit>& messageBits) {
    /* TODO: Implement this function. */
    string text = "";
    EncodingTreeNode* cur = tree;
    while(!messageBits.isEmpty()){
        Bit bi = messageBits.dequeue();
        if(bi == 0){
            cur = cur->zero;
        } else {
            cur = cur->one;
        }
        if(cur->isLeaf()){
            text += cur->ch;
            cur = tree;
        }
    }
    return text;
}


/**
 * Reconstruct encoding tree from flattened form Queue<Bit> and Queue<char>.
 *
 * You can assume that the queues are well-formed and represent
 * a valid encoding tree.
 *
 * Your implementation may change the queue parameters however you like. There
 * are no requirements about what they should look like after this function
 * returns.
 *
 * TODO: Add any additional information to this comment that is necessary to describe
 * your implementation.
 */
EncodingTreeNode* unflattenTree(Queue<Bit>& treeShape, Queue<char>& treeLeaves) {
    /* TODO: Implement this function. */
    Bit bi = treeShape.dequeue();
    EncodingTreeNode* newNode;
    if(bi == 0){
        char ch = treeLeaves.dequeue();
        newNode = new EncodingTreeNode(ch);
    } else {
        newNode = new EncodingTreeNode(unflattenTree(treeShape,treeLeaves),unflattenTree(treeShape,treeLeaves));
    }
    return newNode;
}

/**
 * Decompress the given EncodedData and return the original text.
 *
 * You can assume the input data is well-formed and was created by a correct
 * implementation of compress.
 *
 * Your implementation may change the data parameter however you like. There
 * are no requirements about what it should look like after this function
 * returns.
 *
 * TODO: Add any additional information to this comment that is necessary to describe
 * your implementation.
 */
string decompress(EncodedData& data) {
    /* TODO: Implement this function. */
    EncodingTreeNode* tree = unflattenTree(data.treeShape,data.treeLeaves);
    string result = decodeText(tree,data.messageBits);
    deallocateTree(tree);
    return result;
}

/**
 * Constructs an optimal Huffman coding tree for the given text, using
 * the algorithm described in lecture.
 *
 * Reports an error if the input text does not contain at least
 * two distinct characters.
 *
 * When assembling larger trees out of smaller ones, make sure to set the first
 * tree dequeued from the queue to be the zero subtree of the new tree and the
 * second tree as the one subtree.
 *
 * TODO: Add any additional information to this comment that is necessary to describe
 * your implementation.
 */
EncodingTreeNode* buildHuffmanTree(string text){
    /* TODO: Implement this function. */
    if(text.size() < 2){
        error("the text have to contain two characters");
    }
    // 1 create a character to frequencytable
    Map<char,double> frequencyTable;
    for(char& ch : text){
        if(frequencyTable.containsKey(ch)){
            frequencyTable[ch]++;
        } else {
            frequencyTable.put(ch,1);
        }
    }
    if(frequencyTable.size() < 2){
        error("must contain two distinct characters");
    }
    // 2 create a priority queue with frequency priority
    PriorityQueue<EncodingTreeNode*> pq;
    for(const char& ch : frequencyTable){
        EncodingTreeNode* node = new EncodingTreeNode(ch);
        pq.enqueue(node,frequencyTable[ch]);
    }
    // 3 with a weight of frequency, get two lowest weight together, become a bigger node, put into priority queue
    EncodingTreeNode* tree;
    while(!pq.isEmpty()){
        double weightF = pq.peekPriority();
        EncodingTreeNode* front = pq.dequeue();
        if(!pq.isEmpty()) {
            double weightS = pq.peekPriority();
            EncodingTreeNode* second = pq.dequeue();
            EncodingTreeNode* unit = new EncodingTreeNode(front,second);
            double newWeight = weightF + weightS;
            pq.enqueue(unit,newWeight);
        } else{
            tree = front;
        }
    }
    return tree;
}

/**
 * Given a string and an encoding tree, encode the text using the tree
 * and return a Queue<Bit> of the encoded bit sequence.
 *
 * You can assume tree is a valid non-empty encoding tree and contains an
 * encoding for every character in the text.
 *
 * TODO: Add any additional information to this comment that is necessary to describe
 * your implementation.
 */
void mappingTableHelper(EncodingTreeNode* tree, Map<char,string>& mapping, string& path){
    if(tree->isLeaf()){
        mapping.put(tree->ch,path);
        path.pop_back();
        return;
    }
    path.push_back('0');
    mappingTableHelper(tree->zero,mapping,path);
    path.push_back('1');
    mappingTableHelper(tree->one,mapping,path);
    path.pop_back();
    return;
}

Map<char,string> mappingTable(EncodingTreeNode* tree){
    Map<char,string> mapping;
    string bitstream = "";
    bitstream += '0';
    mappingTableHelper(tree->zero, mapping, bitstream);
    bitstream += '1';
    mappingTableHelper(tree->one, mapping, bitstream);
    return mapping;
}

Queue<Bit> encodeText(EncodingTreeNode* tree, string text) {
    /* TODO: Implement this function. */
    Map<char,string> mapTable = mappingTable(tree);
    Queue<Bit> bitstream;
    for(char& ch : text){
        string path = mapTable[ch];
        for(char& bi : path){
            if(bi == '0'){
                bitstream.enqueue(0);
            } else {
                bitstream.enqueue(1);
            }

        }
    }
    return bitstream;
}

/**
 * Flatten the given tree into a Queue<Bit> and Queue<char> in the manner
 * specified in the assignment writeup.
 *
 * You can assume the input queues are empty on entry to this function.
 *
 * You can assume tree is a valid well-formed encoding tree.
 *
 * TODO: Add any additional information to this comment that is necessary to describe
 * your implementation.
 */
void flattenTree(EncodingTreeNode* tree, Queue<Bit>& treeShape, Queue<char>& treeLeaves) {
    /* TODO: Implement this function. */
    if(tree->isLeaf()){
        treeShape.enqueue(0);
        treeLeaves.enqueue(tree->ch);
        return;
    }
    treeShape.enqueue(1);
    flattenTree(tree->zero, treeShape, treeLeaves);
    flattenTree(tree->one, treeShape, treeLeaves);
    return;
}

/**
 * Compress the input text using Huffman coding, producing as output
 * an EncodedData containing the encoded message and flattened
 * encoding tree used.
 *
 * Reports an error if the message text does not contain at least
 * two distinct characters.
 *
 * TODO: Add any additional information to this comment that is necessary to describe
 * your implementation.
 */
EncodedData compress(string messageText) {
    /* TODO: Implement this function. */
    EncodingTreeNode* tree = buildHuffmanTree(messageText);
    Queue<Bit> treeShape;
    Queue<char> treeLeaves;
    flattenTree(tree,treeShape,treeLeaves);
    Queue<Bit> text = encodeText(tree,messageText);
    EncodedData compressed = {treeShape,treeLeaves,text};
    deallocateTree(tree);
    return compressed;
}

/* * * * * * Testing Helper Functions Below This Point * * * * * */

EncodingTreeNode* createExampleTree() {
    /* Example encoding tree used in multiple test cases:
     *                *
     *              /   \
     *             T     *
     *                  / \
     *                 *   E
     *                / \
     *               R   S
     */
    /* TODO: Implement this utility function needed for testing. */
    EncodingTreeNode* T = new EncodingTreeNode('T');
    EncodingTreeNode* R = new EncodingTreeNode('R');
    EncodingTreeNode* S = new EncodingTreeNode('S');
    EncodingTreeNode* E = new EncodingTreeNode('E');
    EncodingTreeNode* rs = new EncodingTreeNode(R,S);
    EncodingTreeNode* rse = new EncodingTreeNode(rs,E);
    EncodingTreeNode* root = new EncodingTreeNode(T,rse);
    return root;
}

void deallocateTree(EncodingTreeNode* t) {
    /* TODO: Implement this utility function needed for testing. */
    if(t == nullptr){
        return;
    }
    deallocateTree(t->zero);
    deallocateTree(t->one);
    delete t;
}

bool areEqual(EncodingTreeNode* a, EncodingTreeNode* b) {
    /* TODO: Implement this utility function needed for testing. */
    if(a == nullptr && b == nullptr){
        return true;
    } else if(a == nullptr && b != nullptr){
        return false;
    } else if(a != nullptr && b == nullptr){
        return false;
    }
    if(a->isLeaf() && b->isLeaf()){
        if(a->ch != b->ch){
            return false;
        }
    }
    return areEqual(a->zero,b->zero)&&areEqual(a->one,b->one);
}

/* * * * * * Test Cases Below This Point * * * * * */

/* TODO: Write your own student tests. */

//STUDENT_TEST("areEqual") {
//    EncodingTreeNode* tree = createExampleTree(); // see diagram above
//    EXPECT(tree != nullptr);
//    EncodingTreeNode* null = nullptr;
//    EncodingTreeNode* ftNode = new EncodingTreeNode('c');
//    EncodingTreeNode* sdNode = new EncodingTreeNode('c');
//    EncodingTreeNode* oneNode = new EncodingTreeNode(ftNode,sdNode);
//    EncodingTreeNode* tree2 = createExampleTree();
//    EXPECT(!areEqual(null,oneNode));
//    EXPECT(!areEqual(tree,oneNode));
//    EXPECT(areEqual(ftNode,sdNode));
//    EXPECT(areEqual(tree,tree2));
//    EXPECT(!areEqual(tree,tree->one));
//    delete tree2->one->zero->zero;
//    tree2->one->zero->zero = nullptr;
//    EXPECT(!areEqual(tree,tree2));
//    deallocateTree(tree);
//    deallocateTree(null);
//    deallocateTree(oneNode);
//    deallocateTree(tree2);
//}







/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("decodeText, small example encoding tree") {
    EncodingTreeNode* tree = createExampleTree(); // see diagram above
    EXPECT(tree != nullptr);

    Queue<Bit> messageBits = { 1, 1 }; // E
    EXPECT_EQUAL(decodeText(tree, messageBits), "E");

    messageBits = { 1, 0, 1, 1, 1, 0 }; // SET
    EXPECT_EQUAL(decodeText(tree, messageBits), "SET");

    messageBits = { 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1}; // STREETS
    EXPECT_EQUAL(decodeText(tree, messageBits), "STREETS");

    deallocateTree(tree);
}

PROVIDED_TEST("unflattenTree, small example encoding tree") {
    EncodingTreeNode* reference = createExampleTree(); // see diagram above
    Queue<Bit>  treeShape  = { 1, 0, 1, 1, 0, 0, 0 };
    Queue<char> treeLeaves = { 'T', 'R', 'S', 'E' };
    EncodingTreeNode* tree = unflattenTree(treeShape, treeLeaves);

    EXPECT(areEqual(tree, reference));

    deallocateTree(tree);
    deallocateTree(reference);
}

PROVIDED_TEST("decompress, small example input") {
    EncodedData data = {
        { 1, 0, 1, 1, 0, 0, 0 }, // treeShape
        { 'T', 'R', 'S', 'E' },  // treeLeaves
        { 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1 } // messageBits
    };

    EXPECT_EQUAL(decompress(data), "TRESS");
}

PROVIDED_TEST("buildHuffmanTree, small example encoding tree") {
    EncodingTreeNode* reference = createExampleTree(); // see diagram above
    EncodingTreeNode* tree = buildHuffmanTree("STREETTEST");
    EXPECT(areEqual(tree, reference));

    deallocateTree(reference);
    deallocateTree(tree);
}

PROVIDED_TEST("encodeText, small example encoding tree") {
    EncodingTreeNode* reference = createExampleTree(); // see diagram above

    Queue<Bit> messageBits = { 1, 1 }; // E
    EXPECT_EQUAL(encodeText(reference, "E"), messageBits);

    messageBits = { 1, 0, 1, 1, 1, 0 }; // SET
    EXPECT_EQUAL(encodeText(reference, "SET"), messageBits);

    messageBits = { 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1 }; // STREETS
    EXPECT_EQUAL(encodeText(reference, "STREETS"), messageBits);

    deallocateTree(reference);
}

PROVIDED_TEST("flattenTree, small example encoding tree") {
    EncodingTreeNode* reference = createExampleTree(); // see diagram above
    Queue<Bit>  expectedShape  = { 1, 0, 1, 1, 0, 0, 0 };
    Queue<char> expectedLeaves = { 'T', 'R', 'S', 'E' };

    Queue<Bit>  treeShape;
    Queue<char> treeLeaves;
    flattenTree(reference, treeShape, treeLeaves);

    EXPECT_EQUAL(treeShape,  expectedShape);
    EXPECT_EQUAL(treeLeaves, expectedLeaves);

    deallocateTree(reference);
}

PROVIDED_TEST("compress, small example input") {
    EncodedData data = compress("STREETTEST");
    Queue<Bit>  treeShape   = { 1, 0, 1, 1, 0, 0, 0 };
    Queue<char> treeChars   = { 'T', 'R', 'S', 'E' };
    Queue<Bit>  messageBits = { 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0 };

    EXPECT_EQUAL(data.treeShape, treeShape);
    EXPECT_EQUAL(data.treeLeaves, treeChars);
    EXPECT_EQUAL(data.messageBits, messageBits);
}

PROVIDED_TEST("Test end-to-end compress -> decompress") {
    Vector<string> inputs = {
        "HAPPY HIP HOP",
        "Nana Nana Nana Nana Nana Nana Nana Nana Batman"
        "Research is formalized curiosity. It is poking and prying with a purpose. – Zora Neale Hurston",
    };

    for (string input: inputs) {
        EncodedData data = compress(input);
        string output = decompress(data);

        EXPECT_EQUAL(input, output);
    }
}
