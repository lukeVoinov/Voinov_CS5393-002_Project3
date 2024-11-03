#include <iostream>
#include <vector>
#include <string>
#pragma once
using namespace std;

struct TrieNode{

    TrieNode* leaf[26];

    int sentiment, maxPos, maxNeg = 0;
    string posWord, negWord;
    bool endOfWord;

    TrieNode(){
        endOfWord = false;
        for(int i = 0; i < 26; i++){
            leaf[i] = nullptr;
        }
    }

    void insertLetter(TrieNode* root, string word, int sent){
        TrieNode* curr = root;
        string tempStr = "";

        for(char c : word){

            if(curr->leaf[c - 'a'] == nullptr){ // 'a' corresponds to 0
                TrieNode* newNode = new TrieNode();

                curr->leaf[c - 'a'] = newNode;
            }

            tempStr += c;
            curr = curr->leaf[c - 'a'];
        }
        if(sent == 0){
            sent = -4;
        }
        curr->endOfWord = true;
        curr->sentiment += sent; // add sent to show how positive relative to the other words this word is

        if(curr->sentiment > maxPos){
            maxPos = curr->sentiment;
            posWord = tempStr;
        }
        else if(curr->sentiment < maxNeg){
            maxNeg = curr->sentiment;
            negWord = tempStr;
        }
    }

    // Method to search a key in the Trie
    bool searchWord(TrieNode* root, const string& key) {
    
        // Initialize the curr pointer with the root node
        TrieNode* curr = root;

        // Iterate across the length of the string
        for (char c : key) {
        
            // Check if the node exists for the 
            // current character in the Trie
            if (curr->leaf[c - 'a'] == nullptr) 
                return false;
            
            // Move the curr pointer to the 
            // already existing node for the 
            // current character
            curr = curr->leaf[c - 'a'];
        }

        // Return true if the word exists 
        // and is marked as ending
        return curr->endOfWord;
    }

    vector<string> parseSentence(string sent){
        vector<string> words;
        string word;
        int j, i = 0;

        for(i = 0; i < sent.length(); i++){
            if(sent.at(i) == ' '){ 
                word = sent.substr(j, i-j-1);
                words.push_back(word);
            }
            else if( i+1 >= sent.length() ) { //>= could arbitraily be ==
                word = sent.substr(j, i-j);
                words.push_back(word);
            }
        }

        return words;
    }

    void mostChargedWords(){
        cout << "Most Negative: " << negWord << " -> " << maxNeg << endl
             << "Most Positive: " << posWord << " -> " << maxPos << endl;
    }
};

//https://www.geeksforgeeks.org/trie-insert-and-search/