#include "ArgumentManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////
// AUTHOR: TYLER HU,   ID: 0276538                                                   //
//                                                                                   //
// Inspired by code posted by Dr. Rizk, Dr. Malik (textbook), and internet websites  //
///////////////////////////////////////////////////////////////////////////////////////

// B-TREE NODE CLASS //////////////////////////////////////////////////////////////////
class BTreeNode 
{
	public: 
		int numKeys;             //number of keys in node
		int *keysArr;            //dynamic array of keys
		BTreeNode **childrenArr; //dynamic array of child pointers 

		//constructor 
		BTreeNode(int degree) {
			numKeys = 0;
			//init dynamic arrays
			keysArr = new int[degree-1];
		  childrenArr = new BTreeNode *[degree];
			//sets array values
			for(int i=0; i<degree-1; i++) {
				keysArr[i]=0;
			}
			for(int j=0; j<degree; j++) {
				childrenArr[j]=NULL;
			}
		}
}; 
  
// B-TREE CLASS ///////////////////////////////////////////////////////////////////////
class BTree
{
	private:
    BTreeNode *root; //pointer to root node 
		int degree;      //holds degree for node

	public: 
    //constructor
    BTree(int deg) 
    {  
			root = NULL;  
			degree = deg;
		} 
		
		//searches a node for a key
		void searchNode(BTreeNode *cu, int& key, bool& isFound, int& loc) 
		{
			loc = 0;
			//traverses key array
			while (loc < cu->numKeys && key > cu->keysArr[loc]) {
				loc++;
			}
			//if key is found
			if (loc < cu->numKeys && key == cu->keysArr[loc]) {
				isFound = true;
			}
			//key not found
			else {
				isFound = false;
			}
		} //end searchNode

		//searches the tree
		bool search(int& key)
		{
			bool isFound = false;
			int loc;
			BTreeNode *cu;
			cu = root;

			while (cu != NULL && !isFound) {
				//calls search node function
				searchNode(cu, key, isFound, loc);
				//moves to next child pointer
				if (!isFound) {
					cu = cu->childrenArr[loc];
				}
			}
			return isFound;
		} //end search

		//handles root node adjustments
		void insert(int& key)
		{
			//cout << "inserting " << key << endl; //DEBUG

			bool isTaller = false;
			int middle;
			BTreeNode *right;

			//initial function call to see if tree is empty
			insertIntoBTree(root, right, key, middle, isTaller);

			//true if the tree is initially empty or the root was split
			if (isTaller) {
				BTreeNode *temp = new BTreeNode(degree);
				temp->numKeys = 1;
				temp->keysArr[0] = middle;
				temp->childrenArr[0] = root;
				temp->childrenArr[1] = right;
				
				root = temp;
			}
		} //end insert

		//inserts node into the tree
		void insertIntoBTree(BTreeNode *cu, BTreeNode* &right, 
												 int& key, int& middle, bool& isTaller) 
		{
			bool isFound = false;
			int pos = 0;

			//checks if tree is empty or function is at an empty subtree
			if (cu == NULL) {
				middle = key;
				right = NULL;
				isTaller = true;
			}
			else {
				//for (int k = 0; k < root->numKeys; k++)             //DEBUG
				//	cout << "root key  " << root->keysArr[k] << endl; //DEBUG
				//cout << "end\n";                                    //DEBUG
				searchNode(cu, key, isFound, pos);
				//checks for duplicates
				if (isFound == true) {
					return;
				}
				else {
					int insPos = pos;
					//cout << "inserting  " << key << endl; //DEBUG
					insertIntoBTree(cu->childrenArr[insPos], right, key, middle, isTaller);
					if (isTaller == true) {
						if (cu->numKeys < (degree - 1)) {
							insertIntoNode(cu, right, key, insPos);
							isTaller = false;
						}
						else {
							//init right node for splitting
							BTreeNode *rightNode = right;
							search(key);
							//checks for duplicates
							if (isFound == true) {
								isTaller = false;
								return;
							}
							splitNode(cu, right, rightNode, key, insPos, middle);
							right = rightNode;
							isTaller = true;
							key = middle;
						}
					}
				}
			}
		} //end insertIntoBTree

