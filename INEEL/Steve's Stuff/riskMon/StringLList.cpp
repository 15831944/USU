// StringLList.cpp: implementation of the CStringLList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "mfcTest.h"
#include "StringLList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStringLList::CStringLList()
{
	head=NULL;
	total=0;
	tail = NULL;
}

CStringLList::~CStringLList()
{
	Node * temp = head;
	while(head != NULL)
	{
		temp=head;
		head=head->next;
		delete temp;
	}
	

}

CStringLList::CStringLList(CStringLList & newLL)
{
	head=NULL;
	total=0;
	if(newLL.head == NULL)
		return;
	head = new Node;
	head->item=newLL.head->item;
	head->next=NULL;
	++total; 
	
	
	Node * newCurr = newLL.head;
	Node * curr =head;
	
	while(newCurr->next != NULL)
	{
		++total;
		newCurr=newCurr->next;
		curr->next=new Node;
		curr = curr->next;
		curr->item = newCurr->item;
		curr->next = NULL;		
	}

}

double CStringLList::Pop(CString &ret)
{
	if(head==NULL)
		return -1;
	double retVal = head->riskLev;
	Node* curr=head;
	//CString ret;  //the Cstring to be returned 
	ret=head->item;
	head=head->next;
	--total;
	delete curr;
	return retVal;
}

void CStringLList::Push(CString newCString, double Lev)
{
	if(tail == NULL)
	{
		tail = new Node;
		tail->next = NULL;
		tail->item = newCString;
		tail->riskLev = Lev;
		head = tail;
		++total;
	}
	else
	{
		tail->next = new Node;
		tail = tail->next;
		tail->next = NULL;
		tail->item = newCString;
		tail->riskLev = Lev;
		++total;
	}
	//curr = new Node;
	//curr->item = newCString;
	//curr->next = head;
	//curr->riskLev = Lev;
	//++total;
	//	head=curr;


}

int CStringLList::Count()
{
	return total;

}

void CStringLList::Delete()
{
	Node * temp = head;
	while(head != NULL)
	{
		temp=head;
		head=head->next;
		delete temp;
	}
}
