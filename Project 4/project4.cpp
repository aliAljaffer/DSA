#include "AVLTree.h"
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <time.h>
using namespace std;

void memory();

int main()
{
   AVLTree tree;
   // cout << tree << endl;
   tree.insert(40, "Forty");
   tree.insert(50, "Fifty");
   tree.insert(20, "Twenty");
   tree.insert(10, "Ten");
   tree.insert(45, "Forty Five");
   tree.insert(30, "Thirty");
   vector<string> myVector = tree.findRange(20, 47);
   for (string x : myVector)
   {
      cout << x << ", ";
   }
   cout << endl;
   string v;
   // AVLTree tree2 = tree;
   //  tree.insert(5, "Five");
   //  cout << tree << endl;
   //  cout << tree2 << endl;
   //  tree.find(120, v);
   //  cout << v << endl;
   system("pause");
   memory();
   system("pause");
   // cout << "Wa";
   // AVLTree tree2(tree);
   // cout << tree << endl;
   // cout << "\n\n";
   // cout << tree2 << endl;
   // cout << tree << endl;
   // cout << tree << endl;
   // cout << tree.insert(50, "Fifty");
   // // This should print 0, because it returns false (no duplicates allowed):
   // cout << tree.insert(50, "Another fifty");
   // cout << tree.insert(100, "One hundred");
   // cout << tree.insert(200, "Two hundred") << endl; // single rotate left
   // cout << tree << endl;
   // cout << "hello" << endl;

   // cout << tree.insert(40, "Fourty");
   // cout << tree.insert(30, "Thirty"); // single rotate right
   // cout << tree.insert(150, "One hundred fifty");
   // cout << tree.insert(175, "One hundred seventy-five"); // double rotate right
   // cout << tree.insert(35, "Thirty-five");
   // cout << tree.insert(34, "Thirty-four");       // double rotate left
   // cout << tree.insert(50, "Fifty yet again");   // should be 0
   // cout << tree.insert(34, "Thirty-four again"); // should be 0;
   // cout << tree.insert(200, "Two hundred");      // should be 0;
   // //                                                  // Expect: 1011111111000
   // // cout << "breakpoint" << endl;
   // cout << "\n\n";

   // cout << tree << endl;
   // cout << tree.getSize() << endl;   // 9
   // cout << tree.getHeight() << endl; // 3

   // string result;

   // cout << tree.find(50, result) << endl;    // 1
   // cout << "finding 50: " << result << endl; // Fifty

   // cout << tree.find(40, result) << endl;    // 1
   // cout << "finding 40: " << result << endl; // Fourty

   // cout << tree.find(175, result) << endl;    // 1
   // cout << "finding 175: " << result << endl; // One hundred seventy-five

   // cout << tree.find(600, result) << endl; // 0
   // cout << "finding 600: " << result << endl;
   // vector<string> vec = tree.findRange(30, 200); // all of it
   // for (vector<string>::iterator it = vec.begin(); it != vec.end(); ++it)
   // {
   //    cout << *it << endl;
   // }
   // cout << "\n\n"
   //      << endl;

   // vec = tree.findRange(100, 200); // right subtree
   // for (vector<string>::iterator it = vec.begin(); it != vec.end(); ++it)
   // {
   //    cout << *it << endl;
   // }
   // cout << "\n\n"
   //      << endl;
   // vec = tree.findRange(30, 100); // left subtree
   // for (vector<string>::iterator it = vec.begin(); it != vec.end(); ++it)
   // {
   //    cout << *it << endl;
   // }
   // cout << "\n\n"
   //      << endl;
   // return 0;
}

void memory()
{
   srand(time(NULL));
   AVLTree tree;
   for (int i = 1; i < 10000000; i++)
   {
      tree.insert((rand() % 10), to_string(i));
   }
   cout << tree << endl;
   cout << "Check Mem" << endl;
}