		//inserts key into tree node
		void insertIntoNode(BTreeNode *cu, BTreeNode* &right, int& key, int pos)
		{
			//cout << "inserting " << key << endl; //DEBUG
			int i;
			//adjusts elements of the key and child pointer arrays
			for (i = cu->numKeys; i > pos; i--) {
				cu->keysArr[i] = cu->keysArr[i - 1];
				cu->childrenArr[i + 1] = cu->childrenArr[i];
			}
			
			//inserts new key and child pointer into arrays
			cu->keysArr[i] = key;
			cu->childrenArr[i + 1] = right;
			//increments number of keys in node
			cu->numKeys++;
		} //end insertIntoNode

		//splits node into two new nodes
		void splitNode(BTreeNode *cu, BTreeNode *right, BTreeNode* &rightNode, 
		               int& key, int pos, int& middle)
		{
			//creates new node
			rightNode = new BTreeNode(degree);
			
			int midPos = (degree-1)/2;
			
			//new item goes in the first half of the node
			if (pos <= midPos) {
				int index = 0;
				int i = midPos;

				while (i < degree-1) {
					rightNode->keysArr[index] = cu->keysArr[i];
					rightNode->childrenArr[index + 1] = cu->childrenArr[i + 1];
					index++;
					i++;
				}

				cu->numKeys = midPos;
				insertIntoNode(cu, right, key, pos);
				(cu->numKeys)--;
				
				middle = cu->keysArr[cu->numKeys];
				
				rightNode->numKeys = index;
				rightNode->childrenArr[0] = cu->childrenArr[cu->numKeys + 1 ];
			}
			//new item goes in the second half of the node
			else {
				int i = midPos + 1;
				int index = 0;

				while (i < degree - 1) {
					rightNode->keysArr[index] = cu->keysArr[i];
					rightNode->childrenArr[index + 1] = cu->childrenArr[i + 1];
					index++;
					i++;
				}

				cu->numKeys = midPos;
				rightNode->numKeys = index;

				middle = cu->keysArr[midPos];

				insertIntoNode(rightNode, right, key, pos-midPos-1);
				rightNode->childrenArr[0] = cu->childrenArr[cu->numKeys + 1];
			}
			//rightNode = right;
		} //end splitNode

		//returns bool value if command level input is valid or not
		bool isValidCommandLevel(int commLevel) 
		{
			//gets level number of tree
			int numLevels = getLevelNum(root, 0);
			//cout << "levels: " << numLevels << endl; //DEBUG
			
			if (commLevel <= numLevels) {
				return true;
			}
			//default return
			return false;
		} //end isValidCommandLevel

		//returns number of levels in tree
		int getLevelNum(BTreeNode *cu, int levelNum)
		{
			if (cu == NULL) {
				return levelNum;
			}
			else {
				levelNum++;
				return getLevelNum(cu->childrenArr[0], levelNum);
			}
		} //end getLevelNum

		//inorder traversal helper for root
		void inOrder(const string output) 
		{
			//init output stream
			ofstream outfs(output, ios_base::app);

			keysInorder(root, outfs);
			
			outfs << endl;

			outfs.close();
		} //end inOrder

		//outputs inorder traversal of keys
		void keysInorder(BTreeNode *cu, ofstream &ofs)
		{
			if (cu != NULL) {
				keysInorder(cu->childrenArr[0], ofs);

				for (int i=0; i < cu->numKeys; i++) {
					ofs << cu->keysArr[i] << " ";
					keysInorder(cu->childrenArr[i + 1], ofs);
				}
			}
		} //end keysInorder

		//level traversal helper for root
		void levelTraverse(const string output, int inputLevel) 
		{
			//init output stream
			ofstream outfs(output, ios_base::app);
			//checks for valid command level input
			bool isValidComm = isValidCommandLevel(inputLevel); 

			if (isValidComm) {
				levelKeyTraverser(root, outfs, inputLevel);
			}
			else {
				outfs << "empty";
			}
			
			outfs << endl;

			outfs.close();
		} //end levelTraverse

