//Mark Salisbury
//marks
//P8265A124.cpp
//CS 1720
/*
CS1720 Assignment 12
A124. Repeat A112 but with templates so the data of your orderedlinkedlist can be of any type. 
*/
#include <iostream.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <math.h>

class complex {
	friend ostream & operator<<(ostream &, const complex &);
public:
	complex(double, double);
	complex();
	bool operator<(const complex &) const;
	double magnitude() const;
	void setComplex(double, double);

private:
	double real;
	double imag;
};

ostream & operator<<(ostream & output, const complex &right){
	output << right.real;
	if (right.imag != 0.0)
		output << (right.imag > 0.0 ? " + " : " - ") 
		       << (right.imag > 0.0 ? right.imag : -1.0 * right.imag) << "i     ";
	return output;
}

complex::complex(double a, double b){
	real = a;
	imag = b;
}

complex::complex(){
	real = 0.0;
	imag = 0.0;
}

bool complex::operator<(const complex &right) const{
	return (this->magnitude() < right.magnitude());
}

double complex::magnitude() const{
	return sqrt(real * real + imag * imag);
}

void complex::setComplex(double r, double i) {
	real = r;
	imag = i;
}

template< class NODETYPE > class List;  // forward declaration
template< class NODETYPE > class OrderedList;

template<class NODETYPE>
class ListNode {
   friend class List< NODETYPE >; // make List a friend
   friend class OrderedList< NODETYPE >;
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
friend class ListNode<NODETYPE>;
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

   cout << "The list is: (forwards) " << endl;

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
		cout << "The list is: (backwards) " << endl << currentPtr->data << ' ';
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

template <class NODETYPE >	
OrderedList<NODETYPE>::OrderedList() : List<NODETYPE>()
{ }

template <class NODETYPE >
OrderedList<NODETYPE>::~OrderedList(){

}

template <class NODETYPE >
void OrderedList<NODETYPE>::insertInOrder( const NODETYPE & value)
{
	ListNode< NODETYPE > *newPtr = getNewNode( value );
	ListNode< NODETYPE > *prevPtr = 0;
	ListNode< NODETYPE > *currPtr = firstPtr;
	bool repeat = true;

	if ( isEmpty() )  // List is empty
		firstPtr = lastPtr = newPtr;
	else {          // List is not empty
		do {
			//if (isLessThan(newPtr->data, currPtr->data, listType ){
			if ( newPtr->data < currPtr->data ){
				newPtr->nextPtr = currPtr;
				if (prevPtr == 0)
					firstPtr = newPtr;
				else
					prevPtr->nextPtr = newPtr;
				repeat = false;
			}
			else
			{
				prevPtr = currPtr;	
				currPtr = currPtr->nextPtr;
			}
			if (currPtr == 0){
				newPtr->nextPtr = 0;
				prevPtr->nextPtr = newPtr;
				lastPtr = newPtr;
				repeat = false;
			}
		}
		while (repeat);
	}
}

template< class T >
void testOrderedList( OrderedList< T > &listObject, const char *type, int nnodes )
{
   cout << "Testing an ordered List of " << nnodes << ' ' << type << "\n\n";

   T value;

   for (int i = 0; i < nnodes; i++){
	   randomValue( value );
		listObject.insertInOrder( value );
   }
   
   listObject.print();
   listObject.printBackwards(listObject.getFirstPtr());
   cout << endl << endl;
}

void randomValue(int & object ){ object = rand() % 100; }
void randomValue(char & object ){ object = char(rand() % 26 + 'a'); }
void randomValue(double & object ){ object = double(rand() % 1000) / 10.0; }
void randomValue(float & object ){ object = float(rand() % 1000) / 10.0; }
void randomValue(complex & object ){ 
	object.setComplex(double(rand() % 100) / 10.0, double(rand() % 100) / 10.0); 
}

void main()
{
	
	OrderedList< int > intList;
	testOrderedList( intList, "int", 20 ); // test intList

	OrderedList< complex > complexList;
	testOrderedList( complexList, "complex numbers", 20 ); // test complex
	
	cout << "Press any key to exit..." << flush;
	while (!kbhit()) { }
  
}
