//
//
//
// 
// File: BitStrm.cpp
//
// Type: implememtations
//
// This file supplies implememtation for the CBitStream class
//
//
// *** WARNING: Read license agreement before including this
//               file in your project.
//
// CBitStream - copyright 1998 - Paolo Brandoli
//                               puntoEXE software
//                               www.puntoexe.com
//
//
//
//
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

// Standard MFC declarations
/////////////////////////////////////////////////////////////////
#include "stdafx.h"

// CBitStream declarations
/////////////////////////////////////////////////////////////////
#include "BitStrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//
//
//
//
// DIAGNOSTIC
//
//
//
//
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

//
//
// CBitStream validity check.
// Assert if CBitStream object is corrupted.
//
//
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
void CBitStream::AssertValid() const
{
	// Assert if the base class is corrupted
	/////////////////////////////////////////////////////////////////
#ifdef _DEBUG
	CObject::AssertValid();
#endif

	// Assert if data source is not a CFile derived object
	/////////////////////////////////////////////////////////////////
	ASSERT(m_pFile==NULL || m_pFile->IsKindOf(RUNTIME_CLASS(CFile)));
	
	// Assert if the I/O buffer holds more bytes than allowed
	/////////////////////////////////////////////////////////////////
	ASSERT(m_bufferSize<=m_bufferMaxSize);
	
	// Assert if the I/O buffer is returning more bytes than allowed
	/////////////////////////////////////////////////////////////////
	ASSERT(m_bufferBytePntr<=m_bufferSize);
	
	// Assert if the direction flag is corrupted
	/////////////////////////////////////////////////////////////////
	ASSERT(m_isWriting==TRUE || m_isWriting==FALSE);
	
	// Assert if the bits buffers are corrupted
	/////////////////////////////////////////////////////////////////
	ASSERT(m_inBits<8);
	ASSERT(m_outBits<8);
}


//
//
// Dump the state of the CBitStream object
//
//
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
#ifdef _DEBUG
void CBitStream::Dump(CDumpContext& dc) const
{
	// Dump CObject
	/////////////////////////////////////////////////////////////////
	CObject::Dump(dc);

	// Dump class state
	/////////////////////////////////////////////////////////////////
	dc << "\nClass CBitStream";
	
	// Dump the I/O buffer state
	/////////////////////////////////////////////////////////////////
	if(m_bufferSize>0)
	{
		dc << "\n buffer capacity: " << m_bufferMaxSize << " bytes";
		dc << "\n bytes in buffer: " << m_bufferSize;
		if(m_bufferSize>m_bufferMaxSize)
			dc << "\n WARNING!! Buffer holds more bytes than allowed";
		if(!m_isWriting)
		{
			dc << "\n bytes to read  :" << (m_bufferSize-m_bufferBytePntr);
			if(m_bufferBytePntr>m_bufferSize)
				dc << "\n WARNING!! Buffer is returning invalid data";
			dc << "\n Buffer is being used for reading";
		}
		else
			dc << "\n Buffer is being used for writing";
	}

	// Dump the bits buffers state
	/////////////////////////////////////////////////////////////////
	if(m_inBits>0)
		dc << "\n Bits waiting to be read: " << m_inBits;
	if(m_outBits>0)
		dc << "\n Bits waiting to be written: " << m_outBits;
	if(m_inBits>7 || m_outBits>7)
		dc << "\n Warning!! Bits buffers corrupted";
}
#endif




//
//
//
//
// CBitStream COSTRUCTION/DESTRUCTION
//
//
//
//
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
		
//
//
// CBitStream construction
//
//
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
CBitStream::CBitStream(CFile* pFile /* =NULL */,
					   unsigned int bufferSize  /* =4096 */)
{
	// Set the I/O buffer size (in bytes)
	/////////////////////////////////////////////////////////////////
	m_bufferMaxSize=0;

	// I/O buffer not allocated
	/////////////////////////////////////////////////////////////////
	m_pBuffer=NULL;

	// Number of bytes in I/O buffer
	/////////////////////////////////////////////////////////////////
	m_bufferSize=0;

	// Number of bytes moved from the input buffer to the
	//  CBitStream reading functions
	/////////////////////////////////////////////////////////////////
	m_bufferBytePntr=0;

	// Reset the buffer state
	/////////////////////////////////////////////////////////////////
	m_isWriting=FALSE;

	// Reset bits I/O buffers 
	/////////////////////////////////////////////////////////////////
	m_inBits=m_outBits=0;
	m_inBitsBuffer=m_outBitsBuffer=0;

	// There are not CFile Objects connected to this CBitStream
	/////////////////////////////////////////////////////////////////
	m_pFile=NULL;

	// Attach a CFile to this CBitStream if requested
	/////////////////////////////////////////////////////////////////
	if(pFile!=NULL)
		Attach(pFile, bufferSize);
}


