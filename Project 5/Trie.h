#include <string>
#include <iostream>
#include <exception>
#include <vector>
#pragma once
#define ALPHABET_SIZE 26
using namespace std;
/*
 * Ali Aljaffer - CS3100 - UID: U01006515

 */

class Trie
{
private:
   int numWords;
   int numNodes;
   class TrieNode
   {
   public:
      TrieNode *alphabet[ALPHABET_SIZE];
      bool endOfWordNode;

      TrieNode()
      {
         for (int i = 0; i < ALPHABET_SIZE; i++)
         {
            alphabet[i] = nullptr;
         }
         endOfWordNode = 0;
      }

      ~TrieNode()
      {
      }
   };
   TrieNode *root;

public:
   Trie();
   ~Trie();
   Trie(const Trie &);
   void destruct(TrieNode *);
   bool insert(string);
   void copyHelper(const Trie &, TrieNode *, TrieNode *);
   int getCount();
   int getSize();
   int getNumWords();
   int getNumNodes();
   int completeCount(string);
   bool find(string);
   string lower(string);
   void traverse(TrieNode *, string, vector<string> &);
   vector<string> autocomplete(string, vector<string> &);
   vector<string> complete(string);
   Trie &operator=(const Trie &);
   // void copyHelper(TrieNode *, const Trie &);
   // void bulldozer(TrieNode *);
};