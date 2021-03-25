#include <iostream>

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////
// AUTHORS: TYLER HU,     ID: 0276538                                                //
//          ARMANDO MATA, ID: 1656706                                                //
//																																									 //
// Inspired by code from Dr. Rizk, Dr. Malik (textbook), Sunny (TA) & Github         //
///////////////////////////////////////////////////////////////////////////////////////

// NODE ///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
struct node 
{
   int data;
   node *left;
   node *right;
   int height;
};

// CLASSES ////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
class AVLTree 
{ 
  public:
		node *root;

		//default constructor
		AVLTree() 
		{
			root = NULL;
		}

		//reinit tree to empty state
		void makeEmpty(node *t) 
		{
			if (t == NULL)
				return;
					
			makeEmpty(t->left);
			makeEmpty(t->right);
			
			free(t);
		}

		//creates root and calls node inserter function////////////////////////////////////
		void insert(int x)
    {
        root = insertIntoAVL(x, root);
    }

		//inserts nodes into tree and balances
		node* insertIntoAVL(int x, node* t)
		{
			//creates node to be inserted
			if (t == NULL) {
				t = new node;
				t->data = x;
				t->left = NULL;
				t->right = NULL;
				t->height = 0;
				
				//cout << endl << t->data << endl; //DEBUG
			}
			//inserts to the left of root
      else if (x < t->data) {
				//cout << "\nAdding left."; //DEBUG
				t->left = insertIntoAVL(x, t->left);

				//checks for balance
				if (getBalance(t) > 1) {
					//if left-left unbalanced
					if (x < t->left->data) {
						//cout << "\nLL R"; //DEBUG
						t = singleRightRotate(t);
					}
					//else left-right rotation
					else {
						//cout << "\nLR R"; //DEBUG
						t = doubleRightRotate(t);
					}
				}
      }
			//inserts to the right of root
      else if (x > t->data) {
				//cout << "\nAdding right."; //DEBUG
				t->right = insertIntoAVL(x, t->right);

				//checks for balance
				if (getBalance(t) < -1) {
					//if right-right unbalanced
					if (x > t->right->data) {
						//cout << "\nRR R"; //DEBUG
						t = singleLeftRotate(t);
					}
					//else right-left rotation
					else {
						//cout << "\nLR R"; //DEBUG
						t = doubleLeftRotate(t);
					}
				}
      }
			//outputs if duplicate value found
			else {
				cout << "\n\nIllegal duplicate input value detected: " << x << 
				        ". Skipping insertion of duplicate value...\n";
			}

			//sets height of node
			t->height = max(height(t->left), height(t->right))+1;

			return t;
		}

		//removes root if needed and calls remover function////////////////////////////////
		void remove(int x)
    {
      root = removeFromAVL(x, root);
    }

		//removes nodes from tree and balances tree
		node* removeFromAVL(int x, node *t) 
		{
			node* temp;

			//error checking if tree is empty
			if (root == NULL)  
        return NULL;  

			//error checking if node not found
			if (t == NULL) {
				return NULL;
			}
			//searches for element in left side of tree
			else if (x < t->data) {
				t->left = removeFromAVL(x, t->left);
			}
			//searches for element in right side of tree
			else if (x > t->data) {
				t->right = removeFromAVL(x, t->right);
			}
			//deletes node with 2 children
			else if (t->left != NULL && t->right != NULL) {
				//finds child node with minimum element in right side of tree 
				temp = findMin(t->right);
				//copies data value into new temp node
				t->data = temp->data;
				//deletes node
				t->right = removeFromAVL(t->data, t->right);
			}
			//deletes node with 1 or 0 children
			else {
				temp = t;
				//if left child doesn't exist
				if (t->left == NULL) {
					t = t->right;
				}
				//if left child doesn't exist
				else if (t->right == NULL) {
					t = t->left;
				}
				//frees memory
				delete temp;
			}
			
			//returns if tree only had one node
			if (t == NULL)
				return t;

			//updates height of current node
			t->height = max(height(t->left), height(t->right))+1;

			//rebalances tree
			if (height(t->left) - height(t->right) == -2) {
				//if right-right unbalanced
				if (height(t->right->right) - height(t->right->left) == 1) {
					return singleLeftRotate(t);
				}
				//else right-left rotation
				else {
					return doubleLeftRotate(t);
				}
			}
			//checks for balance
			else if (getBalance(t) < -1) {
				//if left-left unbalanced
				if (height(t->left->left) - height(t->left->right) == 1) {
					return singleRightRotate(t);
				}
				//else left-right rotation
				else {
					return doubleRightRotate(t);
				}
			}

			return t;
		}

