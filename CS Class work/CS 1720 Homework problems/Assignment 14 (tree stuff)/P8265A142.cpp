//Mark Salisbury
//marks
//P8265A142.cpp
//CS 1720
/*
CS1720 Assignment 14

Put code for each program in one file and turn in the .cpp. 

A142. (Printing trees) Do problem 15.25 from your text.
*/

#include <iostream.h>
#include <iomanip.h>
#include <assert.h>

//*******************************************************************************
//************************|  Class TreeNode  |***********************************
//*******************************************************************************

template< class NODETYPE > class Tree;  // forward declaration

template< class NODETYPE >
class TreeNode {
   friend class Tree< NODETYPE >;
public:
   TreeNode( const NODETYPE &d )   
      : leftPtr( 0 ), data( d ), rightPtr( 0 ) { }
   NODETYPE getData() const { return data; }
private:
   TreeNode< NODETYPE > *leftPtr;  // pointer to left subtree
   NODETYPE data;
   TreeNode< NODETYPE > *rightPtr; // pointer to right subtree
};

//*******************************************************************************
//************************|    Class Tree    |***********************************
//*******************************************************************************

template< class NODETYPE >
class Tree {
public:
   Tree();
   void insertNode( const NODETYPE & );
   void preOrderTraversal() const;
   void inOrderTraversal() const;
   void postOrderTraversal() const;
   void levelOrderTraversal() const;
   void outputTree(TreeNode<NODETYPE> *, int ) const;
   TreeNode<NODETYPE> *getRootPtr() const;
private:
   TreeNode< NODETYPE > *rootPtr;

   // utility functions
   void insertNodeHelper( 
           TreeNode< NODETYPE > **, const NODETYPE & );
   void preOrderHelper( TreeNode< NODETYPE > * ) const;
   void inOrderHelper( TreeNode< NODETYPE > * ) const;
   void postOrderHelper( TreeNode< NODETYPE > * ) const;
};

template< class NODETYPE >
Tree< NODETYPE >::Tree() { rootPtr = 0; }

template< class NODETYPE >
void Tree< NODETYPE >::insertNode( const NODETYPE &value )
   { insertNodeHelper( &rootPtr, value ); }

// This function receives a pointer to a pointer so the
// pointer can be modified.
template< class NODETYPE >
void Tree< NODETYPE >::insertNodeHelper( 
        TreeNode< NODETYPE > **ptr, const NODETYPE &value )
{
   if ( *ptr == 0 ) {                   // tree is empty
      *ptr = new TreeNode< NODETYPE >( value );
      assert( *ptr != 0 );
   }
   else                              // tree is not empty
      if ( value < ( *ptr )->data )
         insertNodeHelper( &( ( *ptr )->leftPtr ), value );
      else
         if ( value > ( *ptr )->data )
            insertNodeHelper( &( ( *ptr )->rightPtr ), value );
         else
            cout << value << " dup" << endl;
}

template< class NODETYPE > 
void Tree< NODETYPE >::preOrderTraversal() const
   { preOrderHelper( rootPtr ); }

template< class NODETYPE >
void Tree< NODETYPE >::preOrderHelper( 
                          TreeNode< NODETYPE > *ptr ) const
{
   if ( ptr != 0 ) {
      cout << ptr->data << ' ';
      preOrderHelper( ptr->leftPtr );
      preOrderHelper( ptr->rightPtr );
   }
}

template< class NODETYPE >
void Tree< NODETYPE >::inOrderTraversal() const
   { inOrderHelper( rootPtr ); }

template< class NODETYPE >
void Tree< NODETYPE >::inOrderHelper( 
                          TreeNode< NODETYPE > *ptr ) const
{
   if ( ptr != 0 ) {
      inOrderHelper( ptr->leftPtr );
      cout << ptr->data << ' ';
      inOrderHelper( ptr->rightPtr );
   }
}

template< class NODETYPE >
void Tree< NODETYPE >::postOrderTraversal() const
   { postOrderHelper( rootPtr ); }

template< class NODETYPE >
void Tree< NODETYPE >::postOrderHelper( 
                          TreeNode< NODETYPE > *ptr ) const
{
   if ( ptr != 0 ) {
      postOrderHelper( ptr->leftPtr );
      postOrderHelper( ptr->rightPtr );
      cout << ptr->data << ' ';
   }
}

