/*****************************************************************************
*
*	File:          PersistentObjectSet.cpp
*	Class:         PersistnetObjectSet
*	Version:       1.0
*	Project:       Distributed Calendar System
*	Author:        Stephen W. Clyde
*	Last Modified: September 5, 2001
*
*	Modification History:
*
*  	Sep. 5, 2001	Initial version
*
*	Description:
*
*	This file contains test cases for the PersistentObjectSet template
*
*/

#include "stdafx.h"
#include <stdlib.h>
#include <fstream.h>
#include "../common/PersistentObject.h"
#include "../common/PersistentObjectSet.h"

#ifdef TESTING
#include "../TestPackage/TestPackage.h"
#include "../common/Building.h"

/*****************************************************************************
*
*   Test cases
*
*/

#include <iostream.h>
#include <fstream.h>
#include <assert.h>

// Test 1 - Constructor, create, and getMaxId methods
void PersistentObjectSet_test1(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	PersistentObjectSet<Building> bs;
	assert(bs.getMaxId()==0);
	assert(bs.next_blank==0);

	Building *b1 = bs.create();
	b1->setName("Old Main");
	b1->setAddress("Old Main Hill");
	b1->setCity("Logan");
	b1->setState("UT");
	b1->setZip("84322");

	assert(bs.getMaxId()==1);
	assert(bs[0]==b1);
	assert(b1->getId()==0);
	assert(b1->getValid()==TRUE);

	Building *b2 = bs.create();
	b2->setName("SER");
	b2->setAddress("USU Campus");
	b2->setCity("Logan");
	b2->setState("UT");
	b2->setZip("84322");

	assert(bs.getMaxId()==2);
	assert(bs[1]==b2);
	assert(b2->getId()==1);
	assert(b2->getValid()==TRUE);

	app->DisplayMessage("PersistentObjectSet Test 1 complete\r\n");
}

// Test 2 - test add, getAt, and removeAt methods and [] operator
void PersistentObjectSet_test2(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	PersistentObjectSet<Building> bs;
	assert(bs.getMaxId()==0);
	assert(bs.next_blank==0);
	assert(bs.count==0);

	Building *b1 = bs.create();
	assert(bs.getMaxId()==1);
	assert(bs[0]==b1);
	assert(b1->getId()==0);
	assert(b1->getValid()==TRUE);
	assert(bs.next_blank==1);
	assert(bs.count==1);

	Building *b2 = bs.create();
	assert(bs.getMaxId()==2);
	assert(bs[1]==b2);
	assert(b2->getId()==1);
	assert(b2->getValid()==TRUE);
	assert(bs.next_blank==2);
	assert(bs.count==2);

	Building *b3 = bs.create();
	assert(bs.getMaxId()==3);
	assert(bs[2]==b3);
	assert(b3->getId()==2);
	assert(b3->getValid()==TRUE);
	assert(bs.count==3);

	assert(bs.getAt(-1)==NULL);
	assert(bs.getAt(0)==b1);
	assert(bs.getAt(1)==b2);
	assert(bs.getAt(2)==b3);
	assert(bs.getAt(3)==NULL);
	assert(bs.next_blank==3);

	bs.removeAt(1);
	assert(bs.getAt(-1)==NULL);
	assert(bs.getAt(0)==b1);
	assert(bs.getAt(1)==NULL);
	assert(bs.getAt(2)==b3);
	assert(bs.getAt(3)==NULL);
	assert(bs.next_blank==1);
	assert(bs.count==2);

	bs.removeAt(-1);
	assert(bs.getAt(-1)==NULL);
	assert(bs.getAt(0)==b1);
	assert(bs.getAt(1)==NULL);
	assert(bs.getAt(2)==b3);
	assert(bs.getAt(3)==NULL);
	assert(bs.next_blank==1);
	assert(bs.count==2);

	bs.removeAt(3);
	assert(bs.getAt(-1)==NULL);
	assert(bs.getAt(0)==b1);
	assert(bs.getAt(1)==NULL);
	assert(bs.getAt(2)==b3);
	assert(bs.getAt(3)==NULL);
	assert(bs.next_blank==1);
	assert(bs.count==2);

	bs.removeAt(4);
	assert(bs.getAt(-1)==NULL);
	assert(bs.getAt(0)==b1);
	assert(bs.getAt(1)==NULL);
	assert(bs.getAt(2)==b3);
	assert(bs.getAt(3)==NULL);
	assert(bs.next_blank==1);
	assert(bs.count==2);

	Building *b4 = bs.create();
	assert(bs.getMaxId()==3);
	assert(b4->getId()==1);
	assert(b4->getValid()==TRUE);
	assert(bs.count==3);

	assert(bs.getAt(-1)==NULL);
	assert(bs.getAt(0)==b1);
	assert(bs.getAt(1)==b4);
	assert(bs.getAt(2)==b3);
	assert(bs.getAt(3)==NULL);
	assert(bs.next_blank==3);

	Building *b5 = new Building;
	b5->setId(1);

	bs.add(b5);
	assert(bs.getAt(-1)==NULL);
	assert(bs.getAt(0)==b1);
	assert(bs.getAt(1)==b5);
	assert(bs.getAt(2)==b3);
	assert(bs.getAt(3)==NULL);
	assert(bs.next_blank==3);

	bs.removeAt(2);
	assert(bs.getAt(-1)==NULL);
	assert(bs.getAt(0)==b1);
	assert(bs.getAt(1)==b5);
	assert(bs.getAt(2)==NULL);
	assert(bs.getAt(3)==NULL);
	assert(bs.next_blank==2);
	assert(bs.max_idx==2);

	bs.removeAt(0);
	bs.removeAt(1);
	assert(bs.getAt(-1)==NULL);
	assert(bs.getAt(0)==NULL);
	assert(bs.getAt(1)==NULL);
	assert(bs.getAt(2)==NULL);
	assert(bs.getAt(3)==NULL);
	assert(bs.next_blank==0);
	assert(bs.max_idx==0);

	app->DisplayMessage("PersistentObjectSet Test 2 complete\r\n");
}

