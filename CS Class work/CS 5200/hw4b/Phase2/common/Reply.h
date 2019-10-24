/*****************************************************************************
*
*	File:          Reply.h
*	Class:         All kinds of reply classes
*	Project:       Parcel Tracker
*	Author:        Stephen W. Clyde
*	Last Modified: Oct. 31, 2001
*
*	Modification History:
*
*   Oct. 31	Initial version
*
*	Description:
*
*	A reply object represents something being send from one process
*	back to another in response to a request.
*
******************************************************************************/

#pragma once

#include "DString.h"
#include "sockaddr.h"
#include "Message.h"
#include "RequestReply.h"
#include "PersistentObject.h"

/******************************************************************************
*
*   Reply
*
*   This is the base class for all types of replies.  In genera, for servers,
*	responses represent things being sent to clients.  For clients, they
*	respresent things received from servers.
*/
class Reply : public RequestReply
{
public:
    typedef enum { UNKNOWN, OBJ='O', COUNT='C', ACK='A', ERR_RESP='E', NEW_ID='N' } REPLY_TYPE;

private:
    REPLY_TYPE      reply_type;
	long			request_msg_id;

public:
    Reply(void) :
		RequestReply(RequestReply::REPLY),
        reply_type(UNKNOWN),
        request_msg_id(0) {}
    Reply(REPLY_TYPE t, unsigned long id=0) :
		RequestReply(RequestReply::REPLY),
        reply_type(t),
        request_msg_id(id) {}

    // Destructor
    virtual ~Reply() {}

    // Access functions
    REPLY_TYPE getReplyType(void) const { return reply_type; } 
    unsigned long getRequestMsgId(void) const { return request_msg_id; }

    // Update functions
    void setType(REPLY_TYPE t) { reply_type=t; }
    void setId(unsigned long id) { request_msg_id=id; }

    /**** Static methods ****/
    static Reply* create(const Message& msg);

protected:
    BOOL unmarshall(const char*& ptr, const char* end_ptr);
	BOOL marshall(char*& ptr, const char* end_ptr);
	unsigned short getPackLng(void)
		{ return RequestReply::getPackLng() + sizeof(char) + sizeof(long); }
	static REPLY_TYPE peekAtType(const char* data);

};

/******************************************************************************
*
*   ObjectReply
*
*   A Object Rsponse encapsulate a persistent object that is being send from
*   one process back to another
*
*/
class ObjectReply : public Reply
{
public:
	typedef enum {	UNKNOWN=' ',
				    BUILDING='B',
					CALENDAR='C',
					EVENT='E',
					LOCATION='L',
					RESERVED_TIME='R',
					MEETING_PREFERENCE='P' } OBJ_TYPE;
private:
	OBJ_TYPE			obj_type;
    PersistentObject*	obj;
    BOOL				obj_cleanup_required;

public:
    // **** METHODS FOR BOTH THE SENDER AND RECEIVE OF THE RESPONSE
    // Constructor
    ObjectReply(void) :
        Reply(Reply::OBJ),
		obj_type(UNKNOWN),
        obj(NULL),
        obj_cleanup_required(FALSE) {}

    // Destructor
    virtual ~ObjectReply()
        { clear(); }
    void clear(void)
        {
			if (obj && obj_cleanup_required)
				delete obj;
			obj_type=UNKNOWN;
			obj=NULL;
			obj_cleanup_required=FALSE;
		}

    PersistentObject* getObject(void) { return obj; }
	OBJ_TYPE getObjectType(void) const { return obj_type; }

    /**** METHODS FOR THE SENDER OF THE RESPONSE ****/
    // Constructor
    ObjectReply(OBJ_TYPE t, PersistentObject* po, unsigned long request_id) :
        Reply(Reply::OBJ, request_id),
		obj_type(t),
        obj(po),
        obj_cleanup_required(FALSE) {}
    virtual BOOL save(Message &d);
	virtual unsigned short getPackLng(void)
		{ return (OBJ==NULL) ? 0 :
			Reply::getPackLng() + 
			sizeof(char) + 
			obj->getPackLng(); }

    /**** METHODS FOR THE RECEIVER OF THE RESPONSE ****/
    ObjectReply(const Message& msg) :
		Reply(Reply::OBJ),
        obj(NULL),
        obj_cleanup_required(FALSE)
        { load(msg); }
    // Function to load the request object from a message
    virtual BOOL load(const Message& d);


#ifdef TESTING
public:
    static void test1(void);
    static void test2(void);
	static void run_tests(void);
#endif
};

/******************************************************************************
*
*   CountReply
*
*   A parcel response object encapsulate a parcel object that is being send from
*   the server back to the client.
*
*/
class CountReply : public Reply
{
private:
    short   count;

public:
    /**** METHODS FOR BOTH THE SENDER AND RECEIVER OF THE RESPONSE ****/
    // Constructor
    CountReply(void) :
        Reply(Reply::COUNT),
		count(0)
		{}

	void setCount(short c) { count = c; }
    short getCount(void) const { return count; }

    // Destructor
    virtual ~CountReply() {}

