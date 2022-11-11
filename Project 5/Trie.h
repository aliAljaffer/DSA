#include <string>
#include <iostream>
#include <exception>
#include <vector>
#pragma once
#define ALPHABET_SIZE 26
using namespace std;
/*
 * Ali Aljaffer - CS3100 - UID: U01006515
 * Alphabet trie implementation that uses lowercase
 * letters.
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
         endOfWordNode = false;
      }

      ~TrieNode()
      {
      }
   };

   TrieNode *root;
   void copyHelper(const Trie &, TrieNode *, TrieNode *);
   bool readFromFile(string);
   void destruct(TrieNode *);
   string lower(string);
   void traverse(TrieNode *, string, vector<string> &);
   vector<string> autocomplete(string, vector<string> &);

public:
   Trie();
   Trie(string);
   ~Trie();
   Trie(const Trie &);
   bool insert(string);
   int count();
   int getSize();
   int getNumWords();
   int getNumNodes();
   int completeCount(string);
   bool find(string);
   vector<string> complete(string);
   Trie &operator=(const Trie &);
};