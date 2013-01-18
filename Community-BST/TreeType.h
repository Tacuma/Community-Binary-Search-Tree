// Tacuma Solomon
// TreeType.h

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

typedef Person ItemType;
struct TreeNode;

struct counter{
	int SSN;
	int count;
};


class TreeType
{
public:
  TreeType();                     // constructor
 ~TreeType();                    // destructor
  TreeType(const TreeType& originalTree); 
  void operator=(const TreeType& originalTree);
  // copy constructor
  bool IsEmpty() const;
  bool IsFull() const;
  void gethalfSiblings(ItemType person);
  void getfullSiblings(ItemType person);
  ItemType getPerson(int item, bool& found);
  void PutItem(ItemType item);
  void DeleteItem(int item);
  void getChildren(ItemType person);
  void getInverseFriend(ItemType person);
  void getMutualFriend(ItemType person);
  int countMutualFriends(ItemType person);
  void mostMutualFriends();
  void mMutualFriends(counter& mostFriends, TreeNode* tree); // Auxiliary Function to most mutual friends

protected:
  TreeNode* root;
};


struct TreeNode
{
  ItemType info;
  TreeNode* left;
  TreeNode* right;
};


bool TreeType::IsFull() const
// Returns true if there is no room for another item 
//  on the free store; false otherwise.
{
  TreeNode* location;
  try
  {
    location = new TreeNode;
    delete location;
    return false;
  }
  catch(std::bad_alloc exception)
  {
    return true;
  }
}


bool TreeType::IsEmpty() const
// Returns true if the tree is empty; false otherwise.
{
  return root == NULL;
}

// Recursive function for gethalfSiblings
void retrievehalfSiblings(TreeNode* tree, ItemType& person, vector<string>& names);

// Traverses Binary Tree and Prints half siblings for person object
void TreeType::gethalfSiblings(Person person) 
{
// Calls recursive function Retrieve to search the tree for item.
	vector<string> names;
	retrievehalfSiblings(root,person,names);
	// Prints out the names
	if (names.empty())
		cout << "UNAVAILABLE";
	else  {
		for (int i=0;i<(names.size()-1);i++)
			cout << names[i] << ", ";
		cout << names[names.size()-1];
	}
}
// Recursive helper function
void retrievehalfSiblings(TreeNode* tree, ItemType& person,vector<string>& names)
{
	if (tree != NULL)
	{
	retrievehalfSiblings(tree->left,person,names);
	if (((person.getMotherSSN() == tree->info.getMotherSSN()) 
		|| ( person.getFatherSSN() == tree->info.getFatherSSN())) && (person.getSSN() != tree->info.getSSN()))
		names.push_back(tree->info.getFullName());
	retrievehalfSiblings(tree->right,person,names);
	}
}




// Recursive function for getfullSiblings
void retrievefullSiblings(TreeNode* tree, ItemType& person, vector<string>& names);

// Traverses Binary Tree and Prints full siblings for person object
void TreeType::getfullSiblings(Person person) 
{
	vector<string> names;
	retrievefullSiblings(root,person,names);
	// Prints out the names
	if (names.empty())
		cout << "UNAVAILABLE";
	else  {
		for (int i=0;i<(names.size()-1);i++)
			cout << names[i] << ", ";
		cout << names[names.size()-1];
	}
}

// Recursive function for getfullSiblings
void retrievefullSiblings(TreeNode* tree, ItemType& person, vector<string>& names)
{
	if (tree != NULL)
	{
	retrievefullSiblings(tree->left,person,names);
	if (((person.getMotherSSN() == tree->info.getMotherSSN()) 
		&& ( person.getFatherSSN() == tree->info.getFatherSSN())) && (person.getSSN() != tree->info.getSSN()))
		names.push_back(tree->info.getFullName());
	retrievefullSiblings(tree->right,person,names);
	}
}



// Recursive function for retrieveChildren
void retrieveChildren(TreeNode* tree, ItemType& person, vector<string>& names);

// Traverses Binary Tree and Prints the names of the children of person object
void TreeType::getChildren(Person person) 
{
	vector<string> names;
	retrieveChildren(root,person,names);
	// Prints out the names
	if (names.empty())
		cout << "UNAVAILABLE";
	else  {
		for (int i=0;i<(names.size()-1);i++)
			cout << names[i] << ", ";
		cout << names[names.size()-1];
	}
}

