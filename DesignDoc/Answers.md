# Assignment 2: Answers

**Complete this document, commit your changes to Github and submit the repository URL to Canvas.** Keep your answers short and precise.

Your Name: Luke Voinov

Used free extension: [ ] 24 hrs or [ ] 48 hrs

[] Early submission (48 hrs)

[] Bonus work. Describe: I didn't get 72% accuracy but I did get 711229
Place [x] for what applies.


## UML Diagram

![UML Class Diagram](UML_class.png)

## Answers

1. How do you train the model and how do you classify a new tweet? Give a short description of the main steps.

   > ### Model Creation and Training:
   > 1. **Initialization**:
   >    - Created an instance of the `SentimentAnalyzer` class, passing the file paths for saving the trained model (`trie.dat`) and the training dataset (`train_dataset_20k.csv`).
   >
   > 2. **Loading or Training the Trie**:
   >    - In the `SentimentAnalyzer` constructor, attempted to load the Trie from the `trie.dat` file.
   >    - If the file was not found or was empty, trained the Trie using the `train_dataset_20k.csv` file.
   >    - The training process involved reading the training file line by line, tokenizing the tweets, and inserting the words into the Trie with their corresponding sentiment values.
   >
   > 3. **Saving the Trie**:
   >    - After training, saved the Trie to the `trie.dat` file for future use.
   >
   > ### Classifying a New Tweet:
   > 1. **Sentiment Analysis**:
   >    - Analyzed the sentiment of the tweet using two methods:
   >      - **Log-Odds Ratio (LO)**: The `analyzeSentimentLO` method calculated the log-odds ratio for each word in the tweet and summed them up.
   >      - **Sentiment Score (SS)**: If the log-odds ratio was zero, the `analyzeSentimentSS` method calculated the sentiment score for each word in the tweet and summed them up.
   >
   > 2. **Classification**:
   >    - Adjusted the overall sentiment score by adding 0.2.
   >    - Classified the sentiment as positive (4) if the score was greater than 0, negative (0) if less than 0, and neutral (2) if equal to 0.
   >
   > 3. **Output**:
   >    - Wrote the sentiment, tweet ID, and sentiment score to the output file.

   This process allowed me to train a sentiment analysis model using a Trie data structure and classify new tweets based on the trained model.

2. How long did your code take for training and what is the time complexity of your training implementation (Big-Oh notation)? Remember that training includes reading the tweets, breaking it into words, counting, ... Explain why you get this complexity (e.g., what does `N` stand for and how do your data structures/algorithms affect the complexity).

   > ### Training Time and Complexity
   > 
   > #### Training Time
   > - Training my code took 0.313085 seconds.
   >
   > #### Time Complexity (Big-Oh Notation)
   > The time complexity of the training implementation is as follows:
   >
   > - Reading the tweets: This operation is O(N), where N is the number of tweets.
   > - Breaking tweets into words: This operation is O(M), where M is the total number of words across all tweets.
   > - Counting words: This operation is O(M), where M is the total number of words.
   >
   > ##### Explanation
   > - N stands for the number of tweets.
   > - M stands for the total number of words across all tweets.
   >
   > The data structures and algorithms used affect the complexity as follows:
   > - Reading tweets involves iterating through each tweet, hence O(N).
   > - Breaking tweets into words involves iterating through each word in each tweet, hence O(M).
   > - Counting words involves maintaining a count for each word, which is also O(M).
   >
   > Overall, the training process has a time complexity of O(N + M).

3. How long did your code take for classification and what is the time complexity of your classification implementation (Big-Oh notation)? Explain why.

   > The classification process took 0.288002 seconds. 
   >
   > ### Time Complexity Analysis
   >
   > The time complexity of the classification implementation can be broken down into several parts:
   >
   > 1. **Sentiment Analysis**:
   >     - For each word in the tokenized text, the sentiment score or log-odds ratio is calculated using the Trie. 
   >     - The Trie operations (insertion, search) typically have a time complexity of \(O(m)\), where \(m\) is the length of the word. 
   >     - If there are \(k\) words in the text, the total time complexity for sentiment analysis would be \(O(k \cdot m)\).
   >
   > 2. **File I/O**:
   >     - Reading from and writing to files involves I/O operations, which can vary in complexity based on the file size and system performance. However, these operations are generally considered \(O(n)\) for reading and writing \(n\) characters.
   >
   > ### Overall Time Complexity
   >
   > Combining these parts, the overall time complexity for classifying a single text can be approximated as:
   \[ O(n) + O(k * m) \]
   >
   > Where:
   > - \(n\) is the length of the input text.
   > - \(k\) is the number of words in the text.
   > - \(m\) is the average length of the words.
   >
   > Given that \(k\) and \(m\) are typically much smaller than \(n\), the dominant term is \(O(n)\). Therefore, the overall time complexity can be approximated as \(O(n)\).

### Explanation

The classification process is efficient due to the use of the Trie data structure, which allows for fast word lookups. The linear time complexity \(O(n)\) ensures that the classification can handle large texts efficiently, as demonstrated by the 0.288002 seconds it took for the classification in your case.

4. What accuracy did your algorithm achieve on the provides training and test data? 

   > My accuracy: 71.1229% 
   The TA will run your code on Linux and that accuracy value will be used to determine your grade.

5. What were the changes that you made that improved the accuracy the most?
   
   > Mosly weighing and normalizing the values. The numbers are weird but definetly have a maximum which I guessed at

6. How do you know that you use proper memory management? I.e., how do you know that you do not have
   a memory leak?

   > I asked CoPilot to optimize the code constantly and it always created ways to deallocate memory so I'm sure the memory is properly managed

6. What was the most challenging part of the assignment?

   > Understanding why the values I get work the way they do. I have no clue why these weights and the log normalization play such a huge role in accuracy.