//
//
// CBitStream destruction
// If there is a CFile object connected to this CBitStream,
//  it is properly detached.
//
//
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
CBitStream::~CBitStream()
{
	// Flush the I/O buffer
	// If an exception is thrown here, it is ignored. This prevent
	//  a second exception to be thrown while unwinding the stack
	//  caused by an exception.
	// For safety data source detaching, call Detach() manually
	//  before CBitStream is deleted.
	/////////////////////////////////////////////////////////////////
	try
	{
		Flush();
	}
	catch(...)
	{
		Abort();
		BufferAlloc(0);
	}

	// Remove the I/O buffer
	/////////////////////////////////////////////////////////////////
	BufferAlloc(0);
}




//
//
//
//
// I/O FILE ATTACHMENT
//
//
//
//
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

//
//
// Attach a CFile object to this stream.
// Previously attached CFile object is properly detached
//
//
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
CFile* CBitStream::Attach(CFile* pFile, 
						  unsigned int bufferSize  /* =4096 */)
{
	// DEBUG ASSERTION.
	// The pFile parameter has been set to a inconsistent or NULL
	//  value
	/////////////////////////////////////////////////////////////////
	ASSERT(pFile!=NULL && pFile->IsKindOf(RUNTIME_CLASS(CFile)));

	// If there is another CFile attached, detach it
	/////////////////////////////////////////////////////////////////
	CFile* pOldFile=Detach();

	// I/O buffers allocation
	/////////////////////////////////////////////////////////////////
	BufferAlloc(bufferSize);

	// Reset bits buffers
	/////////////////////////////////////////////////////////////////
	m_inBits=m_outBits=0;
	m_inBitsBuffer=m_outBitsBuffer=0;

	// Attach CFile object
	/////////////////////////////////////////////////////////////////
	m_pFile=pFile;

	// Return a pointer to the previously attached CFile
	/////////////////////////////////////////////////////////////////
	return pOldFile;
}


//
//
// Detach a CFile object from this stream.
//
//
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
CFile* CBitStream::Detach()
{
	// Remove the I/O buffer
	/////////////////////////////////////////////////////////////////
	BufferAlloc(0);

	// Return a pointer to the detached CFile
	/////////////////////////////////////////////////////////////////
	CFile* pFile=m_pFile;
	m_pFile=NULL;
	return pFile;
}




//
//
//
//
// READING FUNCTIONS
//
//
//
//
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

//
//
// Read a block of bits.
// If you must read a low number of bits, ReadBit
//  will work faster than this function.
//
//
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
BOOL CBitStream::ReadBits(DWORD* pBuffer, unsigned char bitsToRead)
{
    ASSERT(bitsToRead<=32);

	// The bits buffer already holds all the bits we want to read
	/////////////////////////////////////////////////////////////////
	if(m_inBits>=bitsToRead)
	{
		m_inBits-=bitsToRead;
		*pBuffer=m_inBitsBuffer>>m_inBits;
		m_inBitsBuffer&=((BYTE)1<<m_inBits)-1;
		return TRUE;
	}
	
	// The bits buffer does not contains all the requested bits
	/////////////////////////////////////////////////////////////////
	else
	{
        // Reset the read buffer
        /////////////////////////////////////////////////////////////////
        *pBuffer=NULL;

		// This flags is set to FALSE if an error occurs
		/////////////////////////////////////////////////////////////////
		BOOL bOK=TRUE;

        // Calculate the number of bytes to read
        /////////////////////////////////////////////////////////////////
        unsigned char bytesToRead=(bitsToRead-m_inBits+7)>>3;
        
        // Calculate how many bits will be stored in the bits buffer
        /////////////////////////////////////////////////////////////////
        unsigned char tempInBits=(bytesToRead<<3)+m_inBits-bitsToRead;


        // Read requested bytes. Bytes will be right aligned within the
        //  read buffer
        /////////////////////////////////////////////////////////////////
        
// MACINTOSH version
/////////////////////////////////////////////////////////////////
#ifdef _MAC
		for(BYTE* pByte=(BYTE*)pBuffer+sizeof(*pBuffer)-(DWORD)bytesToRead; bytesToWrite!=NULL && (bOK=ReadByte(pByte++)); bytesToRead--);

// PC version
/////////////////////////////////////////////////////////////////
#else
		for(BYTE* pByte=(BYTE*)pBuffer+(DWORD)bytesToRead; bytesToRead!=NULL && (bOK=ReadByte(--pByte)); bytesToRead--);
#endif

        // Retrieve bits that will be stored in the bits buffer
        /////////////////////////////////////////////////////////////////
        BYTE tempBitsBuffer;
        tempBitsBuffer=(BYTE)(*pBuffer & (((DWORD)1<<tempInBits)-1));
        
        // Calculate the DWORD to return
        /////////////////////////////////////////////////////////////////
        *pBuffer>>=tempInBits;
        *pBuffer|=(DWORD)m_inBitsBuffer<<(bitsToRead-m_inBits);
        
        // Update the bits buffer
        /////////////////////////////////////////////////////////////////
        m_inBitsBuffer=tempBitsBuffer;
        m_inBits=tempInBits;

		// Return FALSE if there is an error, otherwise return TRUE
		/////////////////////////////////////////////////////////////////
		return bOK;
	}
}


