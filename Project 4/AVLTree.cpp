#include "AVLTree.h"

using namespace std;

AVLTree::AVLTree()
{
   size = 0;
   height = 0;
   root = nullptr;
}

AVLTree::~AVLTree()
{
   bulldozer(root);
}
// If I kill *this* do I still own the memory?
AVLTree::AVLTree(const AVLTree &copyMe)
{
   if (size)
      bulldozer(root);
   size = 0;
   height = 0;
   root = nullptr;
   if (copyMe.size)
      copyHelper(copyMe.root, copyMe);
}
bool AVLTree::insert(int key, string value)
{
   TreeNode *nodeToInsert = new TreeNode(key, value);
   if (root == nullptr)
   {
      root = nodeToInsert;
      size++;
      return 1;
   }
   TreeNode *currentNode = root;
   // Currently this is for bst
   while (currentNode != nullptr)
   {
      if (currentNode->key <= key)
      {
         if (currentNode->key == key)
         {
            // Duplicate key
            return 0;
         }
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

   currentNode = nodeToInsert->parent;
   while (currentNode)
   {
      rebalanceTree(currentNode);
      currentNode = currentNode->parent;
   }
   size++;
   return 1;
}

bool AVLTree::rebalanceTree(TreeNode *node)
{
   updateNodeHeight(node);
   int nodeBalance = getBalance(node);
   // Check if left rotate
   if (nodeBalance == -2)
   {
      // Check if single or double rotate
      int rightNodeBalance = getBalance(node->right);
      if (rightNodeBalance == 1)
      {
         // Case when doulbe rotating to the left: SRR(on node->right), SLR
         SingleRightRotation(node->right);
      }
      // return rotateLeft on node
      SingleLeftRotation(node);
      return 1;
   }
   else if (nodeBalance == 2)
   {
      // If right rotate.
      // Check if double or single
      int leftNodeBalance = getBalance(node->left);
      if (leftNodeBalance == -1)
      {
         // Case when double rotating to the right: SLR(on node->left), SRR
         // Rotate left
         SingleLeftRotation(node->left);
      }
      // return rotateRight
      SingleRightRotation(node);
      return 1;
   }
   return 1;
}
bool AVLTree::insertBST(int key, string value)
{
   if (root == nullptr)
   {
      root = new TreeNode(key, value);
      return 1;
   }

   TreeNode *currentNode = root;
   // Currently this is for bst
   while (currentNode != nullptr)
   {
      if (currentNode->key <= key)
      {
         if (currentNode->key == key)
         {
            // Duplicate key
            return 0;
         }
         if (currentNode->right == nullptr)
         {
            currentNode->right = new TreeNode(key, value);
            currentNode->right->parent = currentNode;
            currentNode = nullptr;
         }
         else
            currentNode = currentNode->right;
      }
      else
      {
         if (currentNode->left == nullptr)
         {
            currentNode->left = new TreeNode(key, value);
            currentNode->left->parent = currentNode;
            currentNode = nullptr;
         }
         else
            currentNode = currentNode->left;
      }
   }
   size++;
}

bool AVLTree::find(int key, string &value)
{
   TreeNode *currentNode = root;
   while (currentNode != nullptr)
   {
      if (currentNode->key == key)
      {
         value = currentNode->value;
         return 1;
      }
      if (currentNode->key > key)
      {
         currentNode = currentNode->left;
      }
      // Check if currentNode is not nullptr, in case previous if changed it
      if (currentNode && currentNode->key < key)
      {
         currentNode = currentNode->right;
      }
   }
   value = to_string(key) + " not found";
   return 0;
}

std::vector<string> AVLTree::findRange(int lowkey, int highkey)
{
   if (lowkey > highkey)
      throw exception();
   vector<string> rangeResults;
   // If tree is null no point in searching
   if (!getSize())
      return rangeResults;
   findRangeHelper(root, lowkey, highkey, rangeResults);
   return rangeResults;
}

void AVLTree::findRangeHelper(TreeNode *node, int lowkey, int highkey, vector<string> &rangeResults)
{
   if (!node)
      return;

   if (node->key > lowkey)
      findRangeHelper(node->left, lowkey, highkey, rangeResults);
   if (node->key >= lowkey && node->key <= highkey)
      rangeResults.push_back(node->value);
   if (node->key < highkey)
      findRangeHelper(node->right, lowkey, highkey, rangeResults);
}

ostream &operator<<(ostream &os, const AVLTree &me)
{
   if (!me.size)
      os << "Tree is empty." << endl;
   return me.inorderPrint(os, me.root, 1);
}

// tree felling function!
void AVLTree::bulldozer(TreeNode *node)
{
   if (!node)
      return;
   bulldozer(node->left);
   bulldozer(node->right);
   delete node;
}
// Ask about this
AVLTree &AVLTree::operator=(const AVLTree &copyMe)
{
   // Remove everything first.
   bulldozer(root);
   copyHelper(copyMe.root, copyMe);
   return *this;
}

void AVLTree::copyHelper(TreeNode *node, const AVLTree &copyMe)
{
   if (!node)
      return;
   if (node == copyMe.root)
      insert(node->key, node->value);
   if (node->left)
      insert(node->left->key, node->left->value);
   if (node->right)
      insert(node->right->key, node->right->value);
   copyHelper(node->left, copyMe);
   copyHelper(node->right, copyMe);
}
ostream &AVLTree::inorderPrint(ostream &os, TreeNode *node, int depth) const
{
   if (!node)
      return os;
   // traverse to right child, visit it, then left
   inorderPrint(os, node->right, depth + 1);
   string spaces = "";
   for (int i = 0; i < depth; i++)
      spaces += "\t";
   os << spaces << to_string(node->key) << ", " << node->value << endl;
   inorderPrint(os, node->left, depth + 1);
   return os;
}
void AVLTree::updateNodeHeight(TreeNode *node)
{
   int leftHeight = -1;
   if (node->left)
   {
      leftHeight = node->left->height;
   }
   int rightHeight = -1;
   if (node->right)
   {
      rightHeight = node->right->height;
   }
   node->height = 1 + max(rightHeight, leftHeight);
   if (node == root)
      height = node->height;
}
int AVLTree::getBalance(TreeNode *node)
{
   int leftHeight = -1;
   if (node->left)
   {
      leftHeight = node->left->height;
   }
   int rightHeight = -1;
   if (node->right)
   {
      rightHeight = node->right->height;
   }
   return leftHeight - rightHeight;
}
bool AVLTree::replaceChild(TreeNode *parent, TreeNode *currentChild, TreeNode *newChild)
{
   if (parent->left == currentChild)
   {
      return setChild(parent, "left", newChild);
   }
   else if (parent->right == currentChild)
   {
      return setChild(parent, "right", newChild);
   }
   return 0;
}

bool AVLTree::setChild(TreeNode *parent, string childToSet, TreeNode *child)
{
   if (childToSet != "left" && childToSet != "right")
      return 0;

   if (childToSet[0] == 'l')
   {
      parent->left = child;
   }
   else
      parent->right = child;

   if (child)
      child->parent = parent;

   updateNodeHeight(parent);
   return 1;
}
AVLTree::TreeNode *AVLTree::SingleRightRotation(TreeNode *node)
{
   TreeNode *leftRightChild = node->left->right;
   if (node->parent)
   {
      replaceChild(node->parent, node, node->left);
   }
   else
   {
      root = node->left;
      root->parent = nullptr;
   }
   setChild(node->left, "right", node);
   setChild(node, "left", leftRightChild);
   return node;
}

AVLTree::TreeNode *AVLTree::SingleLeftRotation(TreeNode *node)
{
   TreeNode *rightLeftChild = node->right->left;
   if (node->parent)
   {
      replaceChild(node->parent, node, node->right);
   }
   else
   {
      root = node->right;
      root->parent = nullptr;
   }
   setChild(node->right, "left", node);
   setChild(node, "right", rightLeftChild);
   return node;
}
int AVLTree::getHeight()
{
   return height;
}
int AVLTree::getSize()
{
   return size;
}