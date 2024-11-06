#include <iostream> // Include the input-output stream library
#include <vector> // Include the vector library
#include <unordered_map> // Include the unordered_map library
#include <fstream> // Include the file stream library
#include "DSString.h" // Include the custom DSString header file
#include <cmath> // Include the cmath library for mathematical functions
#pragma once // Ensure the file is included only once during compilation

using namespace std; // Use the standard namespace

// Define the TrieNode structure
struct TrieNode {
    unordered_map<char, TrieNode*> leaf; // Map to store child nodes
    int sentiment = 0; // Sentiment score of the word
    int maxPos = 0; // Maximum positive sentiment score
    int maxNeg = 0; // Maximum negative sentiment score
    DSString posWord, negWord; // Words with maximum positive and negative sentiment
    bool endOfWord; // Flag to indicate the end of a word

    // Constructor to initialize endOfWord to false
    TrieNode() : endOfWord(false) {}

    // Function to insert a word into the trie
    void insertLetter(TrieNode* root, const DSString& word, int sent) {
        TrieNode* curr = root; // Start from the root node
        for (char c : word) { // Iterate through each character in the word
            if (curr->leaf.find(c) == curr->leaf.end()) { // If the character is not in the map
                curr->leaf[c] = new TrieNode(); // Create a new TrieNode
            }
            curr = curr->leaf[c]; // Move to the child node
        }
        curr->endOfWord = true; // Mark the end of the word
        curr->sentiment += (sent == 0) ? -2.5 : sent; // Update the sentiment score

        // Update the maximum positive and negative sentiment words
        if (curr->sentiment > maxPos) {
            maxPos = curr->sentiment;
            posWord = word;
        } else if (curr->sentiment < maxNeg) {
            maxNeg = curr->sentiment;
            negWord = word;
        }
    }

    // Function to search for a word in the trie
    bool searchWord(TrieNode* root, const DSString& key) const {
        TrieNode* curr = root; // Start from the root node
        for (char c : key) { // Iterate through each character in the key
            auto it = curr->leaf.find(c); // Find the character in the map
            if (it == curr->leaf.end()) // If the character is not found
                return false; // Return false
            curr = it->second; // Move to the child node
        }
        return curr->endOfWord; // Return true if it's the end of a word
    }

    // Function to parse a sentence into words
    vector<DSString> parseSentence(const DSString& sent) const {
        vector<DSString> words; // Vector to store words
        words.reserve(10); // Reserve space to avoid multiple reallocations
        DSString word; // Temporary variable to store a word
        size_t start = 0, end = 0; // Variables to track the start and end of a word

        // Loop to split the sentence into words
        while ((end = sent.find(' ', start)) != string::npos) {
            word = parseWord(sent.substring(start, end - start)); // Extract and parse the word
            words.push_back(word); // Add the word to the vector
            start = end + 1; // Move to the next word
        }
        word = parseWord(sent.substring(start)); // Parse the last word
        words.push_back(word); // Add the last word to the vector

        return words; // Return the vector of words
    }

    // Function to parse a word by removing non-alphanumeric characters
    DSString parseWord(const DSString& word) const {
        DSString w; // Temporary variable to store the parsed word
        for (char c : word) { // Iterate through each character in the word
            if (isalnum(c)) { // If the character is alphanumeric
                w.append(DSString(1, tolower(c))); // Convert to lowercase and append to the parsed word
            }
        }
        return w; // Return the parsed word
    }

    // Function to print the most positive and negative words
    void mostChargedWords() const {
        cout << "Most Negative: " << negWord << " -> " << maxNeg << endl
             << "Most Positive: " << posWord << " -> " << maxPos << endl;
    }

    // Function to analyze a word and update sentiment scores
    vector<int> analyzeWord(TrieNode* root, const DSString& word, vector<int>& vec) const {
        TrieNode* curr = root; // Start from the root node

        for (char c : word) { // Iterate through each character in the word
            auto it = curr->leaf.find(c); // Find the character in the map
            if (it != curr->leaf.end()) { // If the character is found
                curr = it->second; // Move to the child node
            } else {
                return vec; // Return the vector if the character is not found
            }
        }
        if (curr->endOfWord) { // If it's the end of a word
            if (curr->sentiment >= 0) { // If the sentiment is positive
                vec[0] += curr->sentiment; // Update the positive sentiment score
            } else {
                vec[1] += curr->sentiment; // Update the negative sentiment score
            }
        }

        return vec; // Return the vector of sentiment scores
    }
    
    // Function to normalize a value using logarithm
    inline double normalize(int x) const {
        return log10(x); // Return the base-10 logarithm of x
    }
};
