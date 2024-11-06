#include <iostream> // Include the iostream library for input and output operations
#include "trie.h" // Include the trie header file
#include "DSString.h" // Include the DSString header file
#include <fstream> // Include the fstream library for file operations
using namespace std; // Use the standard namespace

// Function declarations
vector<int> predictSentiment(TrieNode tr, TrieNode* root); // Declare the predictSentiment function
double findAccuracy(const vector<int>& pS); // Declare the findAccuracy function
void writePredictionsToCSV(const vector<int>& predictions, const string& filename); // Declare the writePredictionsToCSV function

int main() {
    TrieNode tr; // Create a TrieNode object
    TrieNode* root = new TrieNode(); // Create a new TrieNode object and assign its pointer to root
    unsigned int findCol = 0; // Initialize findCol to 0
    int sentiment; // Declare an integer variable for sentiment
    DSString str; // Declare a DSString variable for reading strings
    vector<DSString> words; // Declare a vector to store words
    ifstream sTrain("train_dataset_20k_modified.csv"); // Open the training dataset file
    vector<int> predictedSentiments; // Declare a vector to store predicted sentiments
    double accuracy = 0.0; // Initialize accuracy to 0.0

    // Check if the training file is open
    if (!sTrain.is_open()) {
        cout << "File is not open!!"; // Print an error message if the file is not open
        return -1; // Return -1 to indicate an error
    } else {
        cout << "file open ;O\n\n"; // Print a success message if the file is open
    }
    
    getline(sTrain, str); // Ignore headers by reading the first line

    // Read the training file line by line
    while (!sTrain.eof()) {
        if (findCol == 0) { // Find the first column in each row
            getline(sTrain, str, ','); // Read the first column
            sentiment = stoi(str.c_str()); // Convert the string to an integer and assign it to sentiment
        } else if (findCol != 5) {
            getline(sTrain, str, ','); // Read the other columns
        } else if (findCol == 5) { // Find the fifth column in each row
            getline(sTrain, str); // Read the fifth column

            words = tr.parseSentence(str); // Parse the sentence into words
            for (int i = 0; i < words.size(); i++) {
                tr.insertLetter(root, words.at(i), sentiment); // Insert each word into the trie
                // cout << "Inserted: [ " << words.at(i) << " ]" << endl; // Uncomment to print inserted words
            }
            findCol = -1; // Reset findCol to -1
        }
        findCol++; // Increment findCol
    }

    sTrain.close(); // Close the training file
    tr.mostChargedWords(); // Display the most charged words

    predictedSentiments = predictSentiment(tr, root); // Predict sentiments

    accuracy = findAccuracy(predictedSentiments); // Calculate accuracy

    cout << "The accuracy is: " << accuracy << endl; // Print the accuracy

    // Write predictions to a CSV file
    //writePredictionsToCSV(predictedSentiments, "predictedSentiments.txt", accuracy); // Call the function to write predictions to a CSV file

    return 0; // Return 0 to indicate successful execution
}

// Function to predict sentiments
vector<int> predictSentiment(TrieNode tr, TrieNode* root) {
    int pSent = 0, findCol = 0; // Initialize pSent and findCol to 0
    DSString str; // Declare a DSString variable for reading strings
    vector<DSString> words; // Declare a vector to store words
    vector<int> posAndNeg = {0, 0}, allPredictions = {0}; // Initialize vectors for positive/negative counts and predictions
    double posPredict = 0.0, negPredict = 0.0, total = 0.0; // Initialize prediction variables

    ifstream sTest("test_dataset_10k.csv"); // Open the test dataset file
    if (!sTest.is_open()) {
        cout << "File is not open!!"; // Print an error message if the file is not open
        return {-1}; // Return -1 to indicate an error
    } else {
        cout << "file is open\n\n"; // Print a success message if the file is open
    }
    
    getline(sTest, str); // Ignore headers by reading the first line

    // Read the test file line by line
    while (!sTest.eof()) {
        if (findCol != 4) {
            getline(sTest, str, ','); // Read the columns except the tweet column
        } else if (findCol == 4) { // Find the tweet column in each row
            getline(sTest, str); // Read the tweet column

            words = tr.parseSentence(str); // Parse the sentence into words
            for (int j = 0; j < words.size(); j++) {
                posAndNeg = tr.analyzeWord(root, words.at(j), posAndNeg); // Analyze each word
            }
            posPredict = tr.normalize(posAndNeg.at(0)); // Normalize positive sentiment
            negPredict = tr.normalize(-posAndNeg.at(1)) +  1.5 * tr.normalize(-posAndNeg.at(1)); // Normalize negative sentiment
            total = posPredict - negPredict; // Calculate total sentiment

            if (total >= 0) { pSent = 4; } // Assign positive sentiment
            else { pSent = 0; } // Assign negative sentiment

            allPredictions.push_back(pSent); // Add the prediction to the vector

            findCol = -1; // Reset findCol to -1
            posAndNeg = {0, 0}; // Reset posAndNeg
        }
        findCol++; // Increment findCol
    } 

    return allPredictions; // Return the predictions
}

// Function to calculate accuracy
double findAccuracy(const vector<int>& pS) {
    ifstream sTest("test_dataset_sentiment_10k.csv"); // Open the test dataset file with actual sentiments
    DSString str; // Declare a DSString variable for reading strings
    int total = 0; // Initialize total to 0
    double average = 0; // Initialize average to 0

    getline(sTest, str); // Ignore headers by reading the first line

    // Compare predicted sentiments with actual sentiments
    for (int i = 1; i < pS.size(); i++) {
        getline(sTest, str, ','); // Read the actual sentiment
        if (pS.at(i) == stoi(str.c_str())) {
            total++; // Increment total if the prediction matches the actual sentiment
        }
        getline(sTest, str); // Read the next line
    }

    average = double(total) / double(pS.size()); // Calculate the average accuracy

    return average; // Return the accuracy
}

// Function to write predictions to a CSV file
void writePredictionsToCSV(const vector<int>& predictions, const string& filename, double acc) {
    ofstream outFile(filename); // Open the output file
    ifstream sTest("test_dataset_sentiment_10k.csv");
    DSString str;
    int count = 0;
    // Check if the file is open
    if (!outFile.is_open()) {
        cout << "Failed to open file for writing: " << filename << endl; // Print an error message if the file is not open
        return; // Return to exit the function
    }

    getline(sTest,str);
    outFile << "Accuracy: " << acc << endl << endl;
    outFile << "Predicted," << str << endl;
    // Write predictions to the file
    for (int i = 1; i < predictions.size(); i++) {
        getline(sTest,str);
        outFile << predictions.at(i) << "," << str << endl; // Write each prediction to a new line
    }

    outFile.close(); // Close the file
}