// Recursive function for gethalfSiblings
void retrieveChildren(TreeNode* tree, ItemType& person, vector<string>& names)
{
	if (tree != NULL)
	{
	retrieveChildren(tree->left,person,names);
	if (((person.getSSN() == tree->info.getMotherSSN()) 
		|| ( person.getSSN() == tree->info.getFatherSSN())) && (person.getSSN() != tree->info.getSSN()))
		names.push_back(tree->info.getFullName());
	retrieveChildren(tree->right,person,names);
	}
}



// Recursive function for getInverseFriend
void retrieveInverseFriend(TreeNode* tree, ItemType& person, vector<string>& names);

// Traverses Binary Tree and Prints the names of the object's inverse friends
void TreeType::getInverseFriend(Person person) 
{
	vector<string> names;
	retrieveInverseFriend(root,person,names);
	// Prints out the names
	if (names.empty())
		cout << "UNAVAILABLE";
	else  {
		for (int i=0;i<(names.size()-1);i++)
			cout << names[i] << ", ";
		cout << names[names.size()-1];
	}
}

// Recursive function for getInverseFriend
void retrieveInverseFriend(TreeNode* tree, ItemType& person, vector<string>& names)
{
	if (tree != NULL)
	{
	retrieveInverseFriend(tree->left,person,names);
	if (tree->info.isYourFriend(person.getSSN()))
		names.push_back(tree->info.getFullName());
	retrieveInverseFriend(tree->right,person,names);
	}
}



// Recursive function for getMutualFriend
void retrieveMutualFriend(TreeNode* tree, ItemType& person, vector<string>& names);

// Traverses Binary Tree and Prints the mutual friends for person object
void TreeType::getMutualFriend(ItemType person) 
{
	vector<string> names;
	retrieveMutualFriend(root,person,names);
	// Prints out the names
	if (names.empty())
		cout << "UNAVAILABLE";
	else  {
		for (int i=0;i<(names.size()-1);i++)
			cout << names[i] << ", ";
		cout << names[names.size()-1];
	}
}

// Recursive function for getMutualFriend
void retrieveMutualFriend(TreeNode* tree, ItemType& person, vector<string>& names)
{
	if (tree != NULL)
	{
	retrieveMutualFriend(tree->left,person,names);
	if ((person.isYourFriend(tree->info.getSSN())) && (tree->info.isYourFriend(person.getSSN())))
		names.push_back(tree->info.getFullName());
	retrieveMutualFriend(tree->right,person,names);
	}
}



// Recursive function for countMutualFriends
void cMutualFriends(TreeNode* tree, ItemType person, int& count);

// Traverses Binary Tree and counts the mutual friends for person object
// Returns the number of mutual friends for each node
int TreeType::countMutualFriends(ItemType person) 
{
	int count=0;
	cMutualFriends(root,person,count);
	return count;
}

// Recursive function for countMutualFriends
void cMutualFriends(TreeNode* tree, ItemType person, int& count)
{
	if (tree != NULL)
	{
	cMutualFriends(tree->left,person,count);
	if ((person.isYourFriend(tree->info.getSSN())) && (tree->info.isYourFriend(person.getSSN())))
			count++;
	cMutualFriends(tree->right,person,count);
	}
}



// Traverses Binary Tree and counts the mutual friends for person object
void TreeType::mostMutualFriends() 
{
	bool found = false;
	counter mostFriends = {0,0};
	mMutualFriends(mostFriends,root); //Assigns the SSN and count of the person with the most Mutual friends
	ItemType person = getPerson(mostFriends.SSN, found); // Return the person information of ths SSN number
	cout << person.getFullName() << endl;  // Output the person's name
}

// Recursive function for getMutualFriend
// AUXILIARY FUNCTION to most mutual friends
void TreeType::mMutualFriends(counter& mostFriends, TreeNode* tree)
{
	if (tree != NULL)
	{
		mMutualFriends(mostFriends, tree->left); //left node
		int count = this->countMutualFriends(tree->info); // Returns the number of mutual friends
		if (count > mostFriends.count)			// If the count of this node is greater than the present count,
		{
			mostFriends.count = count;		    // Assign the count number to the struct
			mostFriends.SSN = tree->info.getSSN();  // Assign the SSN number
		}
		mMutualFriends(mostFriends, tree->right); //right node
	}
}


// Recursive function for getPerson
void Retrieve(TreeNode* tree, 
     int& item, bool& found, ItemType& person);