template <class NODETYPE >
void Tree<NODETYPE>::levelOrderTraversal() const
{
	Queue< TreeNode<NODETYPE> * > NodesToPrint;
	Queue< TreeNode<NODETYPE> * > RightNodes;

	TreeNode<NODETYPE> *nodePtr = rootPtr;
	TreeNode<NODETYPE> *rightPtr;	
	
	bool printEndl = false;

	if (nodePtr != 0) {
		NodesToPrint.enqueue( nodePtr );
		while (nodePtr != 0){
			RightNodes.enqueue( nodePtr );
			if (nodePtr->rightPtr != 0)
				nodePtr = nodePtr->rightPtr;
			else if(nodePtr->leftPtr != 0)
				nodePtr = nodePtr->leftPtr;
			else
				nodePtr = 0;
		}
	}

	RightNodes.dequeue( rightPtr );
	while (!NodesToPrint.isQueueEmpty()){
		NodesToPrint.dequeue( nodePtr );
		
		if (rightPtr == nodePtr) {
			printEndl = true;
			RightNodes.dequeue( rightPtr );
		} 
		else
			printEndl = false;

		cout << nodePtr->data << (printEndl == true ? '\n' : ' ');
		if ( nodePtr->leftPtr != 0 )
			NodesToPrint.enqueue( nodePtr->leftPtr );
		if ( nodePtr->rightPtr != 0 )
			NodesToPrint.enqueue( nodePtr->rightPtr );

	}

}

template <class NODETYPE >
void Tree<NODETYPE>::outputTree(TreeNode<NODETYPE> *currNode, int totalspaces) const{
	while (currNode != 0){
		outputTree( currNode->rightPtr, totalspaces + 5);
		for (int i = 0; i < totalspaces; i++)
			cout << ' ';
		cout << currNode->data << endl;
		currNode = currNode->leftPtr;
		totalspaces += 5;
	}
}

template <class NODETYPE>
TreeNode<NODETYPE> *Tree<NODETYPE>::getRootPtr() const { return rootPtr; }

//*******************************************************************************
//************************|  Class Listnode  |***********************************
//*******************************************************************************

template< class NODETYPE > class List;  // forward declaration

template<class NODETYPE>
class ListNode {
   friend class List< NODETYPE >; // make List a friend
public:
   ListNode( const NODETYPE & );  // constructor
   NODETYPE getData() const;      // return data in the node
private:
   NODETYPE data;                 // data
   ListNode< NODETYPE > *nextPtr; // next node in the list
};

// Constructor
template<class NODETYPE>
ListNode< NODETYPE >::ListNode( const NODETYPE &info )
   : data( info ), nextPtr( 0 ) { }

// Return a copy of the data in the node
template< class NODETYPE >
NODETYPE ListNode< NODETYPE >::getData() const { return data; }

//*******************************************************************************
//************************|    Class List    |***********************************
//*******************************************************************************

template< class NODETYPE >
class List {
public:
   List();      // constructor
   ~List();     // destructor
   void insertAtFront( const NODETYPE & );
   void insertAtBack( const NODETYPE & );
   bool removeFromFront( NODETYPE & );
   bool removeFromBack( NODETYPE & );
   bool isEmpty() const;
   void print() const;
private:
   ListNode< NODETYPE > *firstPtr;  // pointer to first node
   ListNode< NODETYPE > *lastPtr;   // pointer to last node

   // Utility function to allocate a new node
   ListNode< NODETYPE > *getNewNode( const NODETYPE & );
};

// Default constructor
template< class NODETYPE >
List< NODETYPE >::List() : firstPtr( 0 ), lastPtr( 0 ) { }

// Destructor
template< class NODETYPE >
List< NODETYPE >::~List()
{
   if ( !isEmpty() ) {    // List is not empty
      cout << "Destroying nodes ...\n";

      ListNode< NODETYPE > *currentPtr = firstPtr, *tempPtr;

      while ( currentPtr != 0 ) {  // delete remaining nodes
         tempPtr = currentPtr;
         cout << tempPtr->data << '\n';
         currentPtr = currentPtr->nextPtr;
         delete tempPtr;
      }
   }

   cout << "All nodes destroyed\n\n";
}

