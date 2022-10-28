#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "Trie.h"

int main()
{
   Trie tr;
   tr.insert("hello");
   tr.insert("hea");
   tr.insert("here");
   tr.insert("heal");
   tr.insert("fine");
   vector<string> result;
   tr.autocomplete("1", result);
   for (auto x : result)
   {
      cout << x << endl;
   }
}