    /**** METHODS FOR THE RECEIVER OF THE RESPONSE ****/
    CountReply(const Message& msg) :
        Reply(Reply::COUNT),
		count(0)
		{ load(msg); }
    virtual BOOL load(const Message& d);
										// Function to load the reply
										// from a message

    /**** METHODS FOR THE SEND OF THE RESPONSE ****/
    // Constructor
    CountReply(short c, unsigned long id) :
        Reply(Reply::COUNT, id),
		count(c)
		{}
    virtual BOOL save(Message &msg);	// Method to save the reply
										// into a message
	virtual unsigned short getPackLng(void)
	{ return (OBJ==NULL) ? 0 :
			Reply::getPackLng() + 
			sizeof(short); }

#ifdef TESTING
public:
    static void test1(void);
    static void test2(void);
    static void test3(void);
    static void test4(void);
	static void run_tests(void);
#endif
};

/******************************************************************************
*
*   AckReply
*
*   An acknowledge reply is a positive response to a request.  It encapsulates
*	a value who meaning can be defined by the protocol.
*
*/
class AckReply : public Reply
{
private:
    long value;

public:
    /**** METHODS FOR BOTH THE SENDER AND RECEIVER OF THE RESPONSE ****/
    AckReply(void) :
        Reply(Reply::ACK),
        value(0)
        {}

	void setValue(long v) { value = v; }
    long getValue(void) const { return value; }

    virtual ~AckReply() {}

    /**** METHODS FOR THE RECEIVER OF THE RESPONSE ****/
    AckReply(const Message& msg) :
        Reply(Reply::ACK),
        value(0)
        { load(msg); }

    virtual BOOL load(const Message& msg);
										// Function to load the reply
										// from a message

    /**** METHODS FOR THE SEND OF THE RESPONSE ****/
    // Constructor
    AckReply(long v, unsigned long id) :
        Reply(Reply::ACK, id),
        value(v)
        {}
    virtual BOOL save(Message& d);		// Method to save the reply
										// into a message
	virtual unsigned short getPackLng(void)
		{ return (OBJ==NULL) ? 0 :
			Reply::getPackLng() + 
			sizeof(long); }

#ifdef TESTING
public:
    static void test1(void);
    static void test2(void);
	static void run_tests(void);
#endif
};

/*******************************************************************************
*
*   ErrorReply
*
*   An error reply is a negative response to a request.  It encapsulates an error
*	message.
*
*/
class ErrorReply : public Reply
{
private:
    DString text;

public:
    /**** METHODS FOR BOTH THE SENDER AND RECEIVER OF THE RESPONSE ****/
    ErrorReply(void) :
        Reply(Reply::ERR_RESP),
        text("") {}
    virtual ~ErrorReply() {}

	void setText(DString& t) { text = t; }
    const DString& getText(void) const { return text; }

    /**** METHODS FOR THE RECEIVER OF THE RESPONSE ****/
    ErrorReply(const Message& msg) :
        Reply(Reply::ERR_RESP),
        text("")
        { load(msg); }
    virtual BOOL load(const Message& msg);
										// Function to load the reply
										// from a message

    /**** METHODS FOR THE SEND OF THE RESPONSE ****/
    ErrorReply(DString &t, unsigned long id) :
        Reply(Reply::ERR_RESP, id),
        text(t) {}
    virtual BOOL save(Message &msg);	// Method to save a reply into
										// a message
	virtual unsigned short getPackLng(void)
		{ return (OBJ==NULL) ? 0 :
			Reply::getPackLng() + 
			text.GetLength() + 2; }

#ifdef TESTING
public:
    static void test1(void);
    static void test2(void);
	static void run_tests(void);
#endif
};

/******************************************************************************
*
*   NewIdReply
*
*   A NewIdReply object encapsulates the information sent from
*   the server to the client as an acknowledgement of a create request.  The
*   object encapsulates a new id and the port number of a data communication
*   channel.
*
*/
class NewIdReply : public Reply
{
private:
    long new_id;

public:
    /**** METHODS FOR BOTH THE SENDER AND RECEIVER OF THE RESPONSE ****/
    NewIdReply(void) :
        Reply(Reply::NEW_ID),
        new_id(0)
        {}

	void setNewId(long v) { new_id = v; }
    long getNewId(void) const { return new_id; }

    virtual ~NewIdReply() {}

    /**** METHODS FOR THE RECEIVER OF THE RESPONSE ****/
    NewIdReply(const Message& msg) :
        Reply(Reply::NEW_ID),
        new_id(0)
        { load(msg); }

    virtual BOOL load(const Message& msg);
										// Function to load the reply
										// from a message

    /**** METHODS FOR THE SEND OF THE RESPONSE ****/
    // Constructor
    NewIdReply(long v, unsigned long id) :
        Reply(Reply::NEW_ID, id),
        new_id(v)
        {}
    virtual BOOL save(Message& d);		// Method to save the reply
										// into a message
	virtual unsigned short getPackLng(void)
		{ return (OBJ==NULL) ? 0 :
			Reply::getPackLng() + 
			sizeof(long); }

#ifdef TESTING
public:
    static void test1(void);
    static void test2(void);
	static void run_tests(void);
#endif
};
