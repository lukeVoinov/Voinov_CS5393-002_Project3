#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
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
        curr->sentiment += (sent == 0) ? -4 : sent;

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
};
