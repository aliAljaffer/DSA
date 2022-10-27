#include "Trie.h"
using namespace std;
/*
 * Ali Aljaffer - CS3100 - UID: U01006515
 *          Project 4 - AVL Tree
 * A map implementation that uses int:string
 * and its functions are implemented according
 * to the given requirements of the provided PDF.
 */
Trie::Trie()
{
   root = new TrieNode();
   count = 1;
   size = 0;
}
bool Trie::insert(string word)
{
   TrieNode *curr = nullptr;
   for (int i = 0; i < word.length(); i++)
   {
      if (!root->alphabet[word[i] - 'a'])
      {
         root->alphabet[word[i] - 'a'] = new TrieNode();
         count++;
         curr = root->alphabet[word[i] - 'a'];
      }
      else if (curr)
      {
         curr->alphabet[word[i] - 'a'] = new TrieNode();
         count++;
         curr = curr->alphabet[word[i] - 'a'];
      }
   }
}