#include <string>
#include <iostream>
#include <exception>
#include <vector>
#pragma once
using namespace std;
/*
 * Ali Aljaffer - CS3100
 *          Project 4 - AVL Tree
 * A map implementation that uses int:string
 * and its functions are implemented according
 * to the given requirements of the provided PDF.
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
   bool insert(int, string);
   bool rebalanceTree(TreeNode *);
   int getHeight();
   int getSize();
   int getBalance(TreeNode *);
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
   bool replaceChild(TreeNode *, TreeNode *, TreeNode *);
   bool setChild(TreeNode *, string, TreeNode *);
};