// Test 3 - Load and save methods
void PersistentObjectSet_test3(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();


	PersistentObjectSet<Building> bs;
	Building *b1 = bs.create();
	b1->setName("Old Main");
	b1->setAddress("Old Main Hill");
	b1->setCity("Logan");
	b1->setState("UT");
	b1->setZip("84322");
	assert(bs.count==1);

	Building *b2 = bs.create();
	b2->setName("SER");
	b2->setAddress("USU Campus");
	b2->setCity("Logan");
	b2->setState("UT");
	b2->setZip("84322");
	assert(bs.count==2);

	Building *b3 = bs.create();
	b3->setName("TMC");
	b3->setAddress("USU Campus");
	b3->setCity("Logan");
	b3->setState("UT");
	b3->setZip("84322");
	assert(bs.count==3);

	Building *b4 = bs.create();
	b4->setName("Merril Library");
	b4->setAddress("USU Campus");
	b4->setCity("Logan");
	b4->setState("UT");
	b4->setZip("84322");
	assert(bs.count==4);

	Building *b5 = bs.create();
	b5->setName("Aminal Scnience");
	b5->setAddress("USU Campus");
	b5->setCity("Logan");
	b5->setState("UT");
	b5->setZip("84322");
	assert(bs.count==5);

	bs.removeAt(3);
	assert(bs.count==4);

	assert(bs.getAt(-1)==NULL);
	assert(bs.getAt(0)==b1);
	assert(bs.getAt(1)==b2);
	assert(bs.getAt(2)==b3);
	assert(bs.getAt(3)==NULL);
	assert(bs.getAt(4)==b5);
	assert(bs.getAt(5)==NULL);
	assert(bs.next_blank==3);

    ofstream out("test.dat");
	assert(out.good()==TRUE);
	bs.save(out);
	out.close();

	ifstream in("test.dat");
	assert(in.good()==TRUE);

	PersistentObjectSet<Building> bs1;
	bs1.load(in);

	assert(bs1.max_idx==bs.max_idx);
	assert(bs1.count==bs1.count);

	b1 = bs1.getAt(0);
	assert(b1->getName()=="Old Main");
	assert(b1->getAddress()=="Old Main Hill");
	assert(b1->getCity()=="Logan");
	assert(b1->getState()=="UT");
	assert(b1->getZip()=="84322");

	b2 = bs1.getAt(1);
	assert(b2->getName()=="SER");
	assert(b2->getAddress()=="USU Campus");
	assert(b2->getCity()=="Logan");
	assert(b2->getState()=="UT");
	assert(b2->getZip()=="84322");

	b3 = bs1.getAt(2);
	assert(b3->getName()=="TMC");
	assert(b3->getAddress()=="USU Campus");
	assert(b3->getCity()=="Logan");
	assert(b3->getState()=="UT");
	assert(b3->getZip()=="84322");

	b4 = bs1.getAt(3);
	assert(b4==NULL);

	b5 = bs1.getAt(4);
	assert(b5->getName()=="Aminal Scnience");
	assert(b5->getAddress()=="USU Campus");
	assert(b5->getCity()=="Logan");
	assert(b5->getState()=="UT");
	assert(b5->getZip()=="84322");

	app->DisplayMessage("PersistentObjectSet Test 3 complete\r\n");
}

// Test 4 - Unused
void PersistentObjectSet_test4(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	app->DisplayMessage("PersistentObjectSet Test 4 complete\r\n");
}

// Test 5 - Unused
void PersistentObjectSet_test5(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	app->DisplayMessage("PersistentObjectSet Test 4 complete\r\n");
}

// Test case Dispatcher
void PersistentObjectSet_run_tests(void)
{
	PersistentObjectSet_test1();
	PersistentObjectSet_test2();
	PersistentObjectSet_test3();
	PersistentObjectSet_test4();
	PersistentObjectSet_test4();
}

#endif