#include <afx.h>
#include <fstream.h>

class Record {
	friend istream & operator>>( istream & input, Record & right);
	friend ostream & operator<<( ostream & output, const Record & right);
public:
	Record();
	Record(CString fName, CString lName, CString pNumber, CString bDate, CString Add1, CString Add2);
	void SetInfo(CString fName, CString lName, CString pNumber, CString bDate, CString Add1, CString Add2);
	void GetAllInfo(CString Info[]);
	BOOL operator>(const Record &right) const;
	BOOL operator<(const Record &right) const;
	BOOL operator==(const Record &right) const;
	BOOL operator!=(const Record &right) const;
	BOOL IsEmpty();
	CString GetFirstName();
	CString GetLastName();
private:
	CString FirstName;
	CString LastName;
	CString PhoneNumber;
	CString BirthDate;
	CString Address1;
	CString Address2;
	BOOL isEmpty;
};


