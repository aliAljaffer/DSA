#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "Trie.h"
#include <fstream>
#include <time.h>
void populateTrie(string, Trie *);
void memTest();
int main()
{
   srand(time(NULL));
   // Trie tr;
   // tr.insert("ali");
   // tr.insert("aaa");
   // Trie tr2(tr);
   // Trie tr3 = tr;
   // tr.insert("abc");
   // tr2.insert("cba");
   // tr3.insert("aa");
   // cout << "done" << endl;
   // ifstream infile("words.txt");
   // string word;
   // while (infile >> word)
   // {
   //    tr.insert(word);
   // // }
   // tr->insert("a");
   // tr->insert("a");
   // cout << tr.completeCount("a") << endl;
   // delete tr;
   for (int i = 0; i < 10; i++)
      memTest();
   cout << "Trie deleted" << endl;
   // Trie tr2(tr);
   // cout << tr.completeCount("a") << endl;
   // cout << tr2.completeCount("a") << endl;
}

void populateTrie(string filename, Trie *myTrie)
{
   ifstream infile(filename);
   string word;
   while (infile >> word)
   {
      myTrie->insert(word);
   }
   infile.close();
}

void memTest()
{
   Trie tr;

   // ifstream infile("words.txt");

   for (int i = 0; i < 10000; i++)
   {
      string word = "";
      for (int j = 0; j < 10; j++)
      {
         int random = rand() % 26;
         char ranC = 'a' + random;
         word += ranC;
      }
      tr.insert(word);
      word.empty();
   }

   // while (infile >> word)
   // {
   //    tr.insert(word);
   // }
   cout << "About to delete trie" << endl;
}

// // MAIN METHOD
// int main()
// {
//    Trie *tr = new Trie;
//    populateTrie("words.txt", tr);

//    vector<string> result;
//    while (1)
//    {
//       string userWord;
//       string userAnswer;
//       cout << "Enter a word you'd like to autocomplete (enter \"!\" to terminate)" << endl;
//       cin >> userWord;
//       if (userWord == "!")
//          return 0;
//       result = tr->complete(userWord);
//       int numWords = result.size();
//       if (numWords)
//       {
//          cout << "There are " << to_string(numWords) << " words that start with " << userWord << endl;
//          cout << "Would you like to display them?" << endl;
//          cin >> userAnswer;
//       }
//       else
//          cout << "There are no words that start with " << userWord << endl;
//       if (userAnswer == "!")
//          return 0;
//       if (userAnswer[0] == 'Y' || userAnswer[0] == 'y')
//       {
//          cout << "----------------" << endl;
//          for (auto x : result)
//          {
//             cout << "\t" + x << endl;
//          }
//       }
//    }
// }
// // //    // Trie tr;
//    //  tr.insert("five");
//    //  tr.insert("fire");
//    //  tr.insert("free");
//    //  vector<string> result;
//    //  tr.autocomplete("x", result);
//    //  for (auto x : result)
//    //  {
//    //     cout << "\t" + x << endl;
//    //  }
// }
