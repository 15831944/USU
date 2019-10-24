// TreeListLL.cpp: implementation of the TreeListLL class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RiskMon.h"
#include "TreeListLL.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TreeListLL::TreeListLL()
{
	head=NULL;
	total=0;
}

TreeListLL::~TreeListLL()
{
	TLNode * temp = head;
	while(head != NULL)
	{
		temp=head;
		head=head->next;
		delete temp->BENames;
		delete temp->TreeName;
		delete temp;
	}

}

//Adds a list of a trees basic events pass in the tree name, nuber of basic events and a array of basic events
void TreeListLL::Push(char *treeName,int size, newNames)
{
	TLNode * curr;
	curr = new TLNode;
	curr->TreeName = new char[24];
	memcpy(TreeName, treeName, 24);
	curr->BENames = new char[size][24];
	//make a copy of the array 
	memcpy(curr->BENames, newNames, (size * 24));
	curr->Length = size;
	curr->next = head;
	++total;
	head=curr;
}

//returns the nuber of trees that are in the linked list
int TreeListLL::Count()
{
	return total;

}

//returns true if the specified tree is in the TreeList Linked List
bool TreeListLL::GetList(char * treeName, char * list)
{
	//turn the char array treeName into a CString for comparison
	CString curTName = treeName;

	int num;
	num = Count();  //the number of trees in the linked list
	
	TLNode *curr;
	//try and find the tree name in the linked list
	for(int i=0; ((i < num) && curr != NULL; ++i)
		curr = cur->Next;
	if(curr->TreeName != curTName) 
	{
		list = new char[curr->Length][24];
		memcpy(list, curr->TreeName, (curr->Length * 24));
		return true;
	}
	else
		return false;
}