//
//
// Read a single bit from the stream
//
//
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
BOOL CBitStream::ReadBit(BOOL* pBit)
{
	// If the bits buffer is empty, read a byte
	/////////////////////////////////////////////////////////////////
	if(m_inBits==0)
	{
		if(!ReadByte(&m_inBitsBuffer))
			return FALSE;
		m_inBits=8;
	}
	
	// Read the first bit from the bits buffer
	/////////////////////////////////////////////////////////////////
	*pBit=(m_inBitsBuffer & ((DWORD)1<<--m_inBits))!=NULL;
	m_inBitsBuffer&=((BYTE)1<<m_inBits)-1;

	return TRUE;
}


//
//
// Add a bit to the specified DWORD
//
//
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
BOOL CBitStream::AddBit(DWORD* pBuffer)
{
	// If the bits buffer is empty, read a byte
	/////////////////////////////////////////////////////////////////
	*pBuffer<<=1;
	if(m_inBits==0)
	{
		if(!ReadByte(&m_inBitsBuffer))
			return FALSE;
		m_inBits=8;
	}
	
	// Read the first bit in the bits buffer
	/////////////////////////////////////////////////////////////////
	*pBuffer|=(DWORD)(m_inBitsBuffer>>(--m_inBits));
	m_inBitsBuffer&=((BYTE)1<<m_inBits)-1;

	return TRUE;
}




//
//
//
//
// WRITING FUNCTIONS
//
//
//
//
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

//
//
// Write a block of bits.
// If you must write a low number of bits, WriteBit
//  will work faster than this function.
// WARNING: bitsToWrite safety is checked in the debug version
//          only!!!
//
//
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
void CBitStream::WriteBits(DWORD* pBuffer, unsigned char bitsToWrite)
{
    ASSERT(bitsToWrite<=32);

	// If bitsToWrite is NULL, do nothing
	/////////////////////////////////////////////////////////////////
	if(bitsToWrite!=NULL)
	{
		// Bits to write will be left aligned within tempBuffer
		/////////////////////////////////////////////////////////////////
		DWORD tempBuffer=(DWORD)m_outBitsBuffer<<24;
        
        // Calculate the total number of bits to write
        /////////////////////////////////////////////////////////////////
        bitsToWrite+=m_outBits;
		unsigned char bytesToWrite=bitsToWrite>>3;
        
        // Calculate the number of bits to store for later uses
        /////////////////////////////////////////////////////////////////
        m_outBits=bitsToWrite & (unsigned char)0x07;
        
        if(bitsToWrite>=32)
        {
            // Retrieve bits to store for later uses from the least
            //  significant byte of the buffer to write
            /////////////////////////////////////////////////////////////////
            m_outBitsBuffer=(BYTE)((*pBuffer & (DWORD)0xff)<<(8-m_outBits));
            
            // Calculate the buffer to write
            /////////////////////////////////////////////////////////////////
            tempBuffer|=*pBuffer>>m_outBits;
        }
        else
        {
            // Calculate the buffer to write
            /////////////////////////////////////////////////////////////////
            tempBuffer|=*pBuffer<<(32-bitsToWrite);
            
            // Calculate the bits to store for later uses
            /////////////////////////////////////////////////////////////////
            m_outBitsBuffer=(BYTE)((tempBuffer>>(24-(bytesToWrite<<3))) & (DWORD)0xff);
        }

		// Write bytes to the data source
		/////////////////////////////////////////////////////////////////

// MACINTOSH version
/////////////////////////////////////////////////////////////////
#ifdef _MAC
		for(BYTE* pByte=(BYTE*)&tempBuffer; bytesToWrite!=NULL; WriteByte(pByte++))
			bytesToWrite--;
// PC version
/////////////////////////////////////////////////////////////////
#else
		for(BYTE* pByte=(BYTE*)&tempBuffer+sizeof(tempBuffer); bytesToWrite!=NULL; WriteByte(--pByte))
			bytesToWrite--;
#endif		
	}
}


