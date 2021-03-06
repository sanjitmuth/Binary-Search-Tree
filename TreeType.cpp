#include "TreeType.h"

struct TreeNode
{
  ItemType info;
  TreeNode *left;
  TreeNode *right;
};

TreeType::TreeType()
{
  root = NULL;
  length = 0;
}

TreeType::~TreeType()
// Calls recursive function destroy to destroy the tree.
{
  destroy(root);
}

void TreeType::makeEmpty()
{
  destroy(root);
  root = NULL;
  length = 0;
}

void TreeType::destroy(TreeNode *&tree)
// Post: tree is empty; nodes have been deallocated.
{
  if (tree != NULL)
  {
    destroy(tree->left);
    destroy(tree->right);
    delete tree;
  }
}

bool TreeType::isEmpty() const
// Returns true if the tree is empty; false otherwise.
{
  return root == NULL;
}

int TreeType::getLength() const
{
  return length;
}

void TreeType::putItem(ItemType item)
// Calls recursive function insert to insert item into tree.
{
  insert(root, item);
  length++;
}

// helper Function for putItem
void TreeType::insert(TreeNode *&tree, ItemType item)
// inserts item into tree.
// Post:  item is in tree; binary search property is maintained.
{
  if (tree == NULL)
  { // insertion place found.
    tree = new TreeNode;
    tree->left = NULL;
    tree->right = NULL;
    tree->info = item;
  }
  else if (item < tree->info)
    insert(tree->left, item); // insert in left subtree.
  else
    insert(tree->right, item); // insert in right subtree.
}

void TreeType::deleteItem(ItemType item, ofstream &outFile)
// Calls recursive function remove to delete item from tree.
{
  remove(root, item, outFile);
  length--;
}

void TreeType::remove(TreeNode *&tree, ItemType item, ofstream &outFile)
// Deletes item from tree.
// Post:  item is not in tree.
{
  if (tree == NULL) {
    outFile << item << " is not in tree." << endl;
    length++;	// if item not found, then this length++ offsets the length-- in deleteItem()
  }
  else if (item < tree->info)
    remove(tree->left, item, outFile); // Look in left subtree.
  else if (item > tree->info)
    remove(tree->right, item, outFile); // Look in right subtree.
  else
    deleteNode(tree, outFile); // Node found; call deleteNode
}
/*
 * Uses a pointer to the address of tree and the address of outFile
 * Returns nothing
 * Pre: Tree is intialized
 * Post: Item is removed from the BST
 */
void TreeType::deleteNode(TreeNode *&tree, ofstream &outFile)
// Modify this function to call the getSuccessor function instead of getPredecessor
{
  TreeNode *tempPtr;
  tempPtr = tree;

  if (tree->left == NULL)
  {
    tree = tree->right;
    delete tempPtr;
  }
  else if (tree->right == NULL)
  {
    tree = tree->left;
    delete tempPtr;
  }
  else
  {
    TreeNode *predNode = getSuccessor(tree);
    tree->info = predNode->info;
    remove(tree->left, predNode->info, outFile); // Delete predecessor node.
  }
}

//Helper function for deleteNode
TreeNode *TreeType::getPredecessor(TreeNode *tree) const
{
  while (tree->right != NULL)
    tree = tree->right;
  return tree;
}
/*
 *Helper method for deleteNode
 *Uses a pointer to the tree
 *Returns a pointer to the TreeNode with the smallest value in the BST
 *Pre: Tree is initialized
 *Post: Tree remains unchanged
 */
TreeNode *TreeType::getSuccessor(TreeNode *tree) const {
  TreeNode *curr = tree;

  //getting to the left-most node
  while (curr->left != nullptr) {
    curr = curr->left;
  }
  return curr;
} //getSuccessor

void TreeType::print(ofstream &outFile) const
// Calls recursive function inOrderTraverse to print items in the tree.
{
  inOrderTraverse(root, outFile);
  outFile << endl;
}

// Helper function for print
void TreeType::inOrderTraverse(TreeNode *tree, ofstream &outFile) const
// Prints info member of items in tree in sorted order on screen.
{
  if (tree != NULL)
  {
    inOrderTraverse(tree->left, outFile); // Print left subtree.
    outFile << tree->info << " ";
    inOrderTraverse(tree->right, outFile); // Print right subtree.
  }
}

/* preOrderPrint helper
 *Uses a pointer to tree and the address of outFile
 *Returns nothing, but adds the BST printed out in pre-order to the outFile
 *Pre: Tree is initialized
 *Post: BST remains unchanged
 */
void TreeType::preOrder(TreeNode *tree, ofstream &outFile) const {
  if (tree != nullptr) {
    outFile << tree->info << " ";
    preOrder(tree->left, outFile);
    preOrder(tree->right, outFile);
  }
} //preOrder

/*
 *Uses the address to outFile
 *Calls the method preOrder to actually traverse and print
 *Pre: outFile exists
 *Post: BST is printed to outFile
 */
