//Mark Salisbury
//marks
//P8265A134.cpp
//CS 1720
/*
CS1720 Assignment 13
A134. Evaluate Postfix. Do Problem 15.13 from your text. Put all code in one file and turn 
in the .cpp.
*/

#include <iostream.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <math.h>


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


template< class NODETYPE >
class List {
public:
   List();      // constructor
   ~List();     // destructor
   void insertAtFront( const NODETYPE & );
   void insertAtBack( const NODETYPE & );
   bool removeFromFront( NODETYPE & );
   bool removeFromBack( NODETYPE & );
   ListNode<NODETYPE> * searchList( ListNode<NODETYPE> *, NODETYPE & );
   ListNode<NODETYPE> * getFirstPtr() { return firstPtr; }
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

template< class NODETYPE >
ListNode<NODETYPE> *List< NODETYPE >::searchList( ListNode<NODETYPE> *whichNode, NODETYPE &value )
{
	if (whichNode == 0)
		return 0;
	else if (whichNode->data == value)
		return whichNode;
	else
		whichNode = searchList(whichNode->nextPtr, value);
	return whichNode;
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
	return;
   }

   ListNode< NODETYPE > *currentPtr = firstPtr;

   cout << "The list is: " << endl;

   while ( currentPtr != 0 ) {
      cout << currentPtr->data << '\t';
      currentPtr = currentPtr->nextPtr;
   }

   cout << "\n\n";
}

template< class STACKTYPE >
class Stack : private List< STACKTYPE > {
public:
   void push( const STACKTYPE &d ) { insertAtFront( d ); }
   bool pop( STACKTYPE &d ) { return removeFromFront( d ); }
   bool isStackEmpty() const { return isEmpty(); }
   void printStack() const { print(); }
   Stack & operator=(const Stack<STACKTYPE> & );
};

/*
template <class STACKTYPE >
Stack & Stack::operator=( const Stack<STACKTYPE> &right){
	if (&right != this){
		STACKTYPE a;
		this->~List();
		this = new Stack<STACKTYPE>();
		while (right.pop(a))
			this->push(a);
	}
	return *this;
}
*/

bool checkPalindrome( char *word ){
	Stack< char > charStack;
	char popChar;
	for (int i = 0; word[i] != '\0'; i++)
		charStack.push(word[i]);
	for (i = 0; word[i] != '\0'; i++){
		charStack.pop(popChar);
		if (popChar != word[i])
			return false;
	}
	return true;
}
void main()
{
	char buff[21];
	cout << "Enter an expression in post-fix notation: " << endl
		 << "Keep in mind this program can only accept " << endl
		 << "values from 1-9.  Valid operators are +,  " << endl
		 << "-, *, /, ^, and %.  However, all result   " << endl
		 << "will be truncated.  For example, 3 / 2    " << endl
		 << "evaluates to 1.                           " << endl;
	cin.getline(buff, 20);
	
	Stack< int > expression;
	int x, y, result = 0;

	for (int i = 0; buff[i] != '\0'; i++){
		if (isdigit(buff[i])){
			expression.push(buff[i] - '0');
		}
		else if(buff[i] == '+' || buff[i] == '-' || buff[i] == '*' || 
			buff[i] == '/' || buff[i] == '^' || buff[i] == '%' ){
			expression.pop(x);
			expression.pop(y);
			switch (buff[i]){
			case '+': result = y + x; break;
			case '-': result = y - x; break;
			case '*': result = y * x; break;
			case '\\': result = y / x; break;
			case '^': result = pow(y, x); break;
			case '%': result = y % x; break;
			}
			expression.push(result);
		}
	}
	expression.pop(result);
	cout << "The expression evaluates to: " << result << endl;

}
      
   




