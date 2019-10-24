/*****************************************************************************
*
*  File:          RequestReply.h
*  Class:         RequestReply
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

#include "DString.h"
#include "sockaddr.h"
#include "Message.h"

/****************************************************************************
*
*   RequestReply
*
*   This is an abstract base class for all types of requests and replies.
*/
class RequestReply
{
public:
    typedef enum { UNKNOWN='U', REQUEST='R', REPLY='X' } TYPE;

private:
    TYPE type;

public:
    // Constructor
    RequestReply(TYPE t) : type(t) {}

    // Destructor
    virtual ~RequestReply() {}

	TYPE getType(void) const { return type; }

    // Function to unmarshall a message into a RequestReply
    virtual BOOL load(const Message& msg) = 0;
    // Function to marshall the request or reply into a Message
    virtual BOOL save(Message& msg) = 0;


    /**** METHODS FOR THE SENDERS ****/
    unsigned long send(const SocketAddress& addr);
										// Packages up the request in a datagram and sends
                                        // it to the server.  If successful, it requests
                                        // the message number of the datagram that was sent
	RequestReply* sendAndWait(const SocketAddress& addr, const char* possible_types, unsigned long timeout, unsigned short max_tries);
										// Send out the request and wait for an apprioriate
										// response

    static RequestReply* Receive(		// Try to receive a message from a particular address
										// of a particular type to one of several previous
										// messages
                            const char* op_codes,
                            unsigned long min_request,
                            unsigned long max_request,
                            unsigned long max_time,
                            SocketAddress& from_addr);

    static RequestReply* Receive(		// Try to receive a message from any address
										// of a particular type to one of several previous
										// messages
                            const char* op_codes,
                            unsigned long min_request,
                            unsigned long max_request,
                            unsigned long max_time)
        {   SocketAddress sender;
            return Receive(op_codes, min_request, max_request, max_time, sender); }

	static RequestReply* create(const Message& msg, const SocketAddress& addr);

protected:
    BOOL unmarshall(const char*& ptr, const char* end_ptr);
	BOOL marshall(char*& ptr, const char* end_ptr);
	unsigned short getPackLng(void)	{ return sizeof(char); }
	static TYPE peekAtType(const char* data);
	static BOOL checkOpCodes(const char *op_codes, const char* data);
};

