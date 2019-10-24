#include <stddef.h>

typedef int BOOL;
#define TRUE	1
#define FALSE	0

template <class NodeType>
class TreeNode {
public:
	TreeNode(const NodeType &data);
	TreeNode(TreeNode<NodeType> *Node);
	NodeType data;
	TreeNode *leftChild;
	TreeNode *rightChild;
};

template <class NodeType>
class BinarySearchTree {
public:
	BinarySearchTree(NodeType data);
	BinarySearchTree();
	BOOL InsertData(NodeType data);
	BOOL DeleteNode(NodeType nodeData);
	TreeNode<NodeType> * SearchForNode(NodeType data);
	void InorderTraversal();
	void FillArray(NodeType *&Array, int &nElements); 
	
	TreeNode<NodeType> * GetNextNode(TreeNode<NodeType> *thisNode);
	TreeNode<NodeType> * GetRootNode();
private:
	void InorderTraversalHelper(TreeNode<NodeType> *T);
	TreeNode<NodeType> ** SearchHelper(TreeNode<NodeType> *&curNode, const NodeType &searchKey);
	void FillArrayHelper(TreeNode<NodeType> *T, int &count, NodeType *Array =NULL);
	TreeNode<NodeType> * DeleteHelper(TreeNode<NodeType> *thisNode);

	TreeNode<NodeType> *rootNode;
	int nNodes;
};






