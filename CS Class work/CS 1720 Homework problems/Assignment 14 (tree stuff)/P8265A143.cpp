//Mark Salisbury
//marks
//P8265A143.cpp
//CS 1720
/*
CS1720 Assignment 14

Put code for each program in one file and turn in the .cpp. 

A143. (Tree Sort) If the data in an array is transferred to a binary search tree 
(BST) one element at a time and then the data from the BST is placed back into the 
array using an inorder traversal of the BST, the data will be sorted in ascending order. 

For this program, create an array of 100 random doubles, print the array, 10 numbers per 
line,  create a function treesort that will call the BST insert function to insert the 
array elements into a BST and then place the elements back into the array in sorted
order using an inorder traversal of the BST. Print the sorted array, 10 numbers per 
line. Use template functions so your code will function with any data type.
*/

#include <iostream.h>
#include <iomanip.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>

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
   bool insertNode( const NODETYPE & );
   void preOrderTraversal() const;
   void inOrderTraversal() const;
   void postOrderTraversal() const;
   void levelOrderTraversal() const;
   void outputTree(TreeNode<NODETYPE> *, int ) const;
   TreeNode<NODETYPE> *getRootPtr() const;
   void inOrderSortHelper( TreeNode< NODETYPE > *, NODETYPE [], int) const;
private:
   TreeNode< NODETYPE > *rootPtr;

   // utility functions
   bool insertNodeHelper( 
           TreeNode< NODETYPE > **, const NODETYPE & );
   void preOrderHelper( TreeNode< NODETYPE > * ) const;
   void inOrderHelper( TreeNode< NODETYPE > * ) const;
   
   void postOrderHelper( TreeNode< NODETYPE > * ) const;
};

template< class NODETYPE >
Tree< NODETYPE >::Tree() { rootPtr = 0; }

template< class NODETYPE >
bool Tree< NODETYPE >::insertNode( const NODETYPE &value )
   { return insertNodeHelper( &rootPtr, value ); }

// This function receives a pointer to a pointer so the
// pointer can be modified.
template< class NODETYPE >
bool Tree< NODETYPE >::insertNodeHelper( 
        TreeNode< NODETYPE > **ptr, const NODETYPE &value )
{
   if ( *ptr == 0 ) {                   // tree is empty
      *ptr = new TreeNode< NODETYPE >( value );
      assert( *ptr != 0 );
   }
   else                              // tree is not empty
      if ( value < ( *ptr )->data )
         return insertNodeHelper( &( ( *ptr )->leftPtr ), value );
      else
         if ( value > ( *ptr )->data )
            return insertNodeHelper( &( ( *ptr )->rightPtr ), value );
         else
            return false;
	return true;
}

template< class NODETYPE >
void Tree< NODETYPE >::inOrderSortHelper( TreeNode< NODETYPE > *ptr, NODETYPE array[],
										 int n) const
{
	static int position = 0;
   if ( ptr != 0 ) {
      inOrderSortHelper( ptr->leftPtr, array, n);
      if (position < n)
		  array[position++] = ptr->data;
      inOrderSortHelper( ptr->rightPtr, array, n );
   }
}


template <class NODETYPE>
TreeNode<NODETYPE> *Tree<NODETYPE>::getRootPtr() const { return rootPtr; }

template <class T>
void treesort(T array[], int n){
	Tree<T> sorttree;
	for (int i = 0; i < n; i++)
		sorttree.insertNode(array[i]);

	sorttree.inOrderSortHelper( sorttree.getRootPtr(), array, n);
	
}

void main()
{
   double randDoubles[100];
   double randDouble;
   int totalDoubles = 0;
	Tree<double> doubleTree;

	srand(time(0));

   while (totalDoubles < 100){
	   randDouble = rand() % 100 + double(rand() % 10) / 10;
	   if (doubleTree.insertNode(randDouble)){ // if it was not a duplicate
		   randDoubles[totalDoubles] = randDouble;
		   totalDoubles++;
	   }
   }

   cout << "100 random doubles: " << endl;
   for (int i = 1; i <= 100; i++)
	   cout << randDoubles[i - 1] << '\t';
   treesort(randDoubles, 100);
   cout << "100 sorted doubles: " << endl;
   for (i = 1; i <= 100; i++)
	   cout << randDoubles[i - 1] << '\t';
	  
}
