#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <math.h> 
#pragma once
using namespace std;

struct TrieNode {
    unordered_map<char, TrieNode*> leaf;
    int sentiment = 0;
    int maxPos = 0;
    int maxNeg = 0;
    string posWord, negWord;
    bool endOfWord;

    TrieNode() : endOfWord(false) {}

    void insertLetter(TrieNode* root, const string& word, int sent) {
        TrieNode* curr = root;
        for (char c : word) {
            if (curr->leaf.find(c) == curr->leaf.end()) {
                curr->leaf[c] = new TrieNode();
            }
            curr = curr->leaf[c];
        }
        curr->endOfWord = true;
        curr->sentiment += (sent == 0) ? -3 : sent;

        if (curr->sentiment > maxPos) {
            maxPos = curr->sentiment;
            posWord = word;
        } else if (curr->sentiment < maxNeg) {
            maxNeg = curr->sentiment;
            negWord = word;
        }
    }

    bool searchWord(TrieNode* root, const string& key) const {
        TrieNode* curr = root;
        for (char c : key) {
            if (curr->leaf.find(c) == curr->leaf.end())
                return false;
            curr = curr->leaf[c];
        }
        return curr->endOfWord;
    }

    vector<string> parseSentence(const string& sent) const {
        vector<string> words;
        string word;
        size_t start = 0, end = 0;

        while ((end = sent.find(' ', start)) != string::npos) {
            word = parseWord(sent.substr(start, end - start));
            words.push_back(word);
            start = end + 1;
        }
        word = parseWord(sent.substr(start));
        words.push_back(word);

        return words;
    }

    string parseWord(const string& word) const {
        string w;
        for (char c : word) {
            if (isalnum(c)) {
                w += tolower(c);
            }
        }
        return w;
    }

    void mostChargedWords() const {
        cout << "Most Negative: " << negWord << " -> " << maxNeg << endl
             << "Most Positive: " << posWord << " -> " << maxPos << endl;
    }

    vector<int> analyzeWord(TrieNode* root, const string& word, vector<int> vec) {

        TrieNode* curr = root;
        for (char c : word) {
            if(curr->leaf[c]){
                curr = curr->leaf[c];
            }
        }
        if(curr->endOfWord == true){
            if(curr->sentiment >= 0){
                vec.at(0) += curr->sentiment;
            }
            else {
                vec.at(1) += curr->sentiment; 
            }
        }

        return vec;
    }
    
    double normalize(int x){
        double f_x = 0.0;

        f_x = 20 * log10(x);

        return f_x;
    }
};
