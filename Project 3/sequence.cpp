#include "Sequence.h"
#include <exception>
/* Ali Aljaffer - CS3100
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
   if (!empty())
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
   // Advance current to position.
   while (currentPos != position)
   {
      current = current->next;
      currentPos++;
   }
   return current->elt;
}

/// @brief Adds a sequence node at the end of the sequence
/// @param value - The value to be stored in the new sequence node
void Sequence::push_back(const value_type &value)
{
   SequenceNode *newSqNode = new SequenceNode;
   newSqNode->elt = value;
   // If pushing to an empty sequence
   if (empty())
   {
      head = newSqNode;
      newSqNode->prev = nullptr;
   }
   // Other cases
   else
   {
      tail->next = newSqNode;
      newSqNode->prev = tail;
   }
   newSqNode->next = nullptr;
   tail = newSqNode;
   numElts++;
}

/// @brief removes the last sequence node in the sequence
void Sequence::pop_back()
{
   if (empty())
      throw exception();
   SequenceNode *tailPtr = tail;
   // save the tail
   // if we are popping a sequence of one element
   if (numElts == 1)
   {
      head = nullptr;
      tail = nullptr;
   }
   // any other cases
   else
   {
      tail = tail->prev;
      tail->next = nullptr;
   }
   numElts--;
   delete tailPtr;
}

/// @brief Inserts a new sequence node at the given position. Can only insert inbetween nodes.
/// @param position the position where the new node should be at
/// @param value the value stored in the new node
void Sequence::insert(size_type position, value_type value)
{
   // Rejected cases
   if (position < 0 || position > numElts - 1)
   {
      throw exception();
   }
   // If inserting on position 0 => the head.
   else if (position == 0)
   {
      SequenceNode *nodeToAdd = new SequenceNode;
      nodeToAdd->elt = value;
      nodeToAdd->next = head;
      nodeToAdd->prev = nullptr;
      head = nodeToAdd;
   }
   // Any other inserts
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

/// @brief get the front of the sequence -- the first node's value
/// @return the element stored in the head
const Sequence::value_type &Sequence::front() const
{
   if (empty())
      throw exception();
   return head->elt;
}

/// @brief get the back of the sequence -- the last node's value
/// @return the element stored in the tail
const Sequence::value_type &Sequence::back() const
{
   if (empty())
      throw exception();
   return tail->elt;
}

/// @brief checks if the sequence is empty or not
/// @return True if empty, false if it has nodes.
bool Sequence::empty() const
{
   return head == nullptr;
}

/// @brief gets the current size of the sequence
/// @return the number of nodes in the sequence
Sequence::size_type Sequence::size() const
{
   return numElts;
}

/// @brief resets the sequence to an empty state.
void Sequence::clear()
{
   // Straightforward. Uses erase on the entire sequence
   if (empty())
      return;
   erase(0, numElts);
}

/// @brief erases count number of nodes, starting from the index position
/// @param position the position the erasure should start from
/// @param count the number of nodes to erase
void Sequence::erase(size_type position, size_type count)
{
   // This one got messy so I don't want to restructure it and risk messing it up even more
   int currNumElts = numElts;
   // Cases when unable to erase
   if (position + count - 1 > numElts || position < 0 || position > numElts - 1 || count <= 0 || empty())
      throw exception();

   // Keeping track of current position and number of nodes killed.
   int currentPos = 0;
   int numKilled = 0;
   SequenceNode *current = head;
   // Advance current to position
   while (currentPos != position)
   {
      current = current->next;
      currentPos++;
   }
   // saving the previous node in order to re-link its next pointer and adjust the previous of the node we end up with
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
   // Case where every single element was deleted.
   if (position == 0 && count == currNumElts)
   {
      head = nullptr;
      tail = nullptr;
      return;
   }
   // case when we start from 0. gotta fix the head!
   else if (position == 0)
   {
      head = current;
      head->prev = nullptr;
   }
   // case if current is null. meaning we need a new tail
   else if (current == nullptr)
   {
      current = savePrevious;
      current->next = nullptr;
      tail = current;
   }
   // this covers the other cases
   else
   {
      current->prev = savePrevious;
      savePrevious->next = current;
   }

   // final adjustments
   current = head;
   while (current->next)
   {
      current = current->next;
   }
   tail = current;
}
/// @brief Overloaded << operator that allows the sequence to be sent to an ostream
/// @param os the output stream to send the strings to
/// @param s the sequence to be printed
/// @return the output stream - to allow chaining of outputs
ostream &operator<<(ostream &os, Sequence &s)
{
   // Case when s is empty.
   if (s.empty())
   {
      os << "The sequence is empty." << endl;
      return os;
   }
   int currentPos = 0;
   os << "<";
   // Loop on every node and print it.
   while (currentPos < s.size())
   {
      if (currentPos == (s.size() - 1)) // When at last index, end with ]
      {
         os << s[currentPos] << ">" << endl;
         break;
      }
      os << s[currentPos] << ", ";
      currentPos++;
   }
   return os;
}

/// @brief A methood to test connections. If head can reach tail and vice versa. Tests nexts and prevs.
/// @return true if reached head->tail and then tail->head. false if failed somewhere.
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