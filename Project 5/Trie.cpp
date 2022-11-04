#include "Trie.h"
#include <fstream>
// Issues: Destructor going into ptr array after deletion
//         Check insert to make sure it's not using find first
using namespace std;
/*
 * Ali Aljaffer - CS3100 - UID: U01006515
 */

/// @brief No args constructor creates the root and sets the class fields.
Trie::Trie()
{
   root = new TrieNode();
   numWords = 0;
   numNodes = 1;
}
/// @brief Given a fileName, a trie is created using the content of the text file
/// @param fileName the path to the file containing the words to insert into the trie
Trie::Trie(string fileName)
{
   root = new TrieNode();
   numWords = 0;
   numNodes = 1;
   readFromFile(fileName);
}
/// @brief Copy constructor for a Trie
/// @param copyMe The trie to copy from
Trie::Trie(const Trie &copyMe)
{
   root = new TrieNode();
   numWords = 0;
   numNodes = 1;
   copyHelper(copyMe, copyMe.root, root);
}
/// @brief Trie destructor that uses a helper function destruct()
Trie::~Trie()
{
   destruct(root);
}
/// @brief Recursive destructor function that visits each node until it reaches a leaf child and deletes it
/// @param node The starting point for destruction
void Trie::destruct(TrieNode *node)
{
   if (!node)
      return;
   for (int i = 0; i < ALPHABET_SIZE; i++)
   {
      if (node->alphabet[i])
         destruct(node->alphabet[i]);
      node->alphabet[i] = nullptr;
   }
   delete node;
}

/// @brief Overloaded operator = that functions the same as a copy constructor, but it destroys the left hand side trie first
/// @param copyMe The trie to copy
/// @return returns the Trie after copying
Trie &Trie::operator=(const Trie &copyMe)
{
   destruct(root);
   root = new TrieNode;
   numNodes = 1;
   copyHelper(copyMe, copyMe.root, root);
   return *this;
}

/// @brief Copy helper function for use with copy constructor and assignment operator overload
/// @param copyMe The trie to copy
/// @param nodeCopy the node to copy from copyMe
/// @param curr the current node in this trie
void Trie::copyHelper(const Trie &copyMe, TrieNode *nodeCopy, TrieNode *curr)
{
   if (!copyMe.numNodes || !nodeCopy)
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
         copyHelper(copyMe, nodeCopy->alphabet[i], curr->alphabet[i]);
      }
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
      if (node->alphabet[i])
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
   // Want to avoid running find first
   // if (find(word))
   //    return 0;
   word = lower(word);
   if (word.length() == 0)
      return 0;
   TrieNode *curr = root;
   for (int i = 0; i < word.length(); i++)
   {
      int index = word[i] - 'a';
      if (index < 0 || index > 25)
      {
         // Ensures that the letter is smallcase.
         return false;
      }
      if (!curr->alphabet[index])
      {
         curr->alphabet[index] = new TrieNode();
         numNodes++;
      }
      curr = curr->alphabet[index];
   }
   if (!curr->endOfWordNode)
   {
      // if the most recently created node for the word(last letter) is not an end of word, then the
      // word we just went through is new and therefore we increment numWords and set endOFWord to true
      curr->endOfWordNode = true;
      numWords++;
      return 1;
   }

   return 0;
}

bool Trie::readFromFile(string fileName)
{
   ifstream infile(fileName);
   string word;
   while (infile >> word)
   {
      insert(word);
   }
   infile.close();
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