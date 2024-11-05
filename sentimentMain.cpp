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
    vector<int> posAndNeg = {0,0}, allPredictions = {0};
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
            for(int j = 0; j < words.size(); j++){
                //cout << "Analyzed: [ " << words.at(j) << " ]" << endl;
                posAndNeg = tr.analyzeWord(root, words.at(j), posAndNeg);
            }
            posPredict = tr.normalize(posAndNeg.at(0));
            negPredict = tr.normalize(-posAndNeg.at(1)) + 0.2 * tr.normalize(-posAndNeg.at(1)) ;
            total = posPredict - negPredict;

            //cout << " Pos: " << posPredict << " Neg: "<< negPredict << " total: " << total << endl;

            if(total >= 0){ pSent = 4; }
            else{ pSent = 0; }
            allPredictions.push_back(pSent);

            findCol = -1;
            posAndNeg = {0,0};
        }
        findCol++;
    }

    return allPredictions;
}

double findAccuracy(vector<int> pS){

    ifstream sTest("C:/Users/lukev/Projects/Data Structures/Voinov_CS5393-002_Project3/test_dataset_sentiment_10k.csv");
    string str;
    int total = 0;
    double average = 0;

    getline(sTest, str);

    for(int i = 0; i < pS.size()-1; i++){
        getline(sTest, str, ',');
        if(pS.at(i) == stoi( str ) ){
            total++;
        }
        getline(sTest, str);
    }

    average = double(total) / double( pS.size() -1 );

    return average;
}

