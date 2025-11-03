//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {
    MinHeap heap;                                //creates empty heap

    for (int i = 0; i < nextFree; ++i) {         //pushes all leaf nodes in the heap
        heap.push(i, weightArr);                 //adds node index to heap
    }

    int currFree = nextFree;                     // rack next open index for new parent nodes

    while (heap.size > 1) {                      //while heap size is greater than 1
        int left = heap.pop(weightArr);          //remove smallest node
        int right = heap.pop(weightArr);         //remove next smallest node

        leftArr[currFree] = left;                //set left child
        rightArr[currFree] = right;              //set right child
        weightArr[currFree] = weightArr[left] + weightArr[right]; //set sum of both weights
        charArr[currFree] = '\0';                //no char node
        heap.push(currFree, weightArr);          //push new parent back on heap

        currFree++;                              //moves next
    }

    int root = heap.pop(weightArr);              //last remaining node is the root
    return root;                                 // return root index
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {

    if (leftArr[root] == -1 && rightArr[root] == -1) { //if tree has only one char give it code 0
        char c = charArr[root];                //get char
        codes[c - 'a'] = "0";                  //equal 0
        return;
    }

    stack<int> nodes;                          //stack to hold nodes
    stack<string> paths;                       //stack to hold paths
    nodes.push(root);                          //start from root
    paths.push("");                       //start with empty path

    while (!nodes.empty()) {                   //while there are nodes to visit
        int u = nodes.top(); nodes.pop();      //get top node
        string path = paths.top(); paths.pop();//get its current path

        bool isLeaf = (leftArr[u] == -1 && rightArr[u] == -1);  //check if leaf

        if (isLeaf) {                          //if its a leaf node
            char c = charArr[u];               //get char
            codes[c - 'a'] = path.empty() ? "0" : path; //assign code
        }

        else {

            if (rightArr[u] != -1) {             //if right child exists
                nodes.push(rightArr[u]);         //push right child
                paths.push(path + "1");        //add 1 for right edge
            }

            if (leftArr[u] != -1) {              //if left child exists
                nodes.push(leftArr[u]);          //push left child
                paths.push(path + "0");        //add 0 for left edge
            }
        }
    }
}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}