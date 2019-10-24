//Mark Salisbury
//marks
//P8265A121.cpp
//CS 1720
/*
CS1720 Assignment 12

For these problems put all source code in one .cpp file.

A121. Create a class node with public attributes for a linked-list in which the data is of 
type char. Have your class node have a constructor that will set the pointer to the node to 
NULL or 0. Now, create a class linkedlist that will implement a linked-list of characters 
utilizing the class node. The linked-list should have either private or protected attributes 
head and tail that are pointers to a node and public member functions or behaviors inserth
(insert at head), insertt, removeh, removet, isempty, printht, printth and two friend helper 
functions for printing using recursion. Have your driver program create a linked list of 10
random alphabetic characters and output them to the screen head-tail on one line and tail-head 
on another line. Be sure to have your driver program test all functions.
*/
#include <iostream.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

template< class NODETYPE > class List;  // forward declaration

template<class NODETYPE>
class ListNode {
   friend class List< NODETYPE >; // make List a friend
public:
   ListNode( const NODETYPE & );  // constructor
   NODETYPE getData() const;      // return data in the node
protected:
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
   void printBackwards(ListNode< NODETYPE > *) const;
   ListNode<NODETYPE> * getFirstPtr() const;
protected:
   ListNode< NODETYPE > *firstPtr;  // pointer to first node
   ListNode< NODETYPE > *lastPtr;   // pointer to last node

   // Utility function to allocate a new node
   ListNode< NODETYPE > *getNewNode( const NODETYPE & );
};

template< class NODETYPE >
class OrderedList : public List<NODETYPE> {
public:
   OrderedList();      // constructor
   ~OrderedList();     // destructor
   void insertInOrder( const NODETYPE & );
};

// Default constructor
template< class NODETYPE >
List< NODETYPE >::List() : firstPtr( 0 ), lastPtr( 0 ) { }

// Destructor
template< class NODETYPE >
List< NODETYPE >::~List()
{
   if ( !isEmpty() ) {    // List is not empty
      ListNode< NODETYPE > *currentPtr = firstPtr, *tempPtr;

      while ( currentPtr != 0 ) {  // delete remaining nodes
         tempPtr = currentPtr;
         currentPtr = currentPtr->nextPtr;
         delete tempPtr;
      }
   }

  
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

   cout << "The list is: (forwards) ";

   while ( currentPtr != 0 ) {
      cout << currentPtr->data << ' ';
      currentPtr = currentPtr->nextPtr;
   }

   cout << "\n\n";
}

template< class NODETYPE >
void List< NODETYPE >::printBackwards(ListNode< NODETYPE > *currentPtr) const
{
   if (currentPtr->nextPtr == 0){
		cout << "The list is: (backwards) " << currentPtr->data << ' ';
   }
   else
   {
	   printBackwards(currentPtr->nextPtr);
	   cout << currentPtr->data << ' ';
   }

}

template< class NODETYPE >
ListNode<NODETYPE> * List< NODETYPE>::getFirstPtr() const
{
	return firstPtr;
}

template< class T >
void testList( List< T > &listObject, const char *type, int nnodes)
{
   cout << "Testing a List of " << type << " values\n\n";

   T value;

   for (int i = 0; i < nnodes; i++){
	   randomValue(value);
		listObject.insertAtFront( value );
   }
   
   listObject.print();
   listObject.printBackwards(listObject.getFirstPtr());
   cout << endl << endl;
}


void randomValue(char & object ){ object = char(rand() % 26 + 'a'); }


void main()
{
   List< char > charList;
   testList( charList, "char", 10 ); // test charList

   cout << "Press any key to exit..." << flush;
   while (!kbhit()) { }
  
}
