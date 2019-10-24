/*****************************************************************************
*
*	File:          RequestReply.cpp
*	Class:         RequestReply
*	Version:       1.0
*	Project:       Distributed Calendar System
*	Author:        Stephen W. Clyde
*	Last Modified: September 5, 2001
*
*	Modification History:
*
*	Oct. 30, 2001	Initial Version
*
*	Description:
*  
*	Implementation of RequestReply objects
*/

#include "stdafx.h"

#include <iostream.h>
#include <fstream.h>
#include <stdlib.h>
#include "marshall.h"
#include "RequestReply.h"
#include "Request.h"
#include "Reply.h"
#include "Message.h"
#include "ComChannel.h"

#ifdef SERVER
#include "../server/server.h"
#endif

/******************************************************************************
*
*  RequestReply::send
*
*/
unsigned long RequestReply::send(const SocketAddress& addr)
{
    Message msg;			// Create an empty messsage heading for the target
    save(msg);				// Save this request or reply into the message
    return msg.send(addr);	// Send the message off
}

/******************************************************************************
*
*	RequestReply::sendAndWait
*
*	This method sends a request to the specified address and waits for a
*	response of a particular type.
*
*	Input parameters:
*		addr					Target address where this object should be sent
*		response_op_codes		A list of possible response op codes that could
*								come back as a result of sending this request
*								Each code will be a 4-char string.  The first
*								character will be an R or X.  The next two
*								charactes will indicate exactly the type of
*								request or reply.  The forth character will
*								alway be a ";".  Example: "XA ;XN ;"
*		timeout					The amount of time to wait by trying again.
*		max_tries				Maximum number of retries before giving up
*
*/
RequestReply* RequestReply::sendAndWait(
			const SocketAddress& addr,
			const char* possible_op_codes,
			unsigned long timeout,
			unsigned short max_tries)
{
	int					tries=0;
    unsigned long       send_id;
    unsigned long       first_send_id = 0;
	unsigned long		last_send_id = 0;
    RequestReply*       resp=NULL;
	SocketAddress		target_addr(addr);

	do
	{
		tries++;
	    send_id = send(addr);
        if (first_send_id == 0 && send_id!=0) first_send_id = send_id;
        if (send_id!=0) last_send_id = send_id;

	    if (first_send_id>0)
	    {
            resp = RequestReply::Receive(
                                        possible_op_codes,
                                        first_send_id,
                                        last_send_id,
                                        timeout,
										target_addr);
        }
	} while (resp==NULL && tries<max_tries);

    return resp;
}

/*****************************************************************************
*
*  RequestReply::Receive
*
*  This method receives a response of a specified type
*
*  Parameters:
*       op_codes		List of possible op codes (ignore those not in the list).
*						The requested OP codes must be for replies.
*		min_send_id	
*		max_request_id
*       max_time		maximum time to wait
*       from_addr		Reference to socket address that gets loaded with the
*						sender's address
*/

RequestReply* RequestReply::Receive(
        const char* op_codes,
        unsigned long min_request,
        unsigned long max_request,
        unsigned long max_time,
        SocketAddress &from_addr)
{
    BOOL status = FALSE;
    BOOL loop_again;

    Message* msg = NULL;
    Reply *r = NULL;

    do
    {
        msg = Message::receive(max_time, from_addr);
	    if (msg!=NULL)
        {
            if (checkOpCodes(op_codes, msg->getData()))
			{
                r = (Reply*) create(*msg, from_addr);
										// We at least go the right type of message.
										// So, create the reply object
				if (r->getRequestMsgId()>=min_request &&
					r->getRequestMsgId()<=max_request)
					loop_again=FALSE;	// O.K. we got what we were looking for so
										// stop looping
				else
				 loop_again=TRUE;        // The right kind, but wrong request so
					                     // try again
			}
			else
				loop_again=TRUE;		// Wrong kind of message, so try again
			delete msg;
        }
        else
            loop_again=FALSE;           // Time out, so get out

    } while (loop_again);

    return r;
}

/******************************************************************************
*
*  RequestReply::create
*
*/
RequestReply* RequestReply::create(const Message& msg, const SocketAddress& addr)
{
    RequestReply *r = NULL;

    switch (peekAtType(msg.getData()))
    {
        case REQUEST:
			r = Request::create(msg, addr);
            break;
        case REPLY:
			r = Reply::create(msg);
            break;
        default:
			r = NULL;
    }

    return r;
}

/******************************************************************************
*
*	RequestReply::unmarshall
*
*/
BOOL RequestReply::unmarshall(const char*& ptr, const char* end_ptr)
{
	BOOL result=FALSE;

	char tmp;
	if (::unmarshall(ptr, end_ptr, tmp)==TRUE)
	{
		type = (TYPE) tmp;
		result=TRUE;
	}

	return result;
}

/******************************************************************************
*
*	RequestReply::marshall
*
*/
BOOL RequestReply::marshall(char*& ptr, const char* end_ptr)
{
    BOOL result=FALSE;

	char tmp = (char) type;
	result=::marshall(ptr, end_ptr, tmp);

    return result;
}

/******************************************************************************
*
*	RequestReply::peekAtType
*
*	This method check the type of packaged RequestReply.  It dependent on the
*	implementation of the save methods.
*
*/
RequestReply::TYPE RequestReply::peekAtType(const char* data)
{
	TYPE result = UNKNOWN;

	if (data)
	{
	  char tmp = data[0];
	  if (tmp=='R' || tmp=='X')
		result = (TYPE) tmp;
	}

	return result;
}

/******************************************************************************
*
*	RequestReply::checkOpCodes
*
*	This method check will the op codes of a message
*
*/
BOOL RequestReply::checkOpCodes(const char *op_codes, const char* data)
{
	BOOL result = FALSE;
	char tmp[5];

	if (data)
	{
		memcpy(tmp,data,3);
		tmp[3]=';';
		tmp[4]=0;
		if (strstr(op_codes, tmp)!=NULL)
			result = TRUE;
	}

	return result;
}

