
#include <fstream>
#include "hash.h"

using namespace std;

// BST.cpp
//#include "BST.h"

template <class NodeType>
TreeNode<NodeType>::TreeNode(const NodeType &d){
	data = d;
	leftChild = NULL;
	rightChild = NULL;
}

template <class NodeType>
TreeNode<NodeType>::TreeNode(TreeNode<NodeType> *Node){
	data = Node->data;
	leftChild = Node->leftChild;
	rightChild = Node->rightChild;
}


template <class NodeType>
BinarySearchTree<NodeType>::BinarySearchTree(NodeType data){
	rootNode = new TreeNode<NodeType>(data);
	nNodes = 1;
}

template <class NodeType>
BinarySearchTree<NodeType>::BinarySearchTree(){
	rootNode = NULL;
	nNodes = 0;
}

template <class NodeType>
TreeNode<NodeType> ** BinarySearchTree<NodeType>::SearchHelper(TreeNode<NodeType> *&curNode, const NodeType &searchKey){
	if (searchKey < curNode->data){
		if (curNode->leftChild)
			return SearchHelper(curNode->leftChild, searchKey);
		else
			return &curNode->leftChild;
	}
	else if (searchKey > curNode->data){
		if (curNode->rightChild)
			return SearchHelper(curNode->rightChild, searchKey);
		else
			return &curNode->rightChild;
	}	
	else // searchKey == curNode.data
		return &curNode;//curNode;
}

template <class NodeType>
BOOL BinarySearchTree<NodeType>::InsertData(NodeType data){
	TreeNode<NodeType> **newNode;
	
	if (rootNode != NULL){
		newNode = SearchHelper(rootNode, data);
		if (*newNode == NULL){
			*newNode = new TreeNode<NodeType>(data);
			nNodes++;
			return TRUE;
		}
		else
			return FALSE;
	}
	else {
		rootNode = new TreeNode<NodeType>(data);
		nNodes = 1;
		return TRUE;
	}
}

template <class NodeType>
BOOL BinarySearchTree<NodeType>::SearchForNodeData(NodeType *&data){
	if (rootNode){
		TreeNode<NodeType> **Node;
		Node = SearchHelper(rootNode, *data);
		if (*Node){
			data = &((*Node)->data);
			return TRUE;
		} 
	}
	return FALSE;
}

template <class NodeType>
void BinarySearchTree<NodeType>::InorderTraversalHelper(TreeNode<NodeType> *T){
	if (T->leftChild)
		InorderTraversalHelper(T->leftChild);
	// visit node
	cout << T->data << ' ';
	if (T->rightChild)
		InorderTraversalHelper(T->rightChild);
}

template <class NodeType>
void BinarySearchTree<NodeType>::InorderTraversal(){
	if (rootNode)
		InorderTraversalHelper(rootNode);
	cout << endl;
}

template <class NodeType>
void BinarySearchTree<NodeType>::FillArrayHelper(TreeNode<NodeType> *T, int &count, NodeType *Array /*=NULL*/){
	if (T->leftChild)
		FillArrayHelper(T->leftChild, count, Array);
	// visit node
	if (Array)
		Array[count++] = T->data; // deep copy

	if (T->rightChild)
		FillArrayHelper(T->rightChild, count, Array);
}

template <class NodeType>
void BinarySearchTree<NodeType>::FillArray(NodeType *&Array, int &nElements){
	Array = new NodeType[nNodes];
	nElements = 0;
	if (nNodes > 0)
		FillArrayHelper(rootNode, nElements, Array);
}

template <class NodeType>
void BinarySearchTree<NodeType>::GetNodeHelper(TreeNode<NodeType> *T, int NodeNumber, int &whichNode, TreeNode<NodeType> *&Node){
	
	if (T->leftChild)
		GetNodeHelper(T->leftChild, NodeNumber, whichNode, Node);
	if (Node) return;
	// visit node
	whichNode++;
	if (whichNode == NodeNumber)
		Node = T;
	
	if (T->rightChild)
		GetNodeHelper(T->rightChild, NodeNumber, whichNode, Node);
	if (Node) return;	
	
}

template <class NodeType>
NodeType * BinarySearchTree<NodeType>::GetNode(int NodeNumber){
	// find the first node
	//TreeNode<NodeType> currNode = 
	TreeNode<NodeType> *Node = NULL;
	int whichNode = 0;
	if (NodeNumber <= nNodes)
		GetNodeHelper(rootNode, NodeNumber, whichNode, Node);
	return &Node->data;
}

template <class NodeType>
TreeNode<NodeType> * BinarySearchTree<NodeType>::DeleteHelper(TreeNode<NodeType> *thisNode){
	//go to the right, then go to the left until you find null.
	TreeNode<NodeType> * pSub = thisNode;
	//if (thisNode->rightChild){
	thisNode = thisNode->rightChild;
	if (thisNode->leftChild){
		while (thisNode->leftChild){
			pSub = thisNode;
			thisNode = thisNode->leftChild;
		}
		if (thisNode->rightChild)
			pSub->leftChild = thisNode->rightChild;
		else
			pSub->leftChild = NULL;
	}
	else{
		if (thisNode->rightChild)
			pSub->rightChild = thisNode->rightChild;
		else
			pSub->rightChild = NULL;
	}
	return thisNode;
	
}



