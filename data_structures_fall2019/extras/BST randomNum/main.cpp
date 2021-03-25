#include <iostream>
#include <string>
#include <time.h>

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////
// AUTHOR: TYLER HU,   ID: 0276538                                                   //
//                                                                                   //
// Inspired by code from Dr. Rizk, Dr. Malik (textbook), and internet websites       //
///////////////////////////////////////////////////////////////////////////////////////

// NODE TEMPLATE //////////////////////////////////////////////////////////////////////
template <typename T>
class BSTNode { 
	public:
		T data; 
    BSTNode<T> *left;
		BSTNode<T> *right; 

		//default constructor
    BSTNode<T>()
    {
			this->data = -1;
			this->left = NULL;
			this->right = NULL;
    }
};

// BST TEMPLATE ///////////////////////////////////////////////////////////////////////
template <typename T>  
class BSTree { 
	private:
		//pointer to root
    BSTNode<T> *root; 

	public:
		//default constructor
		BSTree()
		{
			this->root = NULL;
		}

		//returns root
		BSTNode<T>* getRoot()
		{
			BSTNode<T>* cu = root;
			return cu;
		}

		//checks if tree is empty
		bool isEmpty() const
		{
			if (root == NULL)
				return true; 
			else
				return false;
		}

		//inserts data node 
		void inserter(const T &newData) 
		{
			BSTNode<T> *cu = root; 								//pointer to traverse the tree
			BSTNode<T> *prev = NULL; 							//pointer behind current
			BSTNode<T> *newNode = new BSTNode<T>; //new node

			newNode->data = newData;

			if (root == NULL) {
				root = newNode;
			}
			else {
				//traverses tree
				while (cu != NULL) {
					prev = cu;
					if (newData < cu->data) {
						cu = cu->left;
					}
					else {
						cu = cu->right;
					}
				}
				//inserts either left or right
				if (newData < prev->data) {
					prev->left = newNode;
				}
				else {
					prev->right = newNode;
				}
			}
		}

		//deletes node from tree and adjusts pointers
		void deleteNode(BSTNode<T>* &toDelete) 
		{
			BSTNode<T> *cu = NULL;   //pointer to traverse the tree
			BSTNode<T> *prev = NULL; //pointer behind current
			BSTNode<T> *temp;			   //pointer to node to be deleted
			
			if (toDelete == NULL) {
				cout << "Error: The node to be deleted is NULL." << endl;
				return;
			}
			else if (toDelete->left == NULL && toDelete->right == NULL) {
				temp = toDelete;
				toDelete = NULL;
				delete temp;
			}
			else if (toDelete->left == NULL) {
				temp = toDelete;
				toDelete = temp->right;
				delete temp;
			}
			else if (toDelete->right == NULL) {
				temp = toDelete;
				toDelete = temp->left;
				delete temp;
			}
			else {
				cu = toDelete->left;
				//traverses right forks of left branch
				while (cu->right != NULL) {
					prev = cu;
					cu = cu->right;
				}
				toDelete->data = cu->data;

				if (prev == NULL) { //current did not move;
												  	//current == toDelete->left; adjust toDelete
					toDelete->left = cu->left;
				}
				else {
					prev->right = cu->left;
				}
				delete cu;
			}
		}

		void deleter(const T &delData)
		{
			BSTNode<T> *cu = root;   //pointer to traverse the tree
			BSTNode<T> *prev = root; //pointer behind current
			bool isFound = false;

			if (root == NULL) {
				cout << "Cannot delete from an empty tree." << endl;
				return;
			}
			else {
				while (cu != NULL && !isFound) {
					if (cu->data == delData) {
						isFound = true;
					}
					else {
						prev = cu;
						//traverses left
						if (delData < cu->data) {
							cu = cu->left;
						}
						//traverses right
						else {
							cu = cu->right;
						}
					}
				}
			
				if (cu == NULL) {
					cout << "The delete item is not in the tree." << endl;
				}
				else if (isFound) {
					if (cu == root) {
						deleteNode(root);
					}
				}
				else if (delData < prev->data) {
					deleteNode(prev->left);
				}
				else {
					deleteNode(prev->right);
				}
			}
		}
		//recursive traversal (pre order)
		void traversePreorder(BSTNode<T> *cu) const
		{
			if (cu != NULL) {
				cout << cu->data << " ";
				traversePreorder(cu->left);
				traversePreorder(cu->right);
			}
		}
		//recursive traversal (in order)
		void traverseInorder(BSTNode<T> *cu) const
		{
			if (cu != NULL) {
				traverseInorder(cu->left);
				cout << cu->data << " ";
				traverseInorder(cu->right);
			}
		}
		//recursive traversal (post order)
		void traversePostorder(BSTNode<T> *cu) const
		{
			if (cu != NULL) {
				traversePostorder(cu->left);
				traversePostorder(cu->right);
				cout << cu->data << " ";
			}
		}
};

// MAIN ///////////////////////////////////////////////////////////////////////////////
int main() 
{
	int const MAX = 5;
	int arr[MAX];

	srand(time(NULL));

	//builds array of random ints
	for (int i=0; i<MAX; i++) {
    bool ifUnique;
		int newNum;
    do {
      ifUnique = true;
    	newNum = rand()%100+1;

      for (int j=0; j<i; j++) {
				if (arr[j] == newNum) {
				ifUnique = false;     
				break;
				}
      }
    } while (!ifUnique);

    arr[i] = newNum;
		//cout << arr[i] << " "; //DEBUG
	}

	BSTree<int> myTree;

	for (int i=0; i<MAX; i++) {
		myTree.inserter(arr[i]);
	}

	cout << "Unsorted array: ";
	for (int i=0; i<MAX; i++) {
		cout << arr[i] << " ";
	}

	cout << "\n\nPre order traversal of BST: ";
	myTree.traversePreorder(myTree.getRoot());
	cout << "\n\nIn order traversal of BST: ";
	myTree.traverseInorder(myTree.getRoot());
	cout << "\n\nPost order traversal of BST: ";
	myTree.traversePostorder(myTree.getRoot());

	return 0;
}