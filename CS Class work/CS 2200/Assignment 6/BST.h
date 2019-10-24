
typedef int BOOL;
#define TRUE	1
#define FALSE	0
#define NULL	0

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
	BOOL SearchForNodeData(NodeType *&data);
	void InorderTraversal();
	void FillArray(NodeType *&Array, int &nElements); 
	NodeType * GetNode(int NodeNumber);
	void DeleteAllNodes();	
	
	TreeNode<NodeType> * GetNextNode(TreeNode<NodeType> *thisNode);
	TreeNode<NodeType> * GetRootNode();
	int GetSize();
private:
	void InorderTraversalHelper(TreeNode<NodeType> *T);
	TreeNode<NodeType> ** SearchHelper(TreeNode<NodeType> *&curNode, const NodeType &searchKey);
	void FillArrayHelper(TreeNode<NodeType> *T, int &count, NodeType *Array =NULL);
	TreeNode<NodeType> * DeleteHelper(TreeNode<NodeType> *thisNode);
	void GetNodeHelper(TreeNode<NodeType> *T, int NodeNumber, int &whichNode, TreeNode<NodeType> *&Node);
	void DeleteAllNodesHelper(TreeNode<NodeType> *T);	

	TreeNode<NodeType> *rootNode;
	int nNodes;
};


