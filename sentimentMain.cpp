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

        if( tr.searchWord(root, str) ) {
            cout << "Word found!";
        }

        i++;
    }

    i = 0;
    while ( i < 3){
        cin >> str;
        if( tr.searchWord(root, str) ) {
                cout << str << " found!";
            }
        else{ cout << str << " not found!";  }
    }
    



    return 0;
}