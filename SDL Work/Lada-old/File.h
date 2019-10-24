#ifndef FILE1_H
#define FILE1_H

class FileData
{

public:
	CString m_Date;
	CString m_Time;
	CString m_Camera;
	CString m_Size;
	FileData() {};
	~FileData() {};


};
		friend CArchive& operator <<( CArchive& ar, const FileData& right  );

#endif
