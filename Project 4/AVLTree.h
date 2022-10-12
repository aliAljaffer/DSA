#include <string>
#include <iostream>
#include <exception>
#pragma once
#include <vector>
using namespace std;

class AVLTree
{
private:
   class TreeNode
   {
   public:
      TreeNode *left;
      TreeNode *right;
      string value;
      int key;
      int height;

      TreeNode()
      {
         left = nullptr;
         right = nullptr;
         value = "";
         height = 0;
      }
      TreeNode(string &value)
      {
         left = nullptr;
         right = nullptr;
         this->value = value;
         height = 0;
      }
      TreeNode(TreeNode *left, TreeNode *right)
      {
         this->right = right;
         this->left = left;
         value = "";
         height = 0;
      }

      TreeNode(int key, string value)
      {
         left = nullptr;
         right = nullptr;
         this->key = key;
         this->value = value;
         height = 0;
      }
      ~TreeNode()
      {
      }
   };

   int size;
   int height;
   TreeNode *root;

public:
   AVLTree();
   AVLTree(TreeNode *);
   ~AVLTree();
   TreeNode *search(int);
   bool insert(int key, string value);
   int getHeight();
   int getSize();
   friend ostream &operator<<(ostream &os, const AVLTree &me);
   bool find(int key, string &value);
   std::vector<string> findRange(int lowkey, int highkey);
   AVLTree &operator=(const AVLTree &);
   TreeNode *SingleRightRotation(TreeNode *);
   TreeNode *SingleLeftRotation(TreeNode *);
   TreeNode *DoubleRightRotation(TreeNode *);
   TreeNode *DoubleLeftRotation(TreeNode *);
};