#include "Sequence.h"
#include <exception>
/* Ali Aljaffer - CS3100 - UID: U01006515
 * Project 3 - Double linked list
 * A class that implements the functions specified
 * in the header file.
 */
/// @brief Parametric constructor for a Sequence
/// @param sz - the size of the sequence
Sequence::Sequence(size_type sz)
{
   if (sz < 0)
      throw exception();
   if (sz == 0)
   {
      // Case when creating an empty sequence
      head = nullptr;
      tail = nullptr;
      numElts = 0;
   }
   else
   {
      // Case when creating any sz-sized sequence
      this->tail = nullptr;
      this->numElts = 1;
      SequenceNode *newSqNode = new SequenceNode;
      newSqNode->elt = 0;
      this->head = newSqNode;
      SequenceNode *current = head;
      while (this->numElts < sz)
      {
         SequenceNode *nextNode = new SequenceNode;
         nextNode->elt = 0;
         current->next = nextNode;
         nextNode->prev = current;
         current = nextNode;
         this->numElts++;
      }
      this->tail = current;
   }
}

/// @brief Copy constructor
/// @param s - Reference to the sequence getting copied
Sequence::Sequence(const Sequence &s)
{
   head = nullptr;
   tail = nullptr;
   numElts = s.numElts;
   SequenceNode *copyNode = s.head;
   SequenceNode *previous = nullptr;
   while (copyNode)
   {
      SequenceNode *nodeToAdd = new SequenceNode;
      if (head == nullptr)
         head = nodeToAdd;
      nodeToAdd->elt = copyNode->elt;
      nodeToAdd->prev = previous;
      if (previous != nullptr)
         previous->next = nodeToAdd;
      previous = nodeToAdd;
      copyNode = copyNode->next;
   }
   previous->next = nullptr;
   tail = previous->next;
}

/// @brief Sequence destructor
Sequence::~Sequence()
{
   // erase(0, numElts) ?
   SequenceNode *current = head;
   SequenceNode *killNext;
   while (current)
   {
      killNext = current->next;
      delete current;
      current = killNext;
   }
   tail = head = nullptr;
}

/// @brief Overridden equals operator. Sets the left sided sequence equal to the right sided sequence
/// @param s - The sequence to copy
/// @return this - Pointer to the new copy of s
Sequence &Sequence::operator=(const Sequence &s)
{
   // Kill everything in *this*
   // SequenceNode *current = head;
   // SequenceNode *killNext;
   // while (current)
   // {
   //    killNext = current->next;
   //    delete current;
   //    current = killNext;
   // }
   erase(0, numElts);
   // Copy from s
   numElts = s.numElts;
   head = nullptr;
   tail = nullptr;
   SequenceNode *copyNode = s.head;
   SequenceNode *previous = nullptr;
   while (copyNode)
   {
      SequenceNode *nodeToAdd = new SequenceNode;
      if (head == nullptr)
      {
         head = nodeToAdd;
      }
      nodeToAdd->elt = copyNode->elt;
      nodeToAdd->prev = previous;
      if (previous != nullptr)
         previous->next = nodeToAdd;
      previous = nodeToAdd;
      copyNode = copyNode->next;
   }
   previous->next = nullptr;
   tail = previous;
   return *this;
}

/// @brief Overridden brackets operator enables using indecies to get an element from the sequence
/// @param position - the position of the element to return
/// @return elt - the element at the specified position in the sequence
Sequence::value_type &Sequence::operator[](size_type position)
{
   if (position < 0 || position > numElts - 1)
   {
      throw exception();
   }
   SequenceNode *current = head;
   int currentPos = 0;
   while (currentPos != position)
   {
      current = current->next;
      currentPos++;
   }
   return current->elt;
}

void Sequence::push_back(const value_type &value)
{
   SequenceNode *newSqNode = new SequenceNode;
   newSqNode->elt = value;
   if (empty())
   {
      head = newSqNode;
      newSqNode->prev = nullptr;
   }
   else
   {
      tail->next = newSqNode;
      newSqNode->prev = tail;
   }
   newSqNode->next = nullptr;
   tail = newSqNode;
   numElts++;
}

