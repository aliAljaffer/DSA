#include "Trie.h"
using namespace std;
/*
 * Ali Aljaffer - CS3100 - UID: U01006515
 */
Trie::Trie()
{
   root = new TrieNode();
   numWords = 0;
   numNodes = 1;
}
Trie::~Trie()
{
}
bool Trie::insert(string word)
{
   // Find here
   TrieNode *curr = root;
   for (int i = 0; i < word.length(); i++)
   {
      int index = word[i] - 'a';
      if (!curr->alphabet[index])
      {
         curr->alphabet[index] = new TrieNode();
         numNodes++;
         curr = curr->alphabet[index];
      }
      else
         curr = curr->alphabet[index];
   }

   curr->endOfWordNode = true;
   numWords++; // One word added
   return 1;
}