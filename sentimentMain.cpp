#include <iostream>
#include "trie.h"
#include <fstream> 
using namespace std;

int main(){

    TrieNode tr;
    TrieNode* root = new TrieNode();
    int findCol = 0, sentiment;
    string str;
    vector<string> words;
    ifstream sTrain("C:/Users/lukev/Projects/Data Structures/Voinov_CS5393-002_Project3/train_dataset_20k.csv");


    if(!sTrain.is_open()){
        cout << "File is not open!!";
        return -1;
    }
    else{
        cout << "file open ;O\n\n";
    }

    while( getline(sTrain, str) ){
        if(findCol % 6 == 0){ // to find the first column in each row
            getline(sTrain, str);
            cout << "String is: " << str << endl;
            //sentiment = stoi(str);
        }
        else if(findCol % 5 == 0){ // to find the fifth column in each row
            getline(sTrain, str);
            words = tr.parseSentence(str);
            for(unsigned int i = 0; i < words.size(); i++){
                tr.insertLetter(root, words.at(i), sentiment);

                cout << "Inserted: [ " << words.at(i) << " ]" << endl;
            }
        }
        findCol++;
    }

    sTrain.close();

    tr.mostChargedWords();

    return 0;
}