void Sequence::pop_back()
{
   if (empty())
      throw exception();
   SequenceNode *tailPtr = tail;
   if (numElts == 1)
   {
      head = nullptr;
      tail = nullptr;
   }
   else
   {
      tail = tail->prev;
      tail->next = nullptr;
   }
   numElts--;
   delete tailPtr;
}

void Sequence::insert(size_type position, value_type value)
{
   if (position < 0 || position > numElts - 1)
   {
      throw exception();
   }
   else if (position == 0)
   {
      SequenceNode *nodeToAdd = new SequenceNode;
      nodeToAdd->elt = value;
      nodeToAdd->next = head;
      nodeToAdd->prev = nullptr;
      head = nodeToAdd;
   }
   else
   {
      SequenceNode *current = head;
      SequenceNode *nodeToAdd = new SequenceNode;
      nodeToAdd->elt = value;
      int currentPos = 0;
      while (currentPos != position)
      {
         current = current->next;
         currentPos++;
      }
      nodeToAdd->next = current;
      nodeToAdd->prev = current->prev;
      current->prev->next = nodeToAdd;
      current->prev = nodeToAdd;
   }
   numElts++;
}

const Sequence::value_type &Sequence::front() const
{
   if (empty())
      throw exception();
   return head->elt;
}

const Sequence::value_type &Sequence::back() const
{
   if (empty())
      throw exception();
   return tail->elt;
}

bool Sequence::empty() const
{
   return head == nullptr;
}

Sequence::size_type Sequence::size() const
{
   return numElts;
}

void Sequence::clear()
{
   if (empty())
      return;
   erase(0, numElts);
}

void Sequence::erase(size_type position, size_type count)
{
   int currNumElts = numElts;
   if (position + count - 1 > numElts || position < 0 || position > numElts - 1 || count <= 0 || empty())
      throw exception();

   int currentPos = 0;
   int numKilled = 0;
   SequenceNode *current = head;
   while (currentPos != position)
   {
      current = current->next;
      currentPos++;
   }
   SequenceNode *savePrevious = (position != 0) ? current->prev : nullptr;
   SequenceNode *nextToKill;
   while (numKilled != count)
   {
      nextToKill = current->next;
      delete current;
      numElts--;
      current = nextToKill;
      numKilled++;
   }
   if (position == 0 && count == currNumElts)
   {
      head = nullptr;
      tail = nullptr;
      return;
   }
   else if (position == 0)
   {
      head = current;
      head->prev = nullptr;
   }
   else if (current == nullptr)
   {
      current = savePrevious;
      current->next = nullptr;
      tail = current;
   }
   else
   {
      current->prev = savePrevious;
      savePrevious->next = current;
   }

   current = head;
   while (current->next)
   {
      current = current->next;
   }
   tail = current;
}
ostream &operator<<(ostream &os, Sequence &s)
{
   if (s.empty())
   {
      os << "The sequence is empty." << endl;
      return os;
   }
   int currentPos = 0;
   os << "[";
   while (currentPos < s.size())
   {
      if (currentPos == (s.size() - 1)) // When at last index, end with ]
      {
         os << s[currentPos] << "]" << endl;
         break;
      }
      os << s[currentPos] << ", ";
      currentPos++;
   }
   return os;
}
// Testing connections. If head can reach tail and vice versa. Tests nexts and prevs.
bool Sequence::traverser()
{
   if (empty())
      throw exception();
   cout << "Traversing a sequence of " << numElts << " element(s)." << endl;
   bool reachedTailFromHead = 0;
   bool reachedHeadFromTail = 0;
   SequenceNode *current = head;
   cout << "Head to tail:\n";
   while (current)
   {
      cout << current->elt << endl;
      current = current->next;
   }
   reachedTailFromHead = 1;
   current = tail;
   cout << "\nTail to head:\n";
   while (current)
   {
      cout << current->elt << endl;
      current = current->prev;
   }
   reachedHeadFromTail = 1;
   return reachedHeadFromTail && reachedTailFromHead;
}