		//outputs keys for a specified level in tree
		void levelKeyTraverser(BTreeNode *cu, ofstream &ofs, int level) 
		{
			//error checking if tree does not exist
			if (cu == NULL) { 
        return;  
			}
			//outputs all keys of the specified level
    	else if (level == 1) {
				for (int i=0; i < cu->numKeys; i++) {
        	ofs << cu->keysArr[i] << " ";  
				}
			}
			//traverses down tree
			else if (level > 1) { 
				for (int i=0; i < cu->numKeys+1; i++) {
					levelKeyTraverser(cu->childrenArr[i], ofs, level-1); 
				}
    	}
		} //end levelKeyTraverser
    
};

// MAIN ///////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {

	/*
	if (argc != 3 && argc != 2) {
		cout << "Invalid arguments" << endl;
		return 1;
	}*/

	
	ArgumentManager am(argc, argv);
	const string input = am.get("input");
	const string command = am.get("command");
	const string output = am.get("output");
	
	//init input stream
	ifstream infs(input);

	//const string output = "output.txt";

	//init command stream
	ifstream commfs(command);

	//clears output file (inspired by stack overflow website)
	ofstream outfs;
  outfs.open(output, ofstream::out | ofstream::trunc);
	outfs.close();

	//ERROR HANDLING: exits if input not found
	if (!infs) {
		cout << "ERROR: input file is missing. Exiting program." << endl;
		return 1;
	}

	//ERROR HANDLING: exits if command input not found
	if (!commfs) {
    cout << "ERROR: command file is missing. Exiting program." << endl;
    return 1;
  }

	//holds input number
	int tempInt = 0;
	//holds command degree
	int tempDeg = 0;
	//holds command level
	int tempLevel = 1;
	//holds input string
	string temp = "";
	
	//reads from command stream for degree command
	while (!commfs.eof()) {
		getline(commfs, temp, '=');
		int tempSize = 0;
		//stores length of sentence line
		if (!temp.empty() && temp != "\r") {
			//stores length of sentence line
			tempSize = temp.length();
			//avoids empty lines
			while (tempSize == 0) { 
				getline(commfs, temp); 
				tempSize = temp.length();
			}
			//checks for empty strings
			if (tempSize != 0) {
				commfs >> tempDeg;
			}
		}
	}
	//cout << "degree: " << tempDeg << endl << endl; //DEBUG
	commfs.close();

	//init tree
	BTree myTree(tempDeg);

	//reads from input stream for keys
	while (!infs.eof()) {
		getline(commfs, temp);
		int tempSize = 0;
		//stores length of sentence line
		if (!temp.empty() && temp != "\r") {
			//stores length of sentence line
			tempSize = temp.length();
			//avoids empty lines
			while (tempSize == 0) { 
				getline(commfs, temp); 
				tempSize = temp.length();
			}
			//checks for empty strings
			if (tempSize != 0) {
				infs >> tempInt;
				//cout << " " << tempInt; //DEBUG
				myTree.insert(tempInt);
			}
		}
	}
	infs.close();
	//myTree.inOrder(); //DEBUG

	//init command stream
	commfs.open(command);

	//reads from command stream for degree command
	while (!commfs.eof()) {
		getline(commfs, temp);
		int tempSize = 0;
		//stores length of sentence line
		if (!temp.empty() && temp != "\r") {
			//stores length of sentence line
			tempSize = temp.length();
			//avoids empty lines
			while (tempSize == 0) { 
				getline(commfs, temp); 
				tempSize = temp.length();
			}
			//checks for empty strings
			if (tempSize != 0) {
				//cout << temp << endl; //DEBUG
				if (temp[0] == 'I') {
					myTree.inOrder(output);
					//cout << "inorder" << endl; //DEBUG
				}
				else if (temp[0] == 'L') {
					//preps temp string for int extraction
					temp.erase(0,5);
					stringstream commLevel(temp);
					commLevel >> tempLevel; 
					myTree.levelTraverse(output, tempLevel);
					//cout << "level: " << tempLevel << endl; //DEBUG
				}
				else {
				}
			}
		}
	}
	//cout << "degree: " << tempDeg << endl << endl; //DEBUG
	commfs.close();

	return 0;
}