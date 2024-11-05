#include <iostream>
#include "trie.h"
#include <fstream> 
using namespace std;

vector<int> predictSentiment(TrieNode tr, TrieNode* root);
double findAccuracy(vector<int> pS);

int main(){

    TrieNode tr;
    TrieNode* root = new TrieNode();
    unsigned int findCol = 0;
    int sentiment;
    string str;
    vector<string> words;
    ifstream sTrain("C:/Users/lukev/Projects/Data Structures/Voinov_CS5393-002_Project3/train_dataset_20k_modified.csv");
    vector<int> predictedSentiments;
    double accuracy = 0.0;


    if(!sTrain.is_open()){
        cout << "File is not open!!";
        return -1;
    }
    else{
        cout << "file open ;O\n\n";
    }
    
    getline(sTrain, str);//ignore headers

    while( !sTrain.eof() ){
        if(findCol == 0){ // to find the first column in each row
            getline(sTrain, str, ',');
            sentiment = stoi(str);
        }
        else if(findCol != 5){
            getline(sTrain, str, ',');
        }
        else if(findCol == 5){ // to find the fifth column in each row
            getline(sTrain,str);

            words = tr.parseSentence(str);
            for(int i = 0; i < words.size(); i++){
                tr.insertLetter(root, words.at(i), sentiment);

                //cout << "Inserted: [ " << words.at(i) << " ]" << endl;
            }
            findCol = -1;
        }
        findCol++;
    }

    sTrain.close();
    tr.mostChargedWords();

    predictedSentiments = predictSentiment(tr, root);

    accuracy = findAccuracy(predictedSentiments);

    cout << "The accuracy is: " << accuracy << endl;

    return 0;
};

vector<int> predictSentiment(TrieNode tr, TrieNode* root){
    int pSent = 0, findCol = 0;
    string str;
    vector<string> words;
    vector<int> posAndNeg = {0,0}, allPredictions;
    double posPredict = 0.0, negPredict = 0.0 , total = 0.0;

    ifstream sTest("C:/Users/lukev/Projects/Data Structures/Voinov_CS5393-002_Project3/test_dataset_10k.csv");


    if(!sTest.is_open()){
        cout << "File is not open!!";
        return {-1};
    }
    else{
        cout << "file is open\n\n";
    }
    
    getline(sTest, str);//ignore headers

    while( !sTest.eof() ){
        if(findCol != 4){
            getline(sTest, str, ',');
        }
        else if(findCol == 4){ // to find the tweet column in each row
            getline(sTest,str);

            words = tr.parseSentence(str);
            for(int i = 0; i < words.size(); i++){
                tr.analyzeWord(root, words.at(i), posAndNeg);
                //cout << "Analyzed: [ " << words.at(i) << " ]" << endl;
            }
            posPredict = tr.calculateSigmoidApprox(posAndNeg.at(0));
            negPredict = tr.calculateSigmoidApprox(posAndNeg.at(1));
            total = posPredict - negPredict;

            if(total >= 0){ pSent = 4; }
            else{ pSent = 0; }
            allPredictions.push_back(pSent);

            findCol = -1;
        }
        findCol++;
    }

    return allPredictions;
}

double findAccuracy(vector<int> pS){

    ifstream sTest("C:/Users/lukev/Projects/Data Structures/Voinov_CS5393-002_Project3/test_dataset_sentiment_10k.csv");
    string str;
    int total = 0, average = 0;

    for(int i = 0; i < pS.size(); i++){
        getline(sTest, str, ',');
        if(pS.at(i) == stoi( str ) ){
            total++;
        }
    }

    average = double(total) / double( pS.size() );

    return average;
}