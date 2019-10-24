//////////////////////////////////////////////////////////////////////////////
//
//  File:          Request.h
//  Class:         All Request Class
//  Project:       DCS
//  Author:        Stephen W. Clyde
//  Last Modified: October 31, 2001
//
//  Modification History:
//     Oct 31, 2001		Initial Version
//
//  Description:
//     A Request object represents a command from the client to the server
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "DString.h"
#include "sockaddr.h"
#include "Message.h"

/****************************************************************************
*
*   Request
*
*   This is an abstract base class for all types of requests.  It encapsulates
*   address, type and status information.  For clients, a request object
*   represents something they want to send to a server.  In this case, the address
*   is a server address.  For servers, a request object represents something
*   received from a client.  For them, the address data member contains the address
*   of the client that sent the request.
*/
class Request : public RequestReply
{
public:
    typedef enum { UNKNOWN='U', LOGIN='L', DATA='D', SCHEDULING='S', QUERY='Q', TERMINATE='T' } REQUEST_TYPE;
    typedef enum { BAD, NOT_DONE, SUCCESS, FAILURE } STATUS;

private:
    REQUEST_TYPE	request_type;
	SocketAddress	reply_to_addr;
    STATUS          status; 

public:
    // Constructor
    Request(void) :
		RequestReply(RequestReply::REQUEST),
        request_type(UNKNOWN),
        status(NOT_DONE) {}
    Request(REQUEST_TYPE t) :
		RequestReply(RequestReply::REQUEST),
        request_type(t),
        status(NOT_DONE) {}
    Request(REQUEST_TYPE t, const SocketAddress& addr) :
		RequestReply(RequestReply::REQUEST),
        request_type(t),
		reply_to_addr(addr),
        status(NOT_DONE) {}

	// Destructor
    virtual ~Request() {}

    // Access functions
    REQUEST_TYPE getRequestType(void) const { return request_type; } 
	const SocketAddress& getReplyTo(void) const { return reply_to_addr; }
    STATUS getStatus(void) const { return status; }

    // Update functions
	void setReplyTo(const SocketAddress& addr) { reply_to_addr=addr; }

    // process function
    virtual BOOL process(unsigned long request_id) = 0;

	// Factory method
	static Request* create(const Message& msg, const SocketAddress& addr);

protected:
    void setStatus(STATUS s) { status=s; }
    BOOL unmarshall(const char*& ptr, const char* end_ptr);
	BOOL marshall(char*& ptr, const char* end_ptr);
	unsigned short getPackLng(void)
		{ return RequestReply::getPackLng() + sizeof(char)*2; }
	static REQUEST_TYPE peekAtType(const char* data);
};

/****************************************************************************
*
*   LoginRequest
*
*   Objects of this class represent request for parcels and therefore, contain
*   a parcel id.  The class encapsulates logic for marshalling/unmarshalling the
*   request. It also encapsulates how the request is processed by a server.
*/
class LoginRequest : public Request
{
private:
	char	sub_type;		// current not used, it is need so all requests
							// have the same header structure
    DString	username;
	DString	password;

public:
    /**** METHODS FOR BOTH THE SENDER AND RECEIVERS OF THE REQUEST ****/
    LoginRequest(void) :
		Request(Request::LOGIN), sub_type(' '), username(), password() { }
    LoginRequest(const SocketAddress& addr) :
		Request(Request::LOGIN, addr), sub_type(' '), username(), password() { }
    virtual ~LoginRequest() {}

    /**** METHODS FOR THE RECEIVER OF REQUESTS ****/
	LoginRequest(const Message& msg, const SocketAddress& addr) :
		Request(Request::LOGIN, addr), sub_type(' '), username(), password()
		{ load(msg); }
    virtual BOOL process(unsigned long request_id);
										// process function
    virtual BOOL load(const Message& msg);
										// Function to unpack a message
										// into this request object
	const DString& getUsername(void) const { return username; }
	const DString& getPassword(void) const { return password; }

    /**** METHODS FOR THE SENDER OF METHODS ****/
    LoginRequest(const DString& u, const DString& p) :
		Request(Request::LOGIN), sub_type(' '), username(u), password(p) {}
										// Construct to originator of
										// a request
    virtual BOOL save(Message& msg);	// Function to pack a request into
										// a message
	virtual unsigned short getPackLng(void)
		{ return Request::getPackLng() +
			sizeof(char) + 
			username.GetLength() + 2 +
			password.GetLength() + 2; }

#ifdef TESTING
public:
    static void test1(void);
    static void test2(void);
    static void test3(void);
    static void test4(void);
	static void run_tests(void);
#endif

};

/****************************************************************************
*
*   TerminateRequest
*
*   Objects of this class represent a terminate request. The class encapsulates 
*   logic for marshalling/unmarshalling the request. It also encapsulates how
*   the request is processed by a server.
*/
class TerminateRequest : public Request
{
private:
	char	sub_type;		// current not used, it is need so all requests
							// have the same header structure

public:
    /**** METHODS FOR BOTH THE SENDER AND RECEIVERS OF THE REQUEST ****/
    TerminateRequest(void) :
        Request(TERMINATE), sub_type(' ')
		{}
    TerminateRequest(const SocketAddress& addr) :
		Request(Request::TERMINATE, addr), sub_type(' ')
		{}
    virtual ~TerminateRequest() {}

    /**** METHODS FOR THE RECEIVER OR REQUESTS ****/
	TerminateRequest(const Message& msg, const SocketAddress& addr) :
		Request(Request::TERMINATE, addr), sub_type(' ')
		{ load(msg); }
    virtual BOOL process(unsigned long request_id);
										// process function
    virtual BOOL load(const Message& msg);
									    // Function to unpack a message
										// into this request object

    /**** METHODS FOR THE SENDER OF REQUESTS ****/
    virtual BOOL save(Message& msg);	// Function to pack this request
										// into a message
	virtual unsigned short getPackLng(void)
		{ return Request::getPackLng() + sizeof(char); }


#ifdef TESTING
public:
    static void test1(void);
    static void test2(void);
    static void test3(void);
    static void test4(void);
	static void run_tests(void);
#endif
};

/****************************************************************************
*
*   RequestParam
*
*   This class defines a wrapper for request parameters passed by the server
*   to a new thread for processing.  Caution: when this parameter object is
*   deleted, it will delete the request object that it references.
*/
class RequestParam
{
private:
	Request*     	request;
	unsigned long	request_id;

public:
    RequestParam(void) : request(NULL), request_id(0) {}
	RequestParam(Request* r, unsigned int id) :
		request(r), request_id(id) {}

    ~RequestParam() {}

    Request* getRequest(void) { return request; }
    unsigned long getRequestId(void) const { return request_id; }
};
