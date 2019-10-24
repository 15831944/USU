/*****************************************************************************
*
*   File:                sockaddr.h
*   Project:             Parcel Tracker
*   Class:               SocketAddress
*   Version:             1.0
*   Programmer:          Stephen W. Clyde
*   Last Modified:       Nov. 6, 1995
*
*   Modified History:
*
*   Apr. 25, 1995  Initial version
*
*****************************************************************************/

#pragma once

class SocketAddress
{
private:
	CString host;
    UINT port;

public:
	// Constructors
    SocketAddress(void) :
        host("0.0.0.0"),
        port(0) {}
    SocketAddress(const CString h, UINT p = 0) :
        host(h),
        port(p) {}
    SocketAddress(const SocketAddress &orig) :
        host(orig.host),
        port(orig.port) {}

    // Access methods
    const CString& getHost(void) const { return host; }
    UINT getPort(void) const { return port; }
	BOOL isEmpty(void) const
		{ return (host.IsEmpty() && port==0) ? TRUE : FALSE; }

	BOOL operator == (const SocketAddress& s) const
		{ return (host==s.host && port==s.port) ? TRUE : FALSE; }

	// Update methods
	void setHost(const CString& h)
		{ host = h; }
    void setPort(UINT p)
        { port = p; }

// Testing methods
#ifdef TESTING
    static void test1(void);
    static void test2(void);
    static void test3(void);
    static void test4(void);
    static void test5(void);
	static void run_tests(void);
#endif

};
