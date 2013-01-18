// Tacuma Solomon
// TreeType(int).h


#include <string>
#include <fstream>
typedef int DataType;
struct TreeNodeint;

class TreeTypeint
{
public:
  TreeTypeint();                     // constructor
 ~TreeTypeint();                    // destructor
 void MakeEmpty();
  TreeTypeint(const TreeTypeint& originalTree); 
  void operator=(const TreeTypeint& originalTree);
  // copy constructor
  bool IsEmpty() const;
  bool IsFull() const;
  bool GetItem(DataType item, bool& found);
  void PutItem(DataType item);
  void DeleteItem(DataType item);

private:
  TreeNodeint* root;
};


struct TreeNodeint
{
  DataType info;
  TreeNodeint* left;
  TreeNodeint* right;
};


bool TreeTypeint::IsFull() const
// Returns true if there is no room for another item 
//  on the free store; false otherwise.
{
  TreeNodeint* location;
  try
  {
    location = new TreeNodeint;
    delete location;
    return false;
  }
  catch(std::bad_alloc exception)
  {
    return true;
  }
}


bool TreeTypeint::IsEmpty() const
// Returns true if the tree is empty; false otherwise.
{
  return root == NULL;
}

void Retrieve(TreeNodeint* tree, 
     DataType& item, bool& found);

bool TreeTypeint::GetItem(DataType item, bool& found)
// Calls recursive function Retrieve to search the tree for item.
{
  Retrieve(root, item, found);
  return found;
}

void Retrieve(TreeNodeint* tree, 
     DataType& item, bool& found)
// Recursively searches tree for item.
// Post: If there is an element someItem whose key matches item's,
//       found is true and item is set to a copy of someItem; 
//       otherwise found is false and item is unchanged.
{
  if (tree == NULL)
    found = false;                     // item is not found.
  else if (item < tree->info)      
    Retrieve(tree->left, item, found); // Search left subtree.
  else if (item > tree->info)
    Retrieve(tree->right, item, found);// Search right subtree.
  else
  {
    item = tree->info;                 // item is found.
    found = true;
   }
} 

void Insert(TreeNodeint*& tree, DataType item);

void TreeTypeint::PutItem(DataType item)
// Calls recursive function Insert to insert item into tree.
{
  Insert(root, item);
}

void Insert(TreeNodeint*& tree, DataType item)
// Inserts item into tree.
// Post:  item is in tree; search property is maintained.
{
  if (tree == NULL)
  {// Insertion place found.
    tree = new TreeNodeint;
    tree->right = NULL;
    tree->left = NULL;
    tree->info = item;
  }
  else if (item < tree->info)
    Insert(tree->left, item);    // Insert in left subtree.
  else
    Insert(tree->right, item);   // Insert in right subtree.
}

void DeleteNode(TreeNodeint*& tree);

void Delete(TreeNodeint*& tree, DataType item);

void TreeTypeint::DeleteItem(DataType item)
// Calls recursive function Delete to delete item from tree.
{
  Delete(root, item);
}

void Delete(TreeNodeint*& tree, DataType item)
// Deletes item from tree.
// Post:  item is not in tree.
{
	if (item < tree->info)
    Delete(tree->left, item);   // Look in left subtree.
	else if (item > tree->info)
    Delete(tree->right, item);  // Look in right subtree.
  else
    DeleteNode(tree);           // Node found; call DeleteNode.
}   

void GetPredecessor(TreeNodeint* tree, DataType& data);

void DeleteNode(TreeNodeint*& tree)
// Deletes the node pointed to by tree.
// Post: The user's data in the node pointed to by tree is no 
//       longer in the tree.  If tree is a leaf node or has only 
//       non-NULL child pointer the node pointed to by tree is 
//       deleted; otherwise, the user's data is replaced by its 
//       logical predecessor and the predecessor's node is deleted.
{
  DataType data;
  TreeNodeint* tempPtr;

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
    GetPredecessor(tree->left, data);
    tree->info = data;
    Delete(tree->left, data);  // Delete predecessor node.
  }
}

void GetPredecessor(TreeNodeint* tree, DataType& data)
// Sets data to the info member of the right-most node in tree.
{
  while (tree->right != NULL)
    tree = tree->right;
  data = tree->info;
}

TreeTypeint::TreeTypeint()
{
  root = NULL;
}

void Destroy(TreeNodeint*& tree);

TreeTypeint::~TreeTypeint()
// Calls recursive function Destroy to destroy the tree.
{
  Destroy(root);
}

void Destroy(TreeNodeint*& tree)
// Post: tree is empty; nodes have been deallocated.
{
  if (tree != NULL)
  {
    Destroy(tree->left);
    Destroy(tree->right);
    delete tree;
  }
}

void CopyTree(TreeNodeint*& copy, 
     const TreeNodeint* originalTree);

TreeTypeint::TreeTypeint(const TreeTypeint& originalTree)
// Calls recursive function CopyTree to copy originalTree 
//  into root.
{
  CopyTree(root, originalTree.root);
}

void TreeTypeint::operator= 
     (const TreeTypeint& originalTree)
// Calls recursive function CopyTree to copy originalTree 
// into root.
{
  {
  if (&originalTree == this)
    return;             // Ignore assigning self to self
  Destroy(root);      // Deallocate existing tree nodes
  CopyTree(root, originalTree.root);
  }

}

void CopyTree(TreeNodeint*& copy, 
     const TreeNodeint* originalTree)
// Post: copy is the root of a tree that is a duplicate 
//       of originalTree.
{
  if (originalTree == NULL)
    copy = NULL;
  else
  {
    copy = new TreeNodeint;
    copy->info = originalTree->info;
    CopyTree(copy->left, originalTree->left);
    CopyTree(copy->right, originalTree->right);
  }
}

void TreeTypeint::MakeEmpty()
{
  Destroy(root);
  root = NULL;
}
