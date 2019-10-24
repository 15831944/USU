// This is Version 1.0 PLEASE DOCUMENT CHANGES
// Checkout.h: interface for the CCheckout class.
//
//////////////////////////////////////////////////////////////////////


// This class is used to store, display, and output to a file, the information gathered from Checkout

#if !defined(AFX_CHECKOUT_H__FA75F391_B7EC_11D4_98EE_00A076801ACD__INCLUDED_)
#define AFX_CHECKOUT_H__FA75F391_B7EC_11D4_98EE_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <fstream.h>

class CCheckout  
{
public:
	void output(ofstream fou);  // This function outputs the data to a file
	CCheckout();				// This function sets into the array what data is being collected 
	CString data[51][3];		// data stores the data that is gathered during checkout with the proper names
	CString units[51];			// units stores the units used in the data gathered
	virtual ~CCheckout();		// Destructor

};

#endif // !defined(AFX_CHECKOUT_H__FA75F391_B7EC_11D4_98EE_00A076801ACD__INCLUDED_)
