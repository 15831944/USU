/*****************************************************************************
*
*  File:          PersistentObjectSet.h
*  Class:         PersistentObjectSet
*  Version:       1.0
*  Project:       Distributed Calendar System
*  Author:        Stephen W. Clyde
*  Last Modified: September 5, 2001
*
*  Modification History:
*  	Sep. 5, 2001	Initial version
*
*  Description:
*     An event object represents something on someone's calender.
*/

#pragma once

#include <afx.h>
#include <iostream.h>
#include "DString.h"
#include "Marshall.h"

template <class X>
class PersistentObjectSet
{
private:
	CPtrArray	obj_set;
	int			count;
	int			next_blank;
	int			max_idx;

public:
	PersistentObjectSet(int size=100, int grow_by=50) :
		obj_set(), count(0), next_blank(0), max_idx(0)
		{ obj_set.SetSize(size, grow_by); }

	~PersistentObjectSet() { removeAll(); }

	int getMaxId(void) const { return max_idx; }
	X* getAt(int idx) const
		{
			X* result=NULL;
			if (idx>=0 && idx<=getMaxId())
				result = (X*) obj_set.GetAt(idx);
			return result;
		}
	X* operator [](int idx) const { return getAt(idx); }

	int add(X* obj)
		{
			int idx = -1;

			if (obj!=NULL)
			{
				idx = obj->getId();
				if (idx<0)
					idx = next_blank;
				else
					removeAt(idx);
				count++;
				obj_set.SetAtGrow(idx, obj);
				while (next_blank<=getMaxId() &&
						obj_set.GetAt(next_blank)!=NULL) next_blank++;
				if (idx>=max_idx) max_idx=idx+1;
			}

			return idx;
		}

	X* create(void)
		{
			X* new_obj= new X;
			int idx = add(new_obj);
			new_obj->setId(idx);
			return new_obj;
		}

	void removeAt(int idx)
		{
			if (idx>=0 && idx<=getMaxId())
			{
				X* tmp = getAt(idx);
				if (tmp!=NULL)
				{
					delete tmp;
					obj_set.SetAt(idx,NULL);
					count--;
					if (idx<next_blank) next_blank=idx;
				}
				while (max_idx>0 && getAt(max_idx-1)==NULL)
					max_idx--;
			}
		}

	void removeAll(void)
		{
			for (int idx=0; idx<max_idx; idx++)
				removeAt(idx);
			obj_set.RemoveAll();
			next_blank=0;
			max_idx=0;
			count=0;
		}

	void save(ostream &out)
	{
		char num[sizeof(long)];

		char *tmp;
		char *ptr;
		char *end_ptr;
		unsigned short lng;

		if (out.good())
		{
			// write out maximum id
			ptr = num;
			end_ptr = ptr + sizeof(int);
			marshall(ptr, end_ptr, max_idx);
			out.write(num, sizeof(int));
			ptr = num;
			end_ptr = ptr + sizeof(int);
			marshall(ptr, end_ptr, count);
			out.write(num, sizeof(int));

			for (int idx=0; idx<max_idx && out.good(); idx++)
			{
				X* obj = getAt(idx);
				if (obj)
				{
					lng = obj->getPackLng();
					ptr = num;
					end_ptr = ptr + sizeof(unsigned short);
					marshall(ptr, end_ptr, lng);
					out.write(num, sizeof(unsigned short));
					tmp = new char[lng];
					obj->save(tmp, lng);
					out.write(tmp, lng);
					delete tmp;
				}
			}
		}
	}

	void load(istream &in)
	{
		char num[sizeof(long)];
		char *tmp;
		char *ptr;
		char *end_ptr;
		unsigned short lng;

		if (in.good())
		{
			in.read(num, sizeof(int));
			ptr = num;
			end_ptr = ptr + sizeof(int);
			unmarshall(ptr, end_ptr, max_idx);
			in.read(num, sizeof(int));
			ptr = num;
			end_ptr = ptr + sizeof(int);
			unmarshall(ptr, end_ptr, count);
			for (int i=0; i<count && in.good() && in.peek()!=EOF; i++)
			{
				in.read(num, sizeof(unsigned short));
				ptr = num;
				end_ptr = ptr + sizeof(unsigned short);
				unmarshall(ptr, end_ptr, lng);
				tmp = new char[lng];
				in.read(tmp, lng);
				add(new X(tmp, lng));
				delete tmp;
			}
		}

	}

#ifdef TESTING
	friend void PersistentObjectSet_test1(void);
	friend void PersistentObjectSet_test2(void);
	friend void PersistentObjectSet_test3(void);
	friend void PersistentObjectSet_test4(void);
	friend void PersistentObjectSet_test5(void);
	void PersistentObjectSet_run_tests(void);
#endif

};

#ifdef TESTING
	void PersistentObjectSet_run_tests(void);
#endif
