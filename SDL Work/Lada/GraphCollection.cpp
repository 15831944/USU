// GraphCollection.cpp: implementation of the CGraphCollection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lada control module.h"
#include "GraphCollection.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern COLORREF DefaultColor[15];
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGraphCollection::CGraphCollection(BOOL CreateNew)
{
	if (CreateNew)
	{
		whichPane = -1; // this collection is not in any pane initially
		nItems = 0;
		for (int i = 0; i < 15; i++)
		{
			DataIndex[i] = i;
			isItemChecked[i] = TRUE;
		}
		name = "No name";
	}
}

CGraphCollection::~CGraphCollection()
{

}

CGraphCollection & CGraphCollection::operator=(const CGraphCollection & right)
{

	whichPane = right.whichPane;
	nItems = right.nItems;
	memcpy(DataIndex,right.DataIndex,sizeof(int)*15);
	memcpy(isItemChecked,right.isItemChecked,sizeof(BOOL)*15);
	name = right.name;
	return *this;

}

CGraphCollection::ReadObject(CArchive & ar)
{
	ar.Read(&whichPane,sizeof(int));
	ar.Read(&nItems,sizeof(int));
	ar.Read(DataIndex,sizeof(int)*15);
	ar.Read(isItemChecked,sizeof(BOOL)*15);
	ar.ReadString(name);
}

CGraphCollection::WriteObject(CArchive & ar)
{
	ar.Write(&whichPane,sizeof(int));
	ar.Write(&nItems,sizeof(int));
	ar.Write(DataIndex,sizeof(int)*15);
	ar.Write(isItemChecked,sizeof(BOOL)*15);
	ar.WriteString(name+"\n");
}
