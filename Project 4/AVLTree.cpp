#include "AVLTree.h"

using namespace std;

AVLTree::AVLTree()
{
   size = 0;
   height = 0;
   root = nullptr;
}

AVLTree::AVLTree(TreeNode *root)
{
   size = 0;
   height = 0;
   this->root = root;
}
AVLTree::~AVLTree()
{
   // Use postorder here
}
bool AVLTree::insert(int key, string value)
{
   TreeNode *nodeToInsert = new TreeNode(key, value);
   if (root == nullptr)
      root = nodeToInsert;
   TreeNode *currentNode = root;
   // Currently this is for bst
   while (currentNode != nullptr)
   {
      if (currentNode->key <= key)
      {
         if (currentNode->right == nullptr)
         {

            currentNode->right = nodeToInsert;

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
ostream &operator<<(ostream &os, const AVLTree &me)
{
}
AVLTree &AVLTree::operator=(const AVLTree &)
{
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

AVLTree::TreeNode *AVLTree::search(int key)
{

   return nullptr;
}
vector<string> AVLTree::findRange(int lowkey, int highkey)
{
}

AVLTree::TreeNode *AVLTree::SingleRightRotation(TreeNode *problemNode)
{
}
AVLTree::TreeNode *AVLTree::SingleLeftRotation(TreeNode *problemNode)
{
}
AVLTree::TreeNode *AVLTree::DoubleRightRotation(TreeNode *problemNode)
{
}
AVLTree::TreeNode *AVLTree::DoubleLeftRotation(TreeNode *problemNode)
{
}