// Traverses Binary Tree and returns a Person object
ItemType TreeType::getPerson(int item, bool& found)
// Calls recursive function Retrieve to search the tree for item.
{
  ItemType person;
  Retrieve(root, item, found, person);
  return person;
}

// Recursive function for getPerson
void Retrieve(TreeNode* tree, 
     int& item, bool& found, ItemType& person)
// Recursively searches tree for item.
// Post: If there is an element someItem whose key matches item's,
//       found is true and item is set to a copy of someItem; 
//       otherwise found is false and item is unchanged.
{
  if (tree == NULL) {
    found = false;  // item is not found.
	}
  else if (item < tree->info.getSSN())      
    Retrieve(tree->left, item, found, person); // Search left subtree.
  else if (item > tree->info.getSSN())
    Retrieve(tree->right, item, found, person);// Search right subtree.
  else
  {                // item is found.
	person = tree->info;
	found = true;
   }
} 



// Recursive function for PutItem
void Insert(TreeNode*& tree, ItemType item);

//Inserts a Person Object into a binary search Tree
void TreeType::PutItem(ItemType item)
// Calls recursive function Insert to insert item into tree.
{
  Insert(root, item);
}

// Recursive function for PutItem(
void Insert(TreeNode*& tree, ItemType item)
// Inserts item into tree.
// Post:  item is in tree; search property is maintained.
{
  if (tree == NULL)
  {// Insertion place found.
    tree = new TreeNode;
    tree->right = NULL;
    tree->left = NULL;
    tree->info = item;
  }
  else if (item.getSSN() < tree->info.getSSN())
    Insert(tree->left, item);    // Insert in left subtree.
  else
    Insert(tree->right, item);   // Insert in right subtree.
}


// Recursive function for gethalfSiblings
void DeleteNode(TreeNode*& tree);

void Delete(TreeNode*& tree, int item);

void TreeType::DeleteItem(int item)
// Calls recursive function Delete to delete item from tree.
{
  Delete(root, item);
}

void Delete(TreeNode*& tree, int item)
// Deletes item from tree.
// Post:  item is not in tree.
{
	if (item < tree->info.getSSN())
    Delete(tree->left, item);   // Look in left subtree.
	else if (item > tree->info.getSSN())
    Delete(tree->right, item);  // Look in right subtree.
  else
    DeleteNode(tree);           // Node found; call DeleteNode.
}   

void GetPredecessor(TreeNode* tree, ItemType& data);

void DeleteNode(TreeNode*& tree)
// Deletes the node pointed to by tree.
// Post: The user's data in the node pointed to by tree is no 
//       longer in the tree.  If tree is a leaf node or has only 
//       non-NULL child pointer the node pointed to by tree is 
//       deleted; otherwise, the user's data is replaced by its 
//       logical predecessor and the predecessor's node is deleted.
{
  ItemType data;
  TreeNode* tempPtr;

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
	Delete(tree->left, data.getSSN());  // Delete predecessor node.
  }
}

void GetPredecessor(TreeNode* tree, ItemType& data)
// Sets data to the info member of the right-most node in tree.
{
  while (tree->right != NULL)
    tree = tree->right;
  data = tree->info;
}



TreeType::TreeType()
{
  root = NULL;
}

void Destroy(TreeNode*& tree);

TreeType::~TreeType()
// Calls recursive function Destroy to destroy the tree.
{
  Destroy(root);
}

void Destroy(TreeNode*& tree)
// Post: tree is empty; nodes have been deallocated.
{
  if (tree != NULL)
  {
    Destroy(tree->left);
    Destroy(tree->right);
    delete tree;
  }
}



void CopyTree(TreeNode*& copy, 
     const TreeNode* originalTree);

TreeType::TreeType(const TreeType& originalTree)
// Calls recursive function CopyTree to copy originalTree 
//  into root.
{
  CopyTree(root, originalTree.root);
}

void TreeType::operator= 
     (const TreeType& originalTree)
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

void CopyTree(TreeNode*& copy, 
     const TreeNode* originalTree)
// Post: copy is the root of a tree that is a duplicate 
//       of originalTree.
{
  if (originalTree == NULL)
    copy = NULL;
  else
  {
    copy = new TreeNode;
    copy->info = originalTree->info;
    CopyTree(copy->left, originalTree->left);
    CopyTree(copy->right, originalTree->right);
  }
}
