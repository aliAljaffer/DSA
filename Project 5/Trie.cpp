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

Trie::TrieNode *Trie::findLastNode(string word)
{
   TrieNode *curr = root;
   for (int i = 0; i < word.length(); i++)
   {
      int index = word[i] - 'a';
      if (!curr->alphabet[index])
      {
         return nullptr;
      }
      curr = curr->alphabet[index];
   }
   return curr;
}
void Trie::traverse(TrieNode *node, string carryString, vector<string> &results)
{
   if (!node)
      return;
   for (int i = 0; i < ALPHABET_SIZE; i++)
   {
      if (node->alphabet[i] != nullptr)
      {
         traverse(node->alphabet[i], carryString + (char)('a' + i), results);
      }
   }
   if (node->endOfWordNode)
      results.push_back(carryString);
}
vector<string> Trie::autocomplete(string wordToComplete, vector<string> &results)
{
   if (results.size() > 0)
   {
      // Makes sure that results is empty.
      results.clear();
   }
   TrieNode *curr = findLastNode(wordToComplete);
   if (!curr)
   {
      // If curr is null then the word given doesn't exist in the trie
      return results;
   }
   traverse(curr, wordToComplete, results);
   return results;
}
bool Trie::find(string word)
{
   TrieNode *curr = findLastNode(word);
   // if curr is null, word isnt in the trie
   if (!curr)
      return 0;
   // if last node is the end of the word, return true
   if (curr->endOfWordNode)
   {
      return 1;
   }
   // its not the end of the word, false
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
int Trie::getCount()
{
   return getNumWords();
}
int Trie::getSize()
{
   return getNumNodes();
}
int Trie::getNumWords()
{
   return numWords;
}
int Trie::getNumNodes()
{
   return numNodes;
}