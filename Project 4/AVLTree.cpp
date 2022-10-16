#include "AVLTree.h"

using namespace std;

AVLTree::AVLTree()
{
   size = 0;
   height = 0;
   root = nullptr;
}

AVLTree::AVLTree(TreeNode *&root)
{
   size = 0;
   height = 0;
   this->root = root;
}
AVLTree::~AVLTree()
{
   // Use postorder here
}

bool AVLTree::insertBST(int key, string value)
{
   TreeNode *nodeToInsert = new TreeNode(key, value);
   if (root == nullptr)
   {
      root = nodeToInsert;
      return true;
   }

   TreeNode *currentNode = root;
   // Currently this is for bst
   while (currentNode != nullptr)
   {
      if (currentNode->key <= key)
      {
         if (currentNode->right == nullptr)
         {

            currentNode->right = nodeToInsert;
            nodeToInsert->parent = currentNode;
            currentNode = nullptr;
         }
         else
            currentNode = currentNode->right;
      }
      else
      {
         if (currentNode->left == nullptr)
         {
            currentNode->left = nodeToInsert;
            nodeToInsert->parent = currentNode;
            currentNode = nullptr;
         }
         else
            currentNode = currentNode->left;
      }
   }
   size++;
}
int AVLTree::getHeight()
{
   return height;
}
int AVLTree::getSize()
{
   return size;
}

bool AVLTree::find(int key, string &value)
{
   TreeNode *currentNode = this->root;
   while (currentNode != nullptr)
   {
      if (currentNode->key == key)
      {
         value = currentNode->value;
         return true;
      }
      if (currentNode->key < key)
      {
         currentNode = currentNode->left;
      }
      if (currentNode->key >= key)
      {
         currentNode = currentNode->right;
      }
   }
   value = key + " not found";
   return false;
}