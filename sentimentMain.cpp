#include <iostream>
#include "trie.h"
using namespace std;

int main(){

    TrieNode tr;
    TrieNode* root = new TrieNode();
    int i = 0;
    string str;

    while( i < 5){
        cout << "Say a word: " << endl;
        cin >> str;

        tr.insertLetter(root, str, 4);
        i++;
    }

    



    return 0;
}