// Insert a node at the front of the list
template< class NODETYPE >
void List< NODETYPE >::insertAtFront( const NODETYPE &value )
{
   ListNode< NODETYPE > *newPtr = getNewNode( value );

   if ( isEmpty() )  // List is empty
      firstPtr = lastPtr = newPtr;
   else {          // List is not empty
      newPtr->nextPtr = firstPtr;
      firstPtr = newPtr;
   }
}

// Insert a node at the back of the list
template< class NODETYPE >
void List< NODETYPE >::insertAtBack( const NODETYPE &value )
{
   ListNode< NODETYPE > *newPtr = getNewNode( value );

   if ( isEmpty() )  // List is empty
      firstPtr = lastPtr = newPtr;
   else {          // List is not empty
      lastPtr->nextPtr = newPtr;
      lastPtr = newPtr;
   }
}

// Delete a node from the front of the list
template< class NODETYPE >
bool List< NODETYPE >::removeFromFront( NODETYPE &value )
{
   if ( isEmpty() )             // List is empty
      return false;             // delete unsuccessful
   else {
      ListNode< NODETYPE > *tempPtr = firstPtr;

      if ( firstPtr == lastPtr )
         firstPtr = lastPtr = 0;
      else
         firstPtr = firstPtr->nextPtr;

      value = tempPtr->data;  // data being removed
      delete tempPtr;
      return true;            // delete successful
   }
}

// Delete a node from the back of the list
template< class NODETYPE >
bool List< NODETYPE >::removeFromBack( NODETYPE &value )
{
   if ( isEmpty() )
      return false;   // delete unsuccessful
   else {
      ListNode< NODETYPE > *tempPtr = lastPtr;

      if ( firstPtr == lastPtr )
         firstPtr = lastPtr = 0;
      else {
         ListNode< NODETYPE > *currentPtr = firstPtr;

         while ( currentPtr->nextPtr != lastPtr )
            currentPtr = currentPtr->nextPtr;

         lastPtr = currentPtr;
         currentPtr->nextPtr = 0;
      }

      value = tempPtr->data;
      delete tempPtr;
      return true;   // delete successful
   }
}

// Is the List empty?
template< class NODETYPE > 
bool List< NODETYPE >::isEmpty() const 
   { return firstPtr == 0; }

// Return a pointer to a newly allocated node
template< class NODETYPE >
ListNode< NODETYPE > *List< NODETYPE >::getNewNode( 
                                        const NODETYPE &value )
{
   ListNode< NODETYPE > *ptr = 
      new ListNode< NODETYPE >( value );
   assert( ptr != 0 );
   return ptr;
}

// Display the contents of the List
template< class NODETYPE >
void List< NODETYPE >::print() const
{
   if ( isEmpty() ) {
      cout << "The list is empty\n\n";
      return;
   }

   ListNode< NODETYPE > *currentPtr = firstPtr;

   cout << "The list is: ";

   while ( currentPtr != 0 ) {
      cout << currentPtr->data << ' ';
      currentPtr = currentPtr->nextPtr;
   }

   cout << "\n\n";
}

//*******************************************************************************
//************************|   Class Queue    |***********************************
//*******************************************************************************

template< class QUEUETYPE >
class Queue: private List< QUEUETYPE > {
public:
   void enqueue( const QUEUETYPE &d ) { insertAtBack( d ); }
   bool dequeue( QUEUETYPE &d ) 
      { return removeFromFront( d ); }
   bool isQueueEmpty() const { return isEmpty(); }
   void printQueue() const { print(); }
};


// Fig. 15.16: fig15_16.cpp
// Driver to test class Tree

int main()
{
   Tree< int > intTree;
   int intVal;

   cout << "Enter 10 integer values:\n";
   for( int i = 0; i < 10; i++ ) {
      cin >> intVal;
      intTree.insertNode( intVal );
   }

   cout << "\nPreorder traversal\n";
   intTree.preOrderTraversal();

   cout << "\nTree:\n";
   intTree.outputTree(intTree.getRootPtr(), 0);

   
   return 0;
}
