//////////////////////////////////////////////////////////////////////////////
//
//  File:          Message.h
//  Class:         Message
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

#include "sockaddr.h"
#include "LogicalClock.h"

class ComChannel;

/****************************************************************************
*
*   Message
*
*   This is an abstract base class for messages.  It encapsulates an
*   address, message_id, and logical clock.  For sendes, the address
*   is a target address.  For receivers, the address is the actual
*	sender's.
*/

class Message {
private:
    SocketAddress   addr;       // For servers, this address references a client
                                // For clients, this addrss references a server
    long			id;			// Message id 
	LogicalClock	timestamp;	// This Message's timestamp,
								// which is a copy of the process's
								// logical clock at the time the
								// Message was sent
    char			*data;		// Data buffer
    short			data_lng;	// Data length

public:
    Message(long msg_id=0) :
	    id(msg_id),
		timestamp(0),
	    data(NULL),
	    data_lng(0) {}
    Message(long msg_id, const char *buffer, short lng) :
	    id(msg_id),
		timestamp(0),
	    data(NULL),
	    data_lng(0)
	    {  setData(buffer, lng); }
    Message(const char* buffer, unsigned short& lng) :
	    id(0),
		timestamp(0),
	    data(NULL),
	    data_lng(0)
	    {  load(buffer, lng); }
    Message(Message &orig) :
	    id(orig.id),
		timestamp(orig.timestamp),
		data(NULL),
		data_lng(0)
	    {  setData(orig.data, orig.data_lng); }
    ~Message()
	    { if (data) delete data; };

    unsigned long send(const SocketAddress& addr, ComChannel * ptrCommChannel = NULL);
	static Message* receive(unsigned long max_time, SocketAddress &from_addr, ComChannel * ptrCommChannel = NULL);
    
    BOOL load(const char *buffer, unsigned short& lng);
    BOOL save(char *buffer, unsigned short& lng);
    void clearData(void);
    void clear(void);

    void setId(long n) { id=n; }
    void setData(const char *buffer, int lng);
    void setAddress(const SocketAddress& a) { addr=a; }

    long getId(void) const { return id; }
    const char *getData(void) const { return data; }
    short getLength(void) const { return data_lng; }
	const LogicalClock& getTimestamp(void) const { return timestamp; }
    const SocketAddress& getAddress(void) const { return addr; }

	operator = (const Message& m)
		{
			id = m.id;
			timestamp = m.timestamp;
			setData(m.data, m.data_lng);
		}

    virtual int compare(const Message &m) const;


private:
	unsigned short getPackLng(void) const
		{ return sizeof(long) + timestamp.getPackLng() + sizeof(short) + data_lng; }

    static unsigned long next_msg_id;
	static unsigned short max_size;

    static unsigned long getNextMsgId(void)
        { return next_msg_id++; }
	static unsigned short getMaxSize(void)
		{ return max_size; }
	static void setMaxSize(unsigned short size)
		{ max_size = size; }

#ifdef TESTING
public:
    static void test1(void);
    static void test2(void);
    static void test3(void);
    static void test4(void);
    static void test5(void);
	static void run_tests(void);
#endif

};
