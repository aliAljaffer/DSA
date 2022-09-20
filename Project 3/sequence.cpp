#include "Sequence.h"

Sequence::Sequence(size_type sz)
{
   this->tail = nullptr;
   this->numElts = 0;
   SequenceNode *newSqNode = new SequenceNode;
   newSqNode->elt = 0;
   this->head = newSqNode;
   SequenceNode *current = head;
   while (this->numElts < sz && sz > 0)
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
      previous->next = nodeToAdd;
      previous = nodeToAdd;
      copyNode = copyNode->next;
   }
   previous->next = nullptr;
   tail = previous->next;
}

Sequence::~Sequence()
{
   // this->erase(0, numElts); ?
   SequenceNode *current = head;
   SequenceNode *killNext;
   while (current)
   {
      killNext = current->next;
      delete current;
      current = killNext;
   }
}

Sequence &Sequence::operator=(const Sequence &s)
{
}

Sequence::value_type &Sequence::operator[](size_type position)
{
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
   newSqNode->prev = tail->prev;
   newSqNode->next = nullptr;
   tail = newSqNode;
   numElts++;
}

void Sequence::pop_back()
{
   SequenceNode *tailPtr = tail;
   tail = tail->prev;
   numElts--;
   delete tailPtr;
}

void Sequence::insert(size_type position, value_type value)
{
   if (position < 0 || position > numElts - 1)
   {
      // throw exception
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
      numElts++;
   }
}

const Sequence::value_type &Sequence::front() const
{
   return head->elt;
}

const Sequence::value_type &Sequence::back() const
{
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
   // Assuming clear means all values 0
   SequenceNode *current = head;
   while (current)
   {
      current->elt = 0;
      current = current->next;
   }
}

void Sequence::erase(size_type position, size_type count)
{
   if (position + count > numElts || position < 0 || position > numElts - 1 || count <= 0)
   {
      // throw exception
   }
   else
   {
      int currentPos = 0;
      int numKilled = 0;
      SequenceNode *current = head;
      while (currentPos != position)
      {
         current = current->next;
         currentPos++;
      }
      SequenceNode *savePrevious = current->prev;
      SequenceNode *nextToKill;
      while (numKilled != count)
      {
         nextToKill = current->next;
         delete current;
         numElts--;
         current = nextToKill;
         numKilled++;
      }
      current->prev = savePrevious;
      savePrevious->next = current;
      current = head;
      while (current)
      {
         current = current->next;
      }
      tail = current;
   }
}
ostream &operator<<(ostream &os, Sequence &s)
{
}