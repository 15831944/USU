// ArrayListLL.cpp: implementation of the ArrayListLL class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RiskMon.h"
#include "ArrayListLL.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//typedef NAME24 = char[24];
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ArrayListLL::ArrayListLL()
{
	Head=NULL;
	Total=0;
	DesiredNode =NULL;
	
}

ArrayListLL::~ArrayListLL()
{
	ALNode * temp = Head;
	while(Head != NULL)
	{
		temp=Head;
		Head=Head->Next;
		delete [] (temp->BENames);
		delete [] (temp->DescOfBEs);
		delete [] (temp->CompGroups);
		delete temp;
	}

}




//Adds a list of a trees basic events pass in the tree name, nuber of basic events and a array of basic events
void ArrayListLL::Push(char *arrayName,char * arraydesc, int size, char (*newNames)[25], char (*newDesc)[61])
{
	ALNode * curr;
	curr = new ALNode;
	curr->Next = Head;
	curr->ArrayName = arrayName;
	curr->ArrayDesc = arraydesc;
	curr->CompGroups = new char[size][25];
	curr->Group = new int[size];
	curr->Length = size;
	++Total;
	curr->BENames = newNames;
	curr->DescOfBEs = newDesc;
	Head=curr;
	DesiredNode = Head;
	
	
	//Add the group the BeName goes with
	//if a group doesn't exist add one
	CString tempName;
	int loc=0;
	int loc2 =0;
	for(int i =0; i<size; ++i)
	{
		
		tempName = newNames[i];
		loc = tempName.Find( '-');
		tempName = tempName.Mid(loc, tempName.GetLength() - loc);
		loc = tempName.Find('-');
		loc2 = tempName.Find('-', (loc+1));
		tempName = tempName.Delete('-', loc2-loc);
		if(tempName == NULL)
			DesiredNode->Group[i] = -1;
		else
		{
			int compGroupId = CompBEGroupExists(tempName);
			if(compGroupId = -1)
				//create a new Base Component group and add that group id to the Basic event
			{
				
				memcpy(DesiredNode->CompGroups[DesiredNode->NumOfCompGroups], tempName, 25);
				++(DesiredNode->NumOfCompGroups);
				DesiredNode->Group[i]=DesiredNode->NumOfCompGroups;

			}
			else //just add the group id to that component
			{
				DesiredNode->Group[i] =  compGroupId;

			}
		}
	}
}

//returns the nuber of trees that are in the linked list
int ArrayListLL::Count()
{
	return Total;

}



int ArrayListLL::NodeSize(char *arrayName)
{
	CString curAName = arrayName;
	ALNode *curr;
	curr = Head;
	for(int i=0; (i < Total) && (curr != NULL); ++i)
	{
		
		if(curr->ArrayName == curAName) 
			return curr->Length;
		curr = curr->Next;
	}	
	return -1;
}

bool ArrayListLL::SetLook(char *arrayName)
{
	ALNode *curr;
	CString curAName = arrayName;
	if((DesiredNode != NULL) && (DesiredNode->ArrayName != curAName))
	{
		curr = Head;
		for(int i=0; (i < Total) && (curr != NULL); ++i)
		{
			
			if(curr->ArrayName == curAName)
			{
				DesiredNode = curr;
				return true;
			}
			curr = curr->Next;
			
		}	
		return false;
	}
	if(DesiredNode == NULL)
	{
		
		curr = Head;
		for(int i=0; (i < Total) && (curr != NULL); ++i)
		{
			
			if(curr->ArrayName == curAName)
			{
				DesiredNode = curr;
				return true;
			}
			curr = curr->Next;
		}	
		return false;
	}

	
	return true;
}

bool ArrayListLL::Exists(char *arrayName)
{
	CString curAName = arrayName;
	ALNode *curr;
	curr = Head;
	for(int i=0; (i < Total) && (curr != NULL); ++i)
	{
		
		if(curr->ArrayName == curAName) 
			return true;
		curr = curr->Next;
	}	
	return false;
}

//fills the char * with the name in the name array by the given index
//SetLook must be called first in order to be in the correct node 
bool ArrayListLL::GetBEName(int index, char *beName, char *beDesc, int bCompAssosiation)
{	
	if(DesiredNode == NULL)
		return false;
	
	else
	{
		
		memcpy(beDesc, DesiredNode->DescOfBEs[index], 61);
		beDesc[61] = '\0';
		memcpy(beName, DesiredNode->BENames[index] , 25);
		beName[25] = '\0';
		return true;
	}


}

void ArrayListLL::Delete()
{
	ALNode * temp = Head;
	while(Head != NULL)
	{
		temp=Head;
		Head=Head->Next;
		delete [] (temp->BENames);
		delete [] (temp->DescOfBEs);
		delete temp;
	}

}

//returns a -1 if not found and an index if it does exist
int ArrayListLL::CompBEGroupExists(CString name)
{
	CString tempName;
	CString CompName;
	tempName = name;
	for(int i =0; i<DesiredNode->NumOfCompGroups; ++i)
	{
		CompName= DesiredNode->CompGroups[i];
		if(CompName == tempName)
			return i;
	}
	return -1;
}

bool ArrayListLL::GetCompBEGroupName(int, char *name)
{
	CString tempName = name;
	for(int i =0; i<DesiredNode->NumOfCompGroups; ++i)
	{
		if(DesiredNode->CompGroups[i] == tempName)
		{
			memcpy(name, DesiredNode->CompGroups[i], 25);
			return true;
		}
	}
	return false;
}

int ArrayListLL::GetNumOfCompBEGroups()
{
	return DesiredNode->NumOfCompGroups;
}
