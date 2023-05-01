#include "AVLTree.h"
using namespace std;
/*
 * Ali Aljaffer - CS3100
 *          Project 4 - AVL Tree
 * A map implementation that uses int:string
 * and its functions are implemented according
 * to the given requirements of the provided PDF.
 */
/// @brief No args constructor
AVLTree::AVLTree()
{
   size = 0;
   height = 0;
   root = nullptr;
}

/// @brief Tree destructor - uses the helper bulldozer() function
AVLTree::~AVLTree()
{
   bulldozer(root);
}

/// @brief Copy constructor for the tree
/// @param copyMe
AVLTree::AVLTree(const AVLTree &copyMe)
{
   // reset everything and then copy
   size = 0;
   height = 0;
   root = nullptr;
   if (copyMe.size)
      copyHelper(copyMe.root, copyMe);
}
/// @brief Inserts a new node with the given key integer and the given value string
/// @param key the key to insert
/// @param value the value associated with the key
/// @return 1 on successful insertion, 0 on failure(duplicate key)
bool AVLTree::insert(int key, string value)
{
   TreeNode *nodeToInsert = new TreeNode(key, value);
   if (root == nullptr)
   {
      // Case when inserting the first node on an empty tree
      root = nodeToInsert;
      size++;
      return 1;
   }
   TreeNode *currentNode = root;

   while (currentNode != nullptr)
   {
      if (currentNode->key <= key)
      {
         if (currentNode->key == key)
         {
            // reject duplicate key, delete the unused node
            delete nodeToInsert;
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
   // start node balancing from parent and going up to root
   currentNode = nodeToInsert->parent;
   while (currentNode)
   {
      rebalanceTree(currentNode);
      currentNode = currentNode->parent;
   }
   size++;
   return 1;
}

/// @brief This function is responsible for keeping the tree balanced and calling the rotations when needed.
/// @param node the node to balance
/// @return 1 on successful balance. Currently no 0 returns.
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
         // Case when double rotating to the left: SRR(on node->right), SLR
         SingleRightRotation(node->right);
      }
      // rotateLeft on node
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
      // rotateRight
      SingleRightRotation(node);
      return 1;
   }
   return 1;
}

/// @brief searches for the given key in the tree and if found, stores the node's value inside of the given string
/// @param key the key to find
/// @param value reference to a string that will be changed
/// @return 1 if the tree has the key, 0 if the key is not present in the tree
bool AVLTree::find(int key, string &value)
{
   TreeNode *currentNode = root;
   while (currentNode != nullptr)
   {
      if (currentNode->key == key)
      {
         // Found!
         value = currentNode->value;
         return 1;
      }
      if (currentNode->key > key)
      {
         currentNode = currentNode->left;
      }
      // Check if currentNode is not nullptr, in case previous ifs changed it
      if (currentNode && currentNode->key < key)
      {
         currentNode = currentNode->right;
      }
   }
   // Loop finished without returning => not found
   value = to_string(key) + " not found";
   return 0;
}

/// @brief Finds all the nodes that have a key higher than the lowkey and lower than the highkey
/// @param lowkey the lower limit for the search
/// @param highkey the upper limit for the search
/// @return vector containing the results of the search
std::vector<string> AVLTree::findRange(int lowkey, int highkey)
{
   if (lowkey > highkey)
      throw exception();
   vector<string> rangeResults;
   // If tree is null no point in searching
   if (!getSize())
      return rangeResults;
   if (lowkey == highkey)
   {
      // If lowkey = highkey, it's not a range anymore, so just use find.
      string value;
      find(lowkey, value);
      rangeResults.push_back(value);
      return rangeResults;
   }
   findRangeHelper(root, lowkey, highkey, rangeResults);
   return rangeResults;
}

/// @brief Helper for the findRange function
/// @param node used to traverse the tree
/// @param lowkey the lower limit for the search
/// @param highkey the upper limit for the search
/// @param rangeResults a reference to the results vector
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

/// @brief Overridden << operator which allows chaining trees to output streams
/// @param os the output stream
/// @param me the tree that called the <<
/// @return the output stream resulting from the call to inorderPrint
ostream &operator<<(ostream &os, const AVLTree &me)
{
   if (!me.size)
      os << "Tree is empty." << endl;
   return me.inorderPrint(os, me.root, 1);
}

/// @brief the deconstructor helper method - uses postorder to delete every node below the root, and finally deletes the root
/// @param node the node where the deletion should start - the tree's root
void AVLTree::bulldozer(TreeNode *node)
{
   if (!node)
      return;
   bulldozer(node->left);
   bulldozer(node->right);
   delete node;
}

/// @brief overridden equals operator which allows tree assignments to other trees
/// @param copyMe the tree to copy
/// @return a pointer to the copied tree
AVLTree &AVLTree::operator=(const AVLTree &copyMe)
{
   // Remove everything first.
   if (size)
      bulldozer(root);
   size = 0;
   height = 0;
   root = nullptr;
   if (copyMe.size)
      copyHelper(copyMe.root, copyMe);
   return *this;
}

/// @brief tree copy helper method that keeps the same shape as the original tree
/// @param node the starting node, usually root
/// @param copyMe the tree to copy from
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
/// @brief Helper method that uses inorder to print right-> current -> left
/// @param os the output stream
/// @param node the node to start from
/// @param depth the depth of the current node
/// @return reference to the output stream
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
/// @brief A function that updates the high of the given node
/// @param node the node to update the height for
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
/// @brief calculates the balance of the given node according to the formula: leftChildHeight - rightChildHeight
/// @param node the node to get the balance for
/// @return the node's balance, -2 <= balance <= 2
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
/// @brief Replaces the child of the given parent with a new one
/// @param parent the parent to add the child to
/// @param currentChild the child currently attached to the parent
/// @param newChild the new child to assign to the parent
/// @return the result of calling the setChild method
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

/// @brief sets the a child to a parent according to childToSet <left or right>
/// @param parent the parent to set the child to
/// @param childToSet the direction to add the child to <left or right>
/// @param child the child to attach the parent
/// @return 1 if successfully sets, 0 if unsuccessful
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

/// @brief Rotate right on the node given
/// @param node the node to rotate on
/// @return the node that was just rotated
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
/// @brief Rotate left on the node given
/// @param node the node to rotate on
/// @return the node that was just rotated
AVLTree::TreeNode *AVLTree::SingleLeftRotation(TreeNode *node)
{
   // Save the right left child in order to use it later after rotating
   TreeNode *rightLeftChild = node->right->left;
   if (node->parent)
   {
      // If the node has a parent, replace its current child(this node) with the right child of the node
      replaceChild(node->parent, node, node->right);
   }
   else
   {
      // If it doesn't have a parent, then it's a rotation at the root
      root = node->right;
      root->parent = nullptr;
   }
   setChild(node->right, "left", node);
   setChild(node, "right", rightLeftChild);
   return node;
}
/// @brief gets the height
/// @return the tree height - O(1)
int AVLTree::getHeight()
{
   return height;
}
/// @brief gets the size - number of elements in the tree
/// @return the height size - O(1)
int AVLTree::getSize()
{
   return size;
}