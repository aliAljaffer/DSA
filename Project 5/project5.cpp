#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "Trie.h"
#include <fstream>
#include <time.h>
/*
 * Ali Aljaffer - CS3100 - UID: U01006515
 * Alphabet trie implementation that uses lowercase
 * letters.
 */
// // MAIN METHOD
int main()
{
   Trie tr("words.txt");
   vector<string> result;
   while (1)
   {
      string userWord;   // User's chosen prefix
      string userAnswer; // User's choice to display the completions
      cout << "Enter a word you'd like to autocomplete (press ! to terminate)" << endl;
      cin >> userWord;
      if (userWord == "!")
         return 0;
      result = tr.complete(userWord);
      int wordsFound = result.size();
      if (wordsFound)
      {
         cout << "There are " << to_string(wordsFound) << " words that start with " << userWord << endl;
         cout << "Would you like to display them?" << endl;
         cin >> userAnswer;
      }
      else
         cout << "There are no words that start with " << userWord << endl;
      if (userAnswer == "!")
         return 0;
      if (userAnswer[0] == 'Y' || userAnswer[0] == 'y')
      {
         cout << "----------------" << endl;
         for (auto x : result)
         {
            cout << "\t" + x << endl;
         }
      }
   }
}
