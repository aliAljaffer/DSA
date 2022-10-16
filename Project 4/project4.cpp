#include "AVLTree.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{

   AVLTree tree;
   tree.insertBST(50, "Fifty");
   // This should print 0, because it returns false (no duplicates allowed):
   tree.insertBST(50, "Another fifty");
   tree.insertBST(100, "One hundred");
   tree.insertBST(200, "Two hundred"); // single rotate left

   // cout << tree << endl;

   // cout << tree.insertBST(40, "Fourty");
   // cout << tree.insertBST(30, "Thirty"); // single rotate right
   // cout << tree.insertBST(150, "One hundred fifty");
   // cout << tree.insertBST(175, "One hundred seventy-five"); // double rotate right
   // cout << tree.insertBST(35, "Thirty-five");
   // cout << tree.insertBST(34, "Thirty-four");       // double rotate left
   // cout << tree.insertBST(50, "Fifty yet again");   // should be 0
   // cout << tree.insertBST(34, "Thirty-four again"); // should be 0;
   // cout << tree.insertBST(200, "Two hundred");      // should be 0;
   //                                                  // Expect: 1011111111000

   // cout << "\n\n";

   // cout << tree << endl;
   // cout << tree.getSize() << endl;   // 9
   // cout << tree.getHeight() << endl; // 3

   // string result;

   // cout << tree.find(50, result) << endl; // 1
   // cout << result << endl;                // Fifty

   // cout << tree.find(40, result) << endl; // 1
   // cout << result << endl;                // Fourty

   // cout << tree.find(175, result) << endl; // 1
   // cout << result << endl;                 // One hundred seventy-five

   // cout << tree.find(600, result) << endl; // 0

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