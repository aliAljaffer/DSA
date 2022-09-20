#include "sequence.h"
#include <iostream>
#include <string>

int main()
{
   Sequence mySequence(7);
   mySequence.insert(3, 100);
   mySequence.insert(5, 200);
   mySequence.push_back(50);
   // mySequence.clear();
   // mySequence.traverser();
   // cout << mySequence << endl;
   // mySequence.pop_back();
   mySequence.push_back(5);
   cout << mySequence << endl;

   Sequence secondSequence;
   secondSequence = mySequence;
   cout << secondSequence << endl;
}