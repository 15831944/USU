#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>

struct polyDistance
{
public:
	polyDistance()
	{
		polyN = 0;
		dist = 0.0;
	}

	void set(int n, double d)
	{
		polyN = n;
		dist = d;
	}

	bool operator<(const polyDistance & right) const 
	{
		return (dist < right.dist);
	}

	polyDistance & operator=(const polyDistance & right)
	{
		polyN = right.polyN;
		dist = right.dist;
		return *this;
	}

	int polyN;
	double dist;
};

typedef int (*compfn)(const void*, const void*);

int compare(struct polyDistance *elem1, struct polyDistance *elem2)
{
  if ( elem1->dist < elem2->dist )
      return -1;

   else if (elem1->dist > elem2->dist )
      return 1;

   else
      return 0;
}


void main()
{


	qsort((void *) &polyList,              // Beginning address of array
	//	nList,                                 // Number of elements in array
	//	sizeof(struct polyDistance),              // Size of each element
	//	(compfn)compare );                  // Pointer to compare function
}