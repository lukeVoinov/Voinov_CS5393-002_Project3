#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include "DSString.h"
#include <cmath> 
#pragma once
using namespace std;

struct TrieNode {
    unordered_map<char, TrieNode*> leaf;
    int sentiment = 0;
    int maxPos = 0;
    int maxNeg = 0;
    DSString posWord, negWord;
    bool endOfWord;

    TrieNode() : endOfWord(false) {}

    void insertLetter(TrieNode* root, const DSString& word, int sent) {
        TrieNode* curr = root;
        for (char c : word) {
            if (curr->leaf.find(c) == curr->leaf.end()) {
                curr->leaf[c] = new TrieNode();
            }
            curr = curr->leaf[c];
        }
        curr->endOfWord = true;
        curr->sentiment += (sent == 0) ? -2.5 : sent;

        if (curr->sentiment > maxPos) {
            maxPos = curr->sentiment;
            posWord = word;
        } else if (curr->sentiment < maxNeg) {
            maxNeg = curr->sentiment;
            negWord = word;
        }
    }

    bool searchWord(TrieNode* root, const DSString& key) const {
        TrieNode* curr = root;
        for (char c : key) {
            auto it = curr->leaf.find(c);
            if (it == curr->leaf.end())
                return false;
            curr = it->second;
        }
        return curr->endOfWord;
    }

    vector<DSString> parseSentence(const DSString& sent) const {
        vector<DSString> words;
        words.reserve(10); // Reserve space to avoid multiple reallocations
        DSString word;
        size_t start = 0, end = 0;

        while ((end = sent.find(' ', start)) != string::npos) {
            word = parseWord(sent.substring(start, end - start));
            words.push_back(word);
            start = end + 1;
        }
        word = parseWord(sent.substring(start));
        words.push_back(word);

        return words;
    }

    DSString parseWord(const DSString& word) const {
        DSString w;
        for (char c : word) {
            if (isalnum(c)) {
                w.append(DSString(1, tolower(c)));
            }
        }
        return w;
    }

    void mostChargedWords() const {
        cout << "Most Negative: " << negWord << " -> " << maxNeg << endl
             << "Most Positive: " << posWord << " -> " << maxPos << endl;
    }

    vector<int> analyzeWord(TrieNode* root, const DSString& word, vector<int>& vec) const {
        TrieNode* curr = root;

        for (char c : word) {
            auto it = curr->leaf.find(c);
            if (it != curr->leaf.end()) {
                curr = it->second;
            } else {
                return vec;
            }
        }
        if (curr->endOfWord) {
            if (curr->sentiment >= 0) {
                vec[0] += curr->sentiment;
            } else {
                vec[1] += curr->sentiment; 
            }
        }

        return vec;
    }
    
    inline double normalize(int x) const {
        return log10(x);
    }
};
