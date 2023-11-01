#include <iostream>
#include <fstream>
#include <cstring>
#include "BinaryTree.h"
#include "BinarySearchTree.h"

using namespace std;

void readWordsAndStoreInBST(BTNode*& wordBST) {
    ifstream wordsFile("/Assignment1-Files/Words.txt");
    if (!wordsFile.is_open()) {
        cerr << "Failed to open Words.txt" << endl;
        return;
    }

    string word;
    while (wordsFile >> word) {
        if (word == "END") {
            break;
        }
        wordBST = insertBSTRec(wordBST, word);
    }

    wordsFile.close();
}

int main() {
    BTNode * wordBST = NULL;
    
    cout << "COMP 2611 Assignment 1" << endl;
    cout << "======================" << endl << endl;
    
    readWordsAndStoreInBST(wordBST);

    // read commands from Commands.txt and perform operations
    
    return 0;
}