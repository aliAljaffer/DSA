#include <string>
#include <iostream>
#include <exception>
#pragma once
#include <vector>
using namespace std;
/*
Write rebalance
write findBalance method

*/
class AVLTree
{
private:
   class TreeNode
   {
   public:
      TreeNode *left = nullptr;
      TreeNode *right = nullptr;
      TreeNode *parent = nullptr;
      string value;
      int key;
      int height = 0;

      TreeNode()
      {
         value = "";
      }
      TreeNode(string &value)
      {
         this->value = value;
      }
      TreeNode(TreeNode *left, TreeNode *right)
      {
         this->right = right;
         this->left = left;
         value = "";
      }

      TreeNode(int key, string value)
      {
         this->key = key;
         this->value = value;
      }
      ~TreeNode()
      {
      }
   };

   int size = 0;
   int height;
   TreeNode *root;

public:
   AVLTree();
   ~AVLTree();
   AVLTree(const AVLTree &);
   // TreeNode *search(int);
   bool insert(int, string);
   bool insertBST(int, string);
   bool rebalanceTree(TreeNode *);
   int getHeight();
   int getSize();
   friend ostream &operator<<(ostream &, const AVLTree &);
   bool find(int, string &);
   ostream &inorderPrint(ostream &, TreeNode *, int) const;
   std::vector<string> findRange(int, int);
   void findRangeHelper(TreeNode *, int, int, vector<string> &);
   AVLTree &operator=(const AVLTree &);
   void copyHelper(TreeNode *, const AVLTree &);
   TreeNode *SingleRightRotation(TreeNode *);
   TreeNode *SingleLeftRotation(TreeNode *);
   void bulldozer(TreeNode *);
   void updateNodeHeight(TreeNode *);
   int getBalance(TreeNode *);
   bool replaceChild(TreeNode *, TreeNode *, TreeNode *);
   bool setChild(TreeNode *, string, TreeNode *);
};