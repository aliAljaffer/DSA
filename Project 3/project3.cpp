#include "sequence.h"
#include <iostream>
#include <string>

int main()
{
   Sequence mySequence(10);
   mySequence.insert(3, 100);
   mySequence.insert(5, 200);
   mySequence.push_back(50);
   // mySequence.traverser();
   //  cout << mySequence << endl;
}