template <class NodeType>
TreeNode<NodeType> * BinarySearchTree<NodeType>::GetRootNode(){
	return rootNode;
}

template <class NodeType>
int BinarySearchTree<NodeType>::GetSize(){
	return nNodes;
}

template <class NodeType>
BOOL BinarySearchTree<NodeType>::DeleteNode(NodeType nodeData){
	
	if (!rootNode)
		return FALSE;

	TreeNode<NodeType> * currNode = rootNode;
	TreeNode<NodeType> ** ptrChildNode = NULL;
	while(1){
		if (nodeData < currNode->data){
			if (currNode->leftChild == NULL)
				return FALSE;

			if (currNode->leftChild->data == nodeData){
				ptrChildNode = &currNode->leftChild;
				currNode = currNode->leftChild;
				break;
			}
			currNode = currNode->leftChild;
		}
		else if (nodeData > currNode->data){
			if (currNode->rightChild == NULL)
				return FALSE;

			if (currNode->rightChild->data == nodeData){
				ptrChildNode = &currNode->rightChild;
				currNode = currNode->rightChild;
				break;
			}
			currNode = currNode->rightChild;
		}
		else{
			ptrChildNode = &rootNode;
			break;
		}
	}

	if (currNode->leftChild && currNode->rightChild){
	// if it has two children, promote the nextNode in its place
		TreeNode<NodeType> *rightChildPtr = currNode->rightChild;
		TreeNode<NodeType> *nextNodePtr = DeleteHelper(currNode);

		if (nextNodePtr == rightChildPtr){
			rightChildPtr->leftChild = currNode->leftChild;
			*currNode = rightChildPtr;
			
			delete nextNodePtr;
			nNodes--;
		}
		else {
			currNode->data = nextNodePtr->data;
			nNodes--;
			delete nextNodePtr;
		}
	}
	else if (currNode->leftChild){
	// if it has no right child, promote the left child in its place
		TreeNode<NodeType> *ptrLeftChild = currNode->leftChild;
		delete currNode;
		*ptrChildNode = ptrLeftChild;
		nNodes--;
	}
	else if (currNode->rightChild){
	// if it has no left child, promote the right child in its place
		TreeNode<NodeType> *ptrRightChild = currNode->rightChild;
		delete currNode;
		*ptrChildNode = ptrRightChild;
		nNodes--;
	}
	else{
	// if it has no children, delete it	
		delete currNode;
		if (ptrChildNode)
			*ptrChildNode = NULL;
		else
			rootNode = NULL;
		nNodes--;
	}	
	return TRUE;
}

template <class NodeType>
void BinarySearchTree<NodeType>::DeleteAllNodesHelper(TreeNode<NodeType> *T){
	if (T->leftChild)
		DeleteAllNodesHelper(T->leftChild);
	if (T->rightChild)
		DeleteAllNodesHelper(T->rightChild);
	delete T;
}

template <class NodeType>
void BinarySearchTree<NodeType>::DeleteAllNodes(){
	if (rootNode){
		DeleteAllNodesHelper(rootNode);	
		nNodes = 0;
		rootNode = NULL;
	}
}

//hash.cpp
//#include "hash.h"

HashTable::HashTable(){

}

BOOL HashTable::Insert(string H){
	return Nodes[Hash(H)].InsertData(H);	
}

BOOL HashTable::Remove(string H){
	return Nodes[Hash(H)].DeleteNode(H);
}

BOOL HashTable::IsInTable(string H){
	string *T = &H;
	return Nodes[Hash(H)].SearchForNodeData(T);
}

int  HashTable::NValuesAtNode(int x){
	return Nodes[x].GetSize();
}

int HashTable::Hash(string x){
	int value = 0;
	char c;
	for (int i = 0; i < 12 && i < x.length(); i++){
		c = x[i];
		value *= 32;
		value += toupper(c) - 'A';
		value %= 37;
	}
	return value;
}
	

// Linkage in Names with File Scope

//HashTable h;
//BinarySearchTree<int> C;

void main(){

	ifstream fin("aliases.txt");
	char aText[16];
	string animal;
	HashTable Animals;
	while (fin.getline(aText,15)){
		animal = aText;
		Animals.Insert(animal);
	}

	cout << "This program reads the names of animals from a file and inserts them " << endl
		 << "into a hash table chained to binary search trees.  It then outputs the "<< endl
		 << "number of animals stored at each hash table index." << endl;

	for (int i = 0; i < 37; i++){
		cout << "Hash index " << i << '\t' << Animals.NValuesAtNode(i) << '\t';
		if ((i-1) % 2 == 0)
			cout << endl;
	}
	cout << endl;
}