		//rotations////////////////////////////////////////////////////////////////////////
		//ll rotation
		node* singleLeftRotate(node* &t)
		{
			//checks if valid branch exists for rotation
      if (t->right != NULL) {
		    node* temp;
				temp = t->right;
		    t->right = temp->left;
		    temp->left = t;

				//adjusts heights
		    t->height = max(height(t->left), height(t->right)) + 1;
		    temp->height = max(height(t->right), t->height) + 1;

		    return temp;
      }
      return t;
		}

		//rr rotation
		node* singleRightRotate(node* &t)
		{
			//checks if valid branch exists for rotation
			if (t->left != NULL) {
				node* temp;
				temp = t->left;
				t->left = temp->right;
				temp->right = t;

				//adjusts heights
				t->height = max(height(t->left), height(t->right)) + 1;
				temp->height = max(height(temp->left), t->height) + 1;

				return temp;
			}
			return t;
		}
			
		//rl rotation
		node *doubleLeftRotate(node* &t) 
		{
			t->right = singleRightRotate(t->right);
      
			return singleLeftRotate(t);
		}
			
		//lr rotation
		node *doubleRightRotate(node* &t) 
		{
			t->left = singleLeftRotate(t->left);
      
			return singleRightRotate(t);
		}

		//helper functions/////////////////////////////////////////////////////////////////
		//returns node with min value	
		node *findMin(node *t) 
		{
			if (t == NULL)
				return NULL;
			else if (t->left == NULL)
				return t;
			else
				return findMin(t->left);
		}
			
		//returns node with max value	
		node *findMax(node *t) 
		{
			if (t == NULL)
				return NULL;
			else if (t->right == NULL)
				return t;
			else
				return findMax(t->right);
		}

		//returns height of node
		int height(node *t) 
		{
			if (t == NULL)
				return -1;
			
			return t->height;
		}
			
		//returns height of node children
		int getBalance(node *t) 
		{
			if (t == NULL)  
				return 0;  
      else   
      	return height(t->left) - height(t->right);  
    }

		//displays in order traversal	
		void inorder(node *t) 
		{
			if (t == NULL)
				return;

			inorder(t->left);    
			cout << t->data << " ";
			inorder(t->right);
		}
			
		//displays tree
		void display(node *t, int level) 
		{			
			if (t != NULL) {
				display(t->right, level + 1);
				cout << "\n";
				if (t == root)
					cout << "Root -> ";
				for (int i = 0; i < level && t != root; i++)
					cout << "       ";
				cout << t->data;
				display(t->left, level + 1);
			}
		}
	
};

// MAIN ///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
int main() {
	AVLTree t;

	t.insert(20);
	t.insert(25);
	t.insert(15);
	t.insert(10);
	t.insert(30);
	t.insert(5);
	t.insert(35);
	t.insert(67);
	t.insert(43);
	t.insert(21);
	t.insert(10);
	t.insert(89);
	t.insert(38);
	t.insert(69);

	cout << "\nIn order traversal before removal: ";
	t.inorder(t.root);
	cout << endl << "\nAVL tree before removal:\n";
	t.display(t.root, 1);

	t.remove(5);
	t.remove(35);
	t.remove(65);
	t.remove(89);
	t.remove(43);
	t.remove(88);
	t.remove(20);
	t.remove(38);

	cout << "\n\nIn order traversal after removal: ";
	t.inorder(t.root);
	cout << endl << "\nAVL tree after removal:\n";
	t.display(t.root, 1);

	return 0;
}