#include "Trie.h"
using namespace std;
/*
 * Ali Aljaffer - CS3100 - UID: U01006515
 */
Trie::Trie()
{
   root = new TrieNode();
   count = 0;
   size = 1;
}
Trie::~Trie()
{
}
string Trie::traverse(TrieNode *node, string carryString, vector<string> &results)
{
   if (!node)
      return "";
   for (int i = 0; i < ALPHABET_SIZE; i++)
   {
      if (node->alphabet[i] != nullptr)
      {
         traverse(node->alphabet[i], carryString + (char)('a' + i), results);
      }
   }
   if (node->endOfWordNode)
      results.push_back(carryString);
   return "";
}
vector<string> Trie::autocomplete(string wordToComplete, vector<string> &results)
{
   TrieNode *curr = root;
   for (int i = 0; i < wordToComplete.length(); i++)
   {
      int index = wordToComplete[i] - 'a';
      if (!curr->alphabet[index])
      {
         return results;
      }
      curr = curr->alphabet[index];
   }
   traverse(curr, wordToComplete, results);
   return results;
}
bool Trie::find(string word)
{
   TrieNode *curr = root;
   for (int i = 0; i < word.length(); i++)
   {
      int index = word[i] - 'a';
      if (!curr->alphabet[index])
      {
         return 0;
      }
      curr = curr->alphabet[index];
   }
   if (curr->endOfWordNode)
   {
      return 1;
   }
   return 0;
}

bool Trie::insert(string word)
{
   if (find(word) || word.length() == 0)
      return 0;
   TrieNode *curr = root;
   for (int i = 0; i < word.length(); i++)
   {
      int index = word[i] - 'a';
      if (index < 0 || index > 25)
      {
         // Ensures that the letter is small.
         return false;
      }
      if (!curr->alphabet[index])
      {
         curr->alphabet[index] = new TrieNode();
         size++;
         curr = curr->alphabet[index];
      }
      else
         curr = curr->alphabet[index];
   }
   curr->endOfWordNode = true;
   count++; // One word added
   return 1;
}