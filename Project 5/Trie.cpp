#include "Trie.h"
using namespace std;
/*
 * Ali Aljaffer - CS3100 - UID: U01006515
 */
Trie::Trie()
{
   root = new TrieNode();
   count = 1;
   size = 0;
}
Trie::~Trie()
{
}
bool Trie::insert(string word)
{
   TrieNode *curr = root;
   for (int i = 0; i < word.length(); i++)
   {
      int index = word[i] - 'a';
      if (!curr->alphabet[index])
      {
         curr->alphabet[index] = new TrieNode();
         size++;
         curr = curr->alphabet[index];
      }
      else
         curr = curr->alphabet[word[i] - 'a'];
   }
   curr->endOfWordNode = true;
   count++; // One word added
   return 1;
}