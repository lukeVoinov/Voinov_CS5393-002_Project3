#include <iostream>
#include "trie.h"
#include <fstream> 
using namespace std;

int main(){

    TrieNode tr;
    TrieNode* root = new TrieNode();
    int i = 0, sentiment;
    string str;
    ifstream sTrain("train_dataset_20k.csv");


    if(!sTrain.is_open()){
        cout << "File is not open!!";
        return -1;
    }
    else{
        cout << "file open ;O";
    }

    while(!sTrain.eof()){
        if(i == 0){
            getline(sTrain, str);
            sentiment = stoi(str);
        }
        else if(i % 7 == 0){
            getline(sTrain, str);
            
        }
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