#include "Trie.h"
#include <fstream>
using namespace std;
/*
 * Ali Aljaffer - CS3100 - UID: U01006515
 * Alphabet trie implementation that uses lowercase
 * letters.
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
/// @brief Changes a word to lowercase
/// @param word the word to turn to uppercase
/// @return the final uppercase word
string Trie::lower(string word)
{
   string lowerCaseWord = "";
   for (char c : word)
   {
      lowerCaseWord += tolower(c);
   }
   return lowerCaseWord;
}

/// @brief Traverses the trie and adds the words it encounters
/// @param node the node to start traversing from
/// @param carryString the string to complete
/// @param results a vector of all the valid words that were encountered
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
/// @brief A helper function for complete.
/// @param wordToComplete the given prefix
/// @param results the results vector
/// @return a vector that contains the valid words found. returns empty if word isnt in trie
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
/// @brief completes the given word
/// @param word the word to complete
/// @return the vector resulting from the helper function autocomplete
vector<string> Trie::complete(string word)
{
   vector<string> tempVec;
   return autocomplete(word, tempVec);
}
/// @brief runs the complete function on the word and returns its size
/// @param word the word to complete
/// @return the size of the vector resulting from completing the given word
int Trie::completeCount(string word)
{
   return complete(word).size();
}
/// @brief finds a given word in the trie
/// @param word the word to find
/// @return true if found, false if not.
bool Trie::find(string word)
{
   if (numWords == 0 || word.length() == 0)
      return false;
   word = lower(word);
   TrieNode *curr = root;
   for (int i = 0; i < word.length(); i++)
   {
      int index = word[i] - 'a';
      if (!curr->alphabet[index])
      {
         return false;
      }
      curr = curr->alphabet[index];
   }
   if (curr->endOfWordNode)
   {
      return true;
   }
   return false;
}

/// @brief Inserts a given word in the trie. Does not accept duplicates.
/// @param word the word to insert
/// @return true if inserted, false if insertion failed (i.e. due to duplication)
bool Trie::insert(string word)
{
   word = lower(word);
   if (word.length() == 0)
      return false;
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
      return true;
   }

   return false;
}

/// @brief Given a file name, will try to read line by line and insert each line into the trie
/// @param fileName path to the file name that contains the words
/// @return true on success
bool Trie::readFromFile(string fileName)
{
   ifstream infile(fileName);
   string word;
   while (infile >> word)
   {
      insert(word);
   }
   infile.close();
   return true;
}
/// @brief getter function for the number of words in the trie
/// @return the number of words in the trie
int Trie::count()
{
   return getNumWords();
}

/// @brief getter function for the number of nodes in the trie
/// @return number of node in the trie
int Trie::getSize()
{
   return getNumNodes();
}
/// @brief getter function for the number of words in the trie
/// @return the number of words in the trie
int Trie::getNumWords()
{
   return numWords;
}
/// @brief getter function for the number of nodes in the trie
/// @return number of node in the trie
int Trie::getNumNodes()
{
   return numNodes;
}