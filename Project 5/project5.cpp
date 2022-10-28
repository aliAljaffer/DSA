#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "Trie.h"
#include <fstream>
void fileReader(string, Trie *);
int main()
{
   Trie *tr = new Trie;
   fileReader("words.txt", tr);
   vector<string> result;
   string userWord;
   string userAnswer;
   while (1)
   {
      cout << "Enter a word you'd like to autocomplete (enter \"byebye\" to terminate)" << endl;
      cin >> userWord;
      if (userWord == "byebye")
         return 0;
      tr->autocomplete(userWord, result);
      int numWords = result.size();
      cout << "There are " << to_string(numWords) << " words that start with " << userWord << endl;
      cout << "Would you like to display them?" << endl;
      cin >> userAnswer;
      if (userAnswer == "byebye")
         return 0;
      if (userAnswer[0] == 'Y' || userAnswer[0] == 'y')
      {
         for (auto x : result)
         {
            cout << "\t" + x << endl;
         }
      }
   }
}

void fileReader(string filename, Trie *myTrie)
{
   ifstream infile(filename);
   string word;
   while (infile >> word)
   {
      myTrie->insert(word);
   }
}