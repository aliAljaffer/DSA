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
   AVLTree(TreeNode *&);
   ~AVLTree();
   // TreeNode *search(int);
   //  bool insertAVL(int key, string value);
   bool insertBST(int key, string value);
   // bool rebalance(TreeNode *&);
   int getHeight();
   int getSize();
   // friend ostream &operator<<(ostream &os, const AVLTree &me);
   bool find(int key, string &value);
   // std::vector<string> findRange(int lowkey, int highkey);
   // AVLTree &operator=(const AVLTree &);
   // TreeNode *SingleRightRotation(TreeNode *);
   // TreeNode *SingleLeftRotation(TreeNode *);
   // TreeNode *DoubleRightRotation(TreeNode *);
   // TreeNode *DoubleLeftRotation(TreeNode *);
};