//
//
// Write a single bit to the stream
//
//
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
void CBitStream::WriteBit(BOOL* pBit)
{
	// Move the bit to the bits buffer
	/////////////////////////////////////////////////////////////////
	if(*pBit)
		m_outBitsBuffer|=(BYTE)0x80>>m_outBits;

	// If the bits buffer is full, move it to the bytes buffer
	/////////////////////////////////////////////////////////////////
	if(++m_outBits==8)
	{
		// Write the value
		/////////////////////////////////////////////////////////////////
		m_outBits=0;
		WriteByte(&m_outBitsBuffer);
		m_outBitsBuffer=0;
	}
}




//
//
//
//
// BYTES I/O.
// ALLOW THE APPLICATION TO READ AND WRITE BYTES TO THE
//  ATTACHED DATA SOURCE.
// THE FOLLOWING FUNCTIONS PERFORMS BITS BUFFER FLUSH IF
//  NECESSARY.
//
//
//
//
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

//
//
// Read a block of bytes from the data source, using the buffer
//  if it is available. Flush the bits buffers if they
//  hold some bit.
//
//
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
unsigned int CBitStream::Read(void* pByte, unsigned int bytesToRead)
{
	// Flush the bits buffers
	/////////////////////////////////////////////////////////////////
	if(m_outBits!=0)
	{
		m_outBits=0;
		WriteByte(&m_outBitsBuffer);
		m_outBitsBuffer=0;
	}
	m_inBits=0;
	m_inBitsBuffer=0;

	// Read the bytes
	/////////////////////////////////////////////////////////////////
	return ReadBuffer((BYTE*) pByte, bytesToRead);
}


//
//
// Write a block of bytes to the data source, using the buffer if
//  it is available. Flush the bits buffer if they hold some bit.
//
//
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
void CBitStream::Write(const void* pByte, unsigned int bytesToWrite)
{
	// Flush the bits buffers
	/////////////////////////////////////////////////////////////////
	if(m_outBits!=0)
	{
		m_outBits=0;
		WriteByte(&m_outBitsBuffer);
		m_outBitsBuffer=0;
	}
	m_inBits=0;
	m_inBitsBuffer=0;

	// Write the bytes
	/////////////////////////////////////////////////////////////////
	WriteBuffer((BYTE*) pByte, bytesToWrite);
}




//
//
//
//
// INTERNAL I/O BUFFERS MANAGEMENT
//
//
//
//
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

//
//
// Set the internal I/O buffer size
//
//
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
void CBitStream::BufferAlloc(unsigned int bufferSize /* =4096 */)
{
	// Remove the old buffer
	/////////////////////////////////////////////////////////////////
	if(m_pBuffer!=NULL)
	{
		Flush();
		delete m_pBuffer;
		m_pBuffer=NULL;
	}
	m_bufferSize=0;
	m_bufferMaxSize=0;
	m_bufferBytePntr=0;

	// Buffer allocation
	/////////////////////////////////////////////////////////////////
	if(bufferSize!=NULL)
	{
		try
		{
			m_pBuffer=new BYTE[bufferSize];
		}
		catch(CMemoryException* e)
		{
			e->Delete();
			m_pBuffer=NULL;
		}
		if(m_pBuffer!=NULL)
			m_bufferMaxSize=bufferSize;
	}
}


//
//
// Return the size of the allocated buffer
//
//
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
unsigned int CBitStream::GetBufferSize()
{
	return m_bufferMaxSize;
}


//
//
// Discard allocated memory, without flushing buffers.
// Use this function from within exceptions handlers.
//
//
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
void CBitStream::Abort()
{
	// Reset the bytes buffer
	/////////////////////////////////////////////////////////////////
	m_bufferMaxSize=0;
	m_bufferSize=0;
	m_bufferBytePntr=0;
	
	// Reset the bits buffers
	/////////////////////////////////////////////////////////////////
	m_inBits=0;
	m_inBitsBuffer=0;
	m_outBits=0;
	m_outBitsBuffer=0;
}


//
//
// Return the file position. Position is adjusted with the
//  internal buffer data.
//
//
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
DWORD CBitStream::GetPosition()
{
    ASSERT(m_pFile!=NULL);

    // Get the file position
	/////////////////////////////////////////////////////////////////
	DWORD filePosition=m_pFile->GetPosition();
    
    // Adjust the position with buffer position
	/////////////////////////////////////////////////////////////////
	if(m_isWriting)
        filePosition+=m_bufferSize;
    else
        filePosition-=m_bufferSize-m_bufferBytePntr;

    // Return correct position
	/////////////////////////////////////////////////////////////////
	return filePosition;
}



//
//
// Adjust the file position. Position is adjusted with the
//  internal buffer data.
//
//
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
DWORD CBitStream::SetPosition(DWORD position)
{
    ASSERT(m_pFile!=NULL);

    // Get the file position
	/////////////////////////////////////////////////////////////////
	DWORD oldFilePosition=m_pFile->GetPosition();

	// Return the new position if all OK
	/////////////////////////////////////////////////////////////////
	DWORD retPosition=position;
    
    // Adjust the position with the internal buffer data
	/////////////////////////////////////////////////////////////////
	if(m_isWriting)
	{
        oldFilePosition+=m_bufferSize;
		int tempSize=(int)m_bufferSize+(int)position-(int)oldFilePosition;
		if(tempSize>=0 && tempSize<(int)m_bufferMaxSize)
			m_bufferSize=(unsigned int)tempSize;
		else
		{
			Flush();
			retPosition=SeekFile(position, CFile::begin);
		}
	}
    else
	{
        oldFilePosition-=m_bufferSize-m_bufferBytePntr;
		int tempPntr=(int)m_bufferBytePntr+(int)position-(int)oldFilePosition;
		if(tempPntr>=0 && tempPntr<(int)m_bufferSize)
			m_bufferBytePntr=(unsigned int)tempPntr;
		else
		{
			m_bufferSize=m_bufferBytePntr=0;
			retPosition=SeekFile(position, CFile::begin);
		}
	}

    return retPosition;
}



//
//
// Read a block of bytes from the data source, using the internal
//  buffer if available.
//
//
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
unsigned int CBitStream::ReadBuffer(BYTE* pByte, unsigned int bytesToRead)
{
	// Nothing happens if bytesToRead is NULL
	/////////////////////////////////////////////////////////////////
	if(bytesToRead==NULL)
		return 0;

	// Read directly from the data source if the I/O buffer doesn't
	//  exist
	/////////////////////////////////////////////////////////////////
	if(m_pBuffer==NULL)
		return ReadFile(pByte, bytesToRead);

	// If the buffer has been used by some writing function, flush it
	/////////////////////////////////////////////////////////////////
	if(m_isWriting)
	{
		Flush();
		m_isWriting=FALSE;
	}

	// Optimized code for single byte fetch
	/////////////////////////////////////////////////////////////////
	if(bytesToRead==1 && m_bufferBytePntr<m_bufferSize)
	{
		*pByte=m_pBuffer[m_bufferBytePntr++];
		return 1;
	}

	// If the requested number of bytes is too high, read bytes
	//  directly from the data source, without using the internal
	//  buffer.
	/////////////////////////////////////////////////////////////////
	if(bytesToRead>=m_bufferMaxSize+m_bufferSize-m_bufferBytePntr)
	{
		// Move the bytes stored in the internal buffer
		/////////////////////////////////////////////////////////////////
		unsigned int bytesToMove=m_bufferSize-m_bufferBytePntr;
		memcpy(pByte, m_pBuffer+m_bufferBytePntr, bytesToMove);
		m_bufferSize=0;
		m_bufferBytePntr=0;
		
		// Read bytes directly from the data source
		/////////////////////////////////////////////////////////////////
		unsigned int bytesFromFile;
		do
		{
			bytesFromFile=ReadFile(pByte+bytesToMove, bytesToRead-bytesToMove);
			bytesToMove+=bytesFromFile;
		}while(bytesFromFile>0 && bytesToRead-bytesToMove>0);
		return bytesToMove;
	}
	
	// If the requested number of bytes is not so high, use the
	//  buffer.
	/////////////////////////////////////////////////////////////////
	else
	{
		// Move bytes from the internal buffer to the application
		//  supplied buffer
		/////////////////////////////////////////////////////////////////
		unsigned int tempBytesToRead=bytesToRead;
		unsigned int bytesToMove=__min(bytesToRead, m_bufferSize-m_bufferBytePntr);
		memcpy(pByte, m_pBuffer+m_bufferBytePntr, bytesToMove);
		tempBytesToRead-=bytesToMove;
		m_bufferBytePntr+=bytesToMove;

		// If the internal buffer does not stores all the bytes
		//  we need, refill it with fresh bytes.
		/////////////////////////////////////////////////////////////////
		if(tempBytesToRead>0)
		{
			// Fill the buffer with new bytes
			/////////////////////////////////////////////////////////////////
			m_bufferBytePntr=0;
			m_bufferSize=0;
			unsigned int bytesFromFile;
			do
			{
				bytesFromFile=ReadFile(m_pBuffer+m_bufferSize, m_bufferMaxSize-m_bufferSize);
				m_bufferSize+=bytesFromFile;
			}while(m_bufferSize<m_bufferMaxSize && bytesFromFile>0);
			
			// Update the destination pointer
			/////////////////////////////////////////////////////////////////
			pByte+=bytesToMove;

			// Move bytes from the internal buffer to the application
			//  supplied buffer
			/////////////////////////////////////////////////////////////////
			bytesToMove=__min(tempBytesToRead, m_bufferSize);
			memcpy(pByte, m_pBuffer, bytesToMove);
			m_bufferBytePntr=bytesToMove;
			tempBytesToRead-=bytesToMove;
		}
		
		// Return the number of bytes read
		/////////////////////////////////////////////////////////////////
		return bytesToRead-tempBytesToRead;
	}
}


//
//
// Write a block of bytes to the data source, using the 
//  internal buffer if available.
//
//
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
void CBitStream::WriteBuffer(BYTE* pByte, unsigned int bytesToWrite /* =1 */)
{
	// Nothing happens if bytesToWrite is NULL
	/////////////////////////////////////////////////////////////////
	if(bytesToWrite==NULL)
		return;

	// Write to the data source if the I/O buffer doesn't exist
	/////////////////////////////////////////////////////////////////
	if(m_pBuffer==NULL)
	{
		WriteFile(pByte, bytesToWrite);
		return;
	}

	// If the buffer has been used by some reading function, flush it
	/////////////////////////////////////////////////////////////////
	if(!m_isWriting)
	{
		Flush();
		m_isWriting=TRUE;
	}

	// Optimized code for single byte writing
	/////////////////////////////////////////////////////////////////
	if(bytesToWrite==1 && m_bufferSize<m_bufferMaxSize)
	{
		m_pBuffer[m_bufferSize++]=*pByte;
		return;
	}

	// If the number of bytes to write is too high, write bytes
	//  directly to the data source, without using the internal
	//  buffer
	/////////////////////////////////////////////////////////////////
	if(bytesToWrite>=(m_bufferMaxSize<<1)-m_bufferSize)
	{
		WriteFile(m_pBuffer, m_bufferSize);
		WriteFile(pByte, bytesToWrite);
		m_bufferSize=0;
	}
	
	// If the number of bytes to write is not so high, write
	//  bytes into the internal buffer
	/////////////////////////////////////////////////////////////////
	else
	{
		// Fill the buffer with the application supplied bytes
		/////////////////////////////////////////////////////////////////
		unsigned int bytesToMove=__min(m_bufferMaxSize-m_bufferSize, bytesToWrite);
		memcpy(m_pBuffer+m_bufferSize, pByte, bytesToMove);
		m_bufferSize+=bytesToMove;
		bytesToWrite-=bytesToMove;
		
		// If the buffer cannot holds all the bytes, flush it and retry
		/////////////////////////////////////////////////////////////////
		if(bytesToWrite>0)
		{
			// Flush the buffer
			/////////////////////////////////////////////////////////////////
			WriteFile(m_pBuffer, m_bufferSize);
			m_bufferSize=0;

			// Fill the internal buffer with the bytes left in the 
			//  application supplied buffer
			/////////////////////////////////////////////////////////////////
			memcpy(m_pBuffer+m_bufferSize, pByte+bytesToMove, bytesToWrite);
			m_bufferSize+=bytesToWrite;
		}
	}
}


//
//
// First flush the bits buffer to the internal I/O buffer,
// then flush the I/O buffers to the data source.
//
//
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
void CBitStream::Flush()
{
	// Flush the bits output buffer to the bytes output buffer
	/////////////////////////////////////////////////////////////////
	if(m_outBits!=0)
	{
		m_outBits=0;
		WriteByte(&m_outBitsBuffer);
		m_outBitsBuffer=0;
	}
	m_inBits=0;
	m_inBitsBuffer=0;

	// Flush the buffer to the data source
	/////////////////////////////////////////////////////////////////
	if(m_bufferSize>0)
	{
		// Move bytes from the buffer to the data source
		/////////////////////////////////////////////////////////////////
		if(m_isWriting)
			WriteFile(m_pBuffer, m_bufferSize);

		// Rewind the data source
		/////////////////////////////////////////////////////////////////
		else
		{
			if(m_bufferSize>m_bufferBytePntr)
				SeekFile(m_bufferBytePntr-m_bufferSize, CFile::current);
		}
		
		// Reset the buffers state
		/////////////////////////////////////////////////////////////////
		m_bufferSize=0;
		m_bufferBytePntr=0;
	}
}



//
//
//
//
// OVERRIDABLES
//
//
//
//
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

//
//
//
// Override the following functions if bytes must be processed
//  before you can write or return them.
// In a Jpeg codec overriden functions are used to check for 
//  restart intervals, headers and byte stuffing.
//
//
//
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

//
//
// Read a byte from the internal buffer, using the internal
//  buffer if available.
// Override if your derived class must process bytes before
//  returning them to the calling function.
//
//
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
BOOL CBitStream::ReadByte(BYTE* pByte)
{
	return (ReadBuffer(pByte, 1)==1);
}


//
//
// Write a byte to the data source, using the internal buffer
//  if available.
// Override if your derived class must process bytes before
//  writing them.
//
//
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
void CBitStream::WriteByte(BYTE* pByte)
{
	WriteBuffer(pByte, 1);
}



//
//
//
// Override the following functions if the data source isn't
//  a CFile derived object.
//
//
//
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

//
//
// Move bytes from the data source to the internal buffer
// Override if your data source is not a CFile derived object.
//
//
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
unsigned int CBitStream::ReadFile(BYTE* pByte, unsigned int bytesToRead)
{
	// DEBUG ASSERTION.
	// The attached CFile object is not a valid object
	/////////////////////////////////////////////////////////////////
	ASSERT(m_pFile!=NULL && m_pFile->IsKindOf(RUNTIME_CLASS(CFile)));

	return m_pFile->Read(pByte, bytesToRead);
}


//
//
// Move bytes from the internal buffer to the data source
// Override if your data source is not a CFile derived object.
//
//
/////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////// 
void CBitStream::WriteFile(BYTE* pByte, unsigned int bytesToWrite)
{
	// DEBUG ASSERTION.
	// The attached CFile object is not a valid object
	/////////////////////////////////////////////////////////////////
	ASSERT(m_pFile!=NULL && m_pFile->IsKindOf(RUNTIME_CLASS(CFile)));

	m_pFile->Write(pByte, bytesToWrite);
}


//
//
// Adjust the data source position.
// The file position is moved forward or back by the specified 
//  number of bytes.
// Override if your data source is not a CFile derived object
//  or if the object doesn't support the Seek function.
//
//
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
DWORD CBitStream::SeekFile(int position, UINT startFrom)
{
	// DEBUG ASSERTION.
	// The attached CFile object is not a valid object
	/////////////////////////////////////////////////////////////////
	ASSERT(m_pFile!=NULL && m_pFile->IsKindOf(RUNTIME_CLASS(CFile)));

	return m_pFile->Seek(position, startFrom);
}

// BitStrm.cpp End Of File
/////////////////////////////////////////////////////////////////
