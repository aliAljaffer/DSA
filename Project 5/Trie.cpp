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
Trie::Trie(const Trie &copyMe)
{
   root = new TrieNode();
   numWords = 0;
   numNodes = 1;
   copyHelper(copyMe, copyMe.root, root);
}
Trie::~Trie()
{
   destruct(root);
}
void Trie::destruct(TrieNode *node)
{
   if (!node)
      return;
   for (int i = 0; i < ALPHABET_SIZE; i++)
   {
      if (node->alphabet[i])
         destruct(node->alphabet[i]);
   }
   delete node;
}
void Trie::copyHelper(const Trie &copyMe, TrieNode *nodeCopy, TrieNode *curr)
{
   if (!copyMe.numNodes || !nodeCopy->alphabet)
   {
      return;
   }
   for (int i = 0; i < ALPHABET_SIZE; i++)
   {
      if (nodeCopy->alphabet[i])
      {
         curr->alphabet[i] = new TrieNode();
         if (nodeCopy->alphabet[i]->endOfWordNode)
         {
            curr->alphabet[i]->endOfWordNode = true;
            numWords++;
         }
         numNodes++;
      }
      copyHelper(copyMe, nodeCopy->alphabet[i], curr->alphabet[i]);
   }
}
string Trie::lower(string word)
{
   string lowerCaseWord = "";
   for (char c : word)
   {
      lowerCaseWord += c;
   }
   return lowerCaseWord;
}

void Trie::traverse(TrieNode *node, string carryString, vector<string> &results)
{
   if (!node)

      return;
   for (int i = 0; i < ALPHABET_SIZE; i++)
   {
      if (node->alphabet[i] != nullptr)
         traverse(node->alphabet[i], carryString + (char)('a' + i), results);
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
   if (wordToComplete.length() == 0)
      return results;
   wordToComplete = lower(wordToComplete);
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
vector<string> Trie::complete(string word)
{
   vector<string> tempVec;
   return autocomplete(word, tempVec);
}
int Trie::completeCount(string word)
{
   return complete(word).size();
}
bool Trie::find(string word)
{
   if (numWords == 0)
      return false;
   word = lower(word);
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
   word = lower(word);
   if (word.length() == 0)
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