#include <iostream.h>
#include <string.h>
#include "Binary Search Tree.h"


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
TreeNode<NodeType>* BinarySearchTree<NodeType>::SearchForNode(NodeType data){
	if (rootNode){
		TreeNode<NodeType> **Node;
		Node = SearchHelper(rootNode, data);
		return *Node;
	}
	return NULL;
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
	FillArrayHelper(rootNode, nElements, Array);
}

template <class NodeType>
TreeNode<NodeType> * BinarySearchTree<NodeType>::GetNextNode(TreeNode<NodeType> *thisNode){
	//go to the right, then go to the left until you find null.
	if (thisNode->rightChild){
		thisNode = thisNode->rightChild;
		while (thisNode->leftChild)
			thisNode = thisNode->leftChild;
		return thisNode;
	}
	return NULL;
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
		else
			break;
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


void main() {
//BinarySearchTree<double> intTree(10);
	BinarySearchTree<int> intTree;
	intTree.InsertData(5);
	intTree.SearchForNode(14);
	intTree.InsertData(7);
	intTree.InsertData(12);
	intTree.InsertData(4);
	intTree.InsertData(3);
	intTree.InsertData(8);
	intTree.InorderTraversal();
	
	intTree.DeleteNode(5);
	cout << endl;
	intTree.InorderTraversal();

	intTree.DeleteNode(7);
	cout << endl;
	intTree.InorderTraversal();

	intTree.DeleteNode(10);
	cout << endl;
	intTree.InorderTraversal();

	intTree.DeleteNode(8);
	cout << endl;
	intTree.InorderTraversal();

	intTree.DeleteNode(4);
	cout << endl;
	intTree.InorderTraversal();

	intTree.DeleteNode(3);
	cout << endl;
	intTree.InorderTraversal();

	intTree.DeleteNode(12);
	cout << endl;
	intTree.InorderTraversal();

	
	
	/*
	int nElements;
	int *a;
	intTree.FillArray(a, nElements);
	for (int i = 0; i < nElements; i++){
		cout << a[i] << ' ';
	}
	delete [] a;
	TreeNode<int> (* myNode)(intTree.GetRootNode());
	do {

		myNode = intTree.GetNextNode(myNode);
		if (myNode)
			cout << myNode->data << ' ';
	} while (myNode);
	*/
	// what remains to do for my binary search tree?
	// be able to delete items.	
}