void TreeType::preOrderPrint(ofstream &outFile) const {
  preOrder(root, outFile);
  outFile << endl;
} //preOrderPrint

/*                                                                                                                                                     
 *Uses the address to outFile                                                                                                                          
 *Calls the method postOrder to actually traverse and print                                                                                            
 *Pre: outFile exists                                                                                                                                  
 *Post: BST is printed to outFile                                                                                                                      
 */    
void TreeType::postOrder(TreeNode *tree, ofstream &outFile) const {
  if (tree != nullptr) {
    postOrder(tree->left, outFile);
    postOrder(tree->right, outFile);
    outFile << tree->info << " ";
  }
}//postOrder

/* 
 *Uses a pointer to tree and the address of outFile                                                                                                                                                                                                                                                              
 *Returns nothing, but adds the BST printed out in post-order to the outFile                                                                                                                                                                                                                                     
 *Pre: Tree is initialized                                                                                                                                                                                                                                                                                       
 *Post: BST remains unchanged                                                                                                                                                                                                                                                                                    
 */
void TreeType::postOrderPrint(ofstream &outFile) const {
  postOrder(root, outFile);
  outFile << endl;
} //postOrderPrint

//Level Order Helpers-----------------------------
/* 
 *Uses a pointer to the tree
 *Returns an int, which is the height of the BST
 *Pre: Tree is initialized
 *Post: BST remains unchanged
 */
int TreeType::height(TreeNode *tree) const {
  if (tree == nullptr) {
    return 0;
  } else {
    //compting height of each subtree
    int leftHeight = height(tree->left);
    int rightHeight = height(tree->right);
    //using the larger height
    if (leftHeight > rightHeight) {
      return (leftHeight + 1);
    } else {
      return (rightHeight + 1);
    }
  }
} //height

/*
 *Uses a pointer to a tree, an int which represents a given level in the BST
 *and the address to the outFile.
 *Returns nothing, but prints the nodes on each specified level
 *Pre: tree is initialized, level is an int, outFile exists
 *Post: BST remains unchanged
 */
void TreeType::printThisLevel(TreeNode *tree, int level, ofstream &outFile) const {
  if (tree == nullptr) {
    return;
  }
  if (level == 1) {
    outFile << tree->info << " ";
  } else if (level > 1) {
    printThisLevel(tree->left, level - 1, outFile);
    printThisLevel(tree->right, level - 1, outFile);
  }
} //printThisLevel
//------------------------------------------------
/*
 *Uses the address to the outFile
 *Returns nothing, but prints the BST in level order, from top to bottom
 *Pre: outFile exists
 *Post: BST remains unchanged
 */
void TreeType::levelOrderPrint(ofstream &outFile) const {
  int h = height(root);
  for (int i = 1; i <= h; i++) {
    printThisLevel(root, i, outFile);
  }
  outFile << endl;
} //levelOrderPrint

/*
 *getAncestors helper method
 *Uses a pointer to tree and an ItemType item.
 *Returns a bool, if the the item exists in the BST: return true
 *If the item doesn't exist in the BST: return false
 *Pre: Tree is initialized
 *Post: BST remains unchanged
 */
bool TreeType::search(TreeNode *tree, ItemType item) const {
  while (tree != nullptr) {
    if (item > tree->info) {
      tree = tree->right;
    } else if (item < tree->info) {
      tree = tree->left;
    } else {
      return true;
    }
  } //while
  //tree is nullptr and item wasn't found
  return false;
} //search

/*
 *Uses a specified value of type ItemType and the address of the outFile
 *Returns nothing, but prints all the ancestors of a given value
 *Pre: Tree is initialized and outFile exists
 *Post: BST remains unchanged and ancestors are printed to the outFile
 */
void TreeType::printAncestors(ItemType value, ofstream &outFile) const {
  if (search(root, value) == false) {
    outFile << value << " is not in the tree." << endl;
  } else {
    TreeNode *curr = root;
    //if value is the root
    if (curr->info == value) {
      outFile << curr->info << " has no ancestors." << endl;
    } else {
      while (curr->info != value) {
	if (value > curr->info) {
	  outFile << curr->info << " ";
	  curr = curr->right;
	}
	if (value < curr->info) {
	  outFile << curr->info << " ";
	  curr = curr->left;
	}
      }
      outFile << "" << endl;
    }
  }
}

void TreeType::mirrorImage(TreeType &t) const
// calls the helper function mirror
{
  mirror(t.root, root);
}

// helper function for mirrorImage
/*
 *Uses a pointer to the address of a variable named copy of type TreeNode
 * and a pointer to a TreeNode variable called originalTree
 *Returns nothing, but creates a mirror copy of a given BST
 *Pre: originalTree is initialized
 *Post: a mirror image is produced
 */
void TreeType::mirror(TreeNode *&copy, const TreeNode *originalTree) const {
  if (originalTree == nullptr) {
    copy = nullptr;
  } else {
    copy = new TreeNode;
    copy->info = originalTree->info;
    mirror(copy->left, originalTree->right);
    mirror(copy->right, originalTree->left);
  }
} //mirror


