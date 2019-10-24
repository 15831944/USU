// Assignment 3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Assignment 3.h"
#include "Assignment 3Dlg.h"
#include "Resource.h"
#include <afxdlgs.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char *columnTitle[] = {"First Name","Last Name","Phone Number","Birthday","Address 1","Address2"}; 

Record::Record(){
	FirstName = "";
	LastName = "";
	PhoneNumber = "";
	BirthDate = "";
	Address1 = "";
	Address2 = "";
	isEmpty = TRUE;
}

Record::Record(CString fName, CString lName, CString pNumber, CString bDate, CString Add1, CString Add2){
	SetInfo(fName,lName,pNumber,bDate,Add1,Add2);	
}

void Record::SetInfo(CString fName, CString lName, CString pNumber, CString bDate, CString Add1, CString Add2){
	FirstName = fName;
	LastName = lName;
	PhoneNumber = pNumber;
	BirthDate = bDate;
	Address1 = Add1;
	Address2 = Add2;
	isEmpty = FALSE;
}

CString Record::GetFirstName(){
	return FirstName;
}

CString Record::GetLastName(){
	return LastName;
}

void Record::GetAllInfo(CString Info[]){
	Info[0] = FirstName;
	Info[1] = LastName;
	Info[2] = PhoneNumber;
	Info[3] = BirthDate;
	Info[4] = Address1;
	Info[5] = Address2;
}

BOOL Record::operator>(const Record &right) const {
	return (LastName + FirstName) > (right.LastName + right.FirstName);
}

BOOL Record::operator<(const Record &right) const {
	return (LastName + FirstName) < (right.LastName + right.FirstName);
}

BOOL Record::operator==(const Record &right) const {
	return (LastName + FirstName) == (right.LastName + right.FirstName);
}

BOOL Record::operator!=(const Record &right) const {
	return !operator==(right);
}

ostream & operator<<( ostream & output, const Record &right){
	output << right.FirstName << ",";
	output << right.LastName << ',';
	output << right.PhoneNumber << ',';
	output << right.BirthDate << ',';
	output << right.Address1 << ',';
	output << right.Address2 << ',' << endl;
	return output;

}

istream& operator>>( istream & input, Record &right){
	char text[6][30];
	for (int i = 0; i < 6; i++){
		if (!input.getline(text[i],30,','))
			return input;
	}
	input.ignore();
	right.FirstName = text[0];
	right.LastName = text[1];
	right.PhoneNumber = text[2];
	right.BirthDate = text[3];
	right.Address1 = text[4];
	right.Address2 = text[5];
	right.isEmpty = FALSE;
	return input;
}

BOOL Record::IsEmpty() { return isEmpty; }

template <class NodeType>
TreeNode<NodeType>::TreeNode(const NodeType &d){
	data = d;
	leftChild = NULL;
	rightChild = NULL;
}

template <class NodeType>
TreeNode<NodeType>::TreeNode(TreeNode<NodeType> *Node){
	data = Node->data;
	leftChild = Node->leftChild;
	rightChild = Node->rightChild;
}


template <class NodeType>
BinarySearchTree<NodeType>::BinarySearchTree(NodeType data){
	rootNode = new TreeNode<NodeType>(data);
	nNodes = 1;
}

template <class NodeType>
BinarySearchTree<NodeType>::BinarySearchTree(){
	rootNode = NULL;
	nNodes = 0;
}

template <class NodeType>
TreeNode<NodeType> ** BinarySearchTree<NodeType>::SearchHelper(TreeNode<NodeType> *&curNode, const NodeType &searchKey){
	if (searchKey < curNode->data){
		if (curNode->leftChild)
			return SearchHelper(curNode->leftChild, searchKey);
		else
			return &curNode->leftChild;
	}
	else if (searchKey > curNode->data){
		if (curNode->rightChild)
			return SearchHelper(curNode->rightChild, searchKey);
		else
			return &curNode->rightChild;
	}	
	else // searchKey == curNode.data
		return &curNode;//curNode;
}

template <class NodeType>
BOOL BinarySearchTree<NodeType>::InsertData(NodeType data){
	TreeNode<NodeType> **newNode;
	
	if (rootNode != NULL){
		newNode = SearchHelper(rootNode, data);
		if (*newNode == NULL){
			*newNode = new TreeNode<NodeType>(data);
			nNodes++;
			return TRUE;
		}
		else
			return FALSE;
	}
	else {
		rootNode = new TreeNode<NodeType>(data);
		nNodes = 1;
		return TRUE;
	}
}

template <class NodeType>
BOOL BinarySearchTree<NodeType>::SearchForNodeData(NodeType *&data){
	if (rootNode){
		TreeNode<NodeType> **Node;
		Node = SearchHelper(rootNode, *data);
		if (*Node){
			data = &((*Node)->data);
			return TRUE;
		} 
	}
	return FALSE;
}

template <class NodeType>
void BinarySearchTree<NodeType>::InorderTraversalHelper(TreeNode<NodeType> *T){
	if (T->leftChild)
		InorderTraversalHelper(T->leftChild);
	// visit node
	cout << T->data << ' ';
	if (T->rightChild)
		InorderTraversalHelper(T->rightChild);
}

template <class NodeType>
void BinarySearchTree<NodeType>::InorderTraversal(){
	if (rootNode)
		InorderTraversalHelper(rootNode);
	cout << endl;
}

template <class NodeType>
void BinarySearchTree<NodeType>::FillArrayHelper(TreeNode<NodeType> *T, int &count, NodeType *Array /*=NULL*/){
	if (T->leftChild)
		FillArrayHelper(T->leftChild, count, Array);
	// visit node
	if (Array)
		Array[count++] = T->data; // deep copy

	if (T->rightChild)
		FillArrayHelper(T->rightChild, count, Array);
}

template <class NodeType>
void BinarySearchTree<NodeType>::FillArray(NodeType *&Array, int &nElements){
	Array = new NodeType[nNodes];
	nElements = 0;
	if (nNodes > 0)
		FillArrayHelper(rootNode, nElements, Array);
}

template <class NodeType>
void BinarySearchTree<NodeType>::GetNodeHelper(TreeNode<NodeType> *T, int NodeNumber, int &whichNode, TreeNode<NodeType> *&Node){
	
	if (T->leftChild)
		GetNodeHelper(T->leftChild, NodeNumber, whichNode, Node);
	if (Node) return;
	// visit node
	whichNode++;
	if (whichNode == NodeNumber)
		Node = T;
	
	if (T->rightChild)
		GetNodeHelper(T->rightChild, NodeNumber, whichNode, Node);
	if (Node) return;	
	
}

template <class NodeType>
NodeType * BinarySearchTree<NodeType>::GetNode(int NodeNumber){
	// find the first node
	//TreeNode<NodeType> currNode = 
	TreeNode<NodeType> *Node = NULL;
	int whichNode = 0;
	if (NodeNumber <= nNodes)
		GetNodeHelper(rootNode, NodeNumber, whichNode, Node);
	return &Node->data;
}

template <class NodeType>
TreeNode<NodeType> * BinarySearchTree<NodeType>::DeleteHelper(TreeNode<NodeType> *thisNode){
	//go to the right, then go to the left until you find null.
	TreeNode<NodeType> * pSub = thisNode;
	//if (thisNode->rightChild){
	thisNode = thisNode->rightChild;
	if (thisNode->leftChild){
		while (thisNode->leftChild){
			pSub = thisNode;
			thisNode = thisNode->leftChild;
		}
		if (thisNode->rightChild)
			pSub->leftChild = thisNode->rightChild;
		else
			pSub->leftChild = NULL;
	}
	else{
		if (thisNode->rightChild)
			pSub->rightChild = thisNode->rightChild;
		else
			pSub->rightChild = NULL;
	}
	return thisNode;
	
}



template <class NodeType>
TreeNode<NodeType> * BinarySearchTree<NodeType>::GetRootNode(){
	return rootNode;
}

template <class NodeType>
BOOL BinarySearchTree<NodeType>::DeleteNode(NodeType nodeData){
	
	if (!rootNode)
		return FALSE;

	TreeNode<NodeType> * currNode = rootNode;
	TreeNode<NodeType> ** ptrChildNode = NULL;
	while(1){
		if (nodeData < currNode->data){
			if (currNode->leftChild == NULL)
				return FALSE;

			if (currNode->leftChild->data == nodeData){
				ptrChildNode = &currNode->leftChild;
				currNode = currNode->leftChild;
				break;
			}
			currNode = currNode->leftChild;
		}
		else if (nodeData > currNode->data){
			if (currNode->rightChild == NULL)
				return FALSE;

			if (currNode->rightChild->data == nodeData){
				ptrChildNode = &currNode->rightChild;
				currNode = currNode->rightChild;
				break;
			}
			currNode = currNode->rightChild;
		}
		else{
			ptrChildNode = &rootNode;
			break;
		}
	}

	if (currNode->leftChild && currNode->rightChild){
	// if it has two children, promote the nextNode in its place
		TreeNode<NodeType> *rightChildPtr = currNode->rightChild;
		TreeNode<NodeType> *nextNodePtr = DeleteHelper(currNode);

		if (nextNodePtr == rightChildPtr){
			rightChildPtr->leftChild = currNode->leftChild;
			*currNode = rightChildPtr;
			
			delete nextNodePtr;
			nNodes--;
		}
		else {
			currNode->data = nextNodePtr->data;
			nNodes--;
			delete nextNodePtr;
		}
	}
	else if (currNode->leftChild){
	// if it has no right child, promote the left child in its place
		TreeNode<NodeType> *ptrLeftChild = currNode->leftChild;
		delete currNode;
		*ptrChildNode = ptrLeftChild;
		nNodes--;
	}
	else if (currNode->rightChild){
	// if it has no left child, promote the right child in its place
		TreeNode<NodeType> *ptrRightChild = currNode->rightChild;
		delete currNode;
		*ptrChildNode = ptrRightChild;
		nNodes--;
	}
	else{
	// if it has no children, delete it	
		delete currNode;
		if (ptrChildNode)
			*ptrChildNode = NULL;
		else
			rootNode = NULL;
		nNodes--;
	}	
	return TRUE;
}

template <class NodeType>
void BinarySearchTree<NodeType>::DeleteAllNodesHelper(TreeNode<NodeType> *T){
	if (T->leftChild)
		DeleteAllNodesHelper(T->leftChild);
	if (T->rightChild)
		DeleteAllNodesHelper(T->rightChild);
	delete T;
}

template <class NodeType>
void BinarySearchTree<NodeType>::DeleteAllNodes(){
	if (rootNode){
		DeleteAllNodesHelper(rootNode);	
		nNodes = 0;
		rootNode = NULL;
	}
}

template <class NodeType>
void BinarySearchTree<NodeType>::WriteTreeHelper( ofstream &stream, TreeNode<NodeType> *T){
	stream << (*T).data;
	if (T->leftChild)
		WriteTreeHelper(stream, T->leftChild);
	if (T->rightChild)
		WriteTreeHelper(stream, T->rightChild);
}

template <class NodeType>
void BinarySearchTree<NodeType>::WriteTree( ofstream &stream){
	WriteTreeHelper(stream, rootNode);	
}

template <class NodeType>
void BinarySearchTree<NodeType>::ReadTree( ifstream &stream){
	NodeType d;
	while (stream >> d)
		InsertData(d);
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAssignment3Dlg dialog

CAssignment3Dlg::CAssignment3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAssignment3Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAssignment3Dlg)
	m_BirthDate = _T("");
	m_FirstName = _T("");
	m_Address1 = _T("");
	m_Address2 = _T("");
	m_PhoneNumber = _T("");
	m_LastName = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nRecords = 0;
	filePath = "";
	Modified = FALSE;
}

void CAssignment3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAssignment3Dlg)
	DDX_Control(pDX, IDC_SAVE, m_Save);
	DDX_Control(pDX, IDC_SAVEAS, m_SaveAs);
	DDX_Control(pDX, IDC_NAMES, m_Names);
	DDX_Text(pDX, IDC_BIRTH_DATE, m_BirthDate);
	DDV_MaxChars(pDX, m_BirthDate, 10);
	DDX_Text(pDX, IDC_FIRST_NAME, m_FirstName);
	DDV_MaxChars(pDX, m_FirstName, 20);
	DDX_Text(pDX, IDC_STREET1, m_Address1);
	DDV_MaxChars(pDX, m_Address1, 30);
	DDX_Text(pDX, IDC_STREET2, m_Address2);
	DDV_MaxChars(pDX, m_Address2, 30);
	DDX_Text(pDX, IDC_PHONE_NUMBER, m_PhoneNumber);
	DDV_MaxChars(pDX, m_PhoneNumber, 14);
	DDX_Text(pDX, IDC_LAST_NAME, m_LastName);
	DDV_MaxChars(pDX, m_LastName, 20);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAssignment3Dlg, CDialog)
	//{{AFX_MSG_MAP(CAssignment3Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD_RECORD, OnAddRecord)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_OPEN, OnOpen)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_SAVEAS, OnSaveas)
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	ON_NOTIFY(NM_CLICK, IDC_NAMES, OnClickNames)
	ON_COMMAND(ID_FILE_SAVE, OnSave)
	ON_COMMAND(ID_FILE_SAVEAS, OnSaveas)
	ON_COMMAND(ID_FILE_OPEN, OnOpen)
	ON_COMMAND(ID_FILE_EXIT, OnExit)
	ON_COMMAND(ID_EDIT_REMOVERECORD, OnRemove)
	ON_COMMAND(ID_EDIT_ADDRECORD, OnAddRecord)
	ON_BN_CLICKED(IDC_UPDATE_RECORD, OnUpdateRecord)
	ON_COMMAND(ID_EDIT_UPDATERECORD, OnEditUpdaterecord)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAssignment3Dlg message handlers

BOOL CAssignment3Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here


	int x;
	for (int i = 0; i < NColumns; i++)
		x = m_Names.InsertColumn( i, columnTitle[i], LVCFMT_LEFT, 75, i + 1 );

	EnableSave(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAssignment3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAssignment3Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAssignment3Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CAssignment3Dlg::ShowAllRecords(){
	Record *records = NULL;
	int nItems;
	AddressBook.FillArray(records,nItems);
	
	//m_Names.DeleteAllItems();
	
	CString Text[6];
	for (int i = 0; i < nItems; i++){
		records[i].GetAllInfo(Text);
		if (m_nRecords < nItems){
			m_nRecords++;
			m_Names.InsertItem(LVIF_TEXT|LVIF_STATE, m_nRecords, NULL, 0, LVIS_SELECTED, 0, 0);
		}
		for (int j = 0; j < 6; j++){		
			m_Names.SetItemText(i, j, Text[j]);
		}
	}

	delete [] records;
}

void CAssignment3Dlg::ShowRecord(CString array[], int pos){
	for (int j = 0; j < 6; j++){		
		m_Names.SetItemText(pos, j, array[j]);
	}
}

void CAssignment3Dlg::Close(){
	if (Modified && MessageBox("Save address book before closing?",NULL,MB_YESNO) == IDYES)
		OnSave();
	AddressBook.DeleteAllNodes();
	

}


void CAssignment3Dlg::OnAddRecord() 
{
	// TODO: Add your control notification handler code here
	
	/*
	int pos = (int) m_Names.GetFirstSelectedItemPosition();
	if (pos){
		UpdateRecord(0);
		return;
	}
	*/

	UpdateData(FROMSCREEN);
	Record newRecord(m_FirstName, m_LastName, m_PhoneNumber, m_BirthDate, m_Address1, m_Address2);

	if (!AddressBook.InsertData(newRecord)){
		UpdateRecord(1);
		//MessageBox("A person with that name already exists in your address book.",NULL,MB_ICONINFORMATION | MB_OK);
		
	}
	else {
		m_Names.InsertItem(LVIF_TEXT|LVIF_STATE, m_nRecords, NULL, 0, LVIS_SELECTED, 0, 0);
		m_nRecords++;
		ShowAllRecords();
	}
	Modified = TRUE;	
}

void CAssignment3Dlg::OnRemove() 
{
	// TODO: Add your control notification handler code here
	
	Record Rec;
	Record *editRec = &Rec;
	
	UpdateData(FROMSCREEN);
	Rec.SetInfo(m_FirstName, m_LastName, m_PhoneNumber, m_BirthDate, m_Address1, m_Address2);
	
	int pos = BinFindText(*editRec, 0, m_nRecords) + 1;
		
	if (pos){
		Record Rec(m_Names.GetItemText( pos - 1, 0 ),m_Names.GetItemText( pos - 1, 1 ),"","","","");
		Record *editRec = &Rec;
		
		if (AddressBook.SearchForNodeData(editRec)){
			char warning[90];
			CString Info[6];
			editRec->GetAllInfo(Info);
			wsprintf(warning,"Are you sure you want to delete %s %s from your address book?",Info[0],Info[1]);
			if( MessageBox(warning,NULL,MB_YESNO) == IDYES){
				Modified = TRUE;	
				AddressBook.DeleteNode(*editRec);
				m_Names.DeleteItem(pos - 1);
				m_nRecords--;
				//ShowAllRecords();
			}
		}
	}
	else
		MessageBox("You must first select a record to remove it",NULL,MB_ICONINFORMATION);
}

void CAssignment3Dlg::UpdateRecord(int pos) 
{
	// TODO: Add your control notification handler code here

	// If you click on update record, then it should update the record
	// which is selected.  

	Record Rec;
	Record *editRec = &Rec;
	
	UpdateData(FROMSCREEN);
	
	if (pos){
		pos = (int) m_Names.GetFirstSelectedItemPosition();
		if (pos == 0) {
			MessageBox("Please select a record to update",NULL,MB_ICONINFORMATION);
			return;
		}
		Rec.SetInfo(m_Names.GetItemText( pos - 1, 0 ),m_Names.GetItemText( pos - 1, 1 ),"","","","");
	}
	else
		Rec.SetInfo(m_FirstName, m_LastName, m_PhoneNumber, m_BirthDate, m_Address1, m_Address2);

	if (AddressBook.SearchForNodeData(editRec)){
		Modified = TRUE;	
		
		if (m_FirstName != editRec->GetFirstName() || m_LastName != editRec->GetLastName()){
			Record newRecord(m_FirstName, m_LastName, m_PhoneNumber, m_BirthDate, m_Address1, m_Address2);
			Record *newRecordPtr = &newRecord;
			if (AddressBook.SearchForNodeData(newRecordPtr)){
				CString Info[6];
				newRecord.GetAllInfo(Info);
				char warning[90];
				wsprintf(warning,"%s %s is already in your address book.  Do you wish to delete them?",Info[0],Info[1]);
				if (MessageBox(warning,NULL,MB_YESNO) == IDYES){
					m_Names.DeleteItem(pos - 1);
					m_nRecords--;
					AddressBook.DeleteNode(newRecord);
				}
				else
					return;
			}
			AddressBook.DeleteNode(*editRec);
			AddressBook.InsertData(newRecord);
			ShowAllRecords();
		}
		else {
			editRec->SetInfo(m_FirstName, m_LastName, m_PhoneNumber, m_BirthDate, m_Address1, m_Address2);
			CString a[6];
			editRec->GetAllInfo(a);
			//if (pos == -1)
			pos = BinFindText(*editRec, 0, m_nRecords);
			if (pos != -1)
				ShowRecord(a,pos);
		}
	
	}

}

int CAssignment3Dlg::BinFindText(Record searchKey, int start, int end){

	int pos = (end - start) / 2 + start;
	Record mRecord (m_Names.GetItemText( pos, 0 ), m_Names.GetItemText( pos, 1 ),"","","","");
	if (end - start <= 1 && mRecord != searchKey)
		return -1;

	if (searchKey > mRecord){
		return BinFindText(searchKey, pos, end);
	}
	else if (searchKey < mRecord){
		return BinFindText(searchKey, start, pos);
	}
	else {
		return pos;
	}
	
}

void CAssignment3Dlg::OnOpen() 
{
	// TODO: Add your control notification handler code here
	Close();
	CFileDialog FDlg(TRUE, "adb",NULL,OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,"Address Book Files (*.adb) |*.adb| All Files (*.*) |*.*||");
	if(FDlg.DoModal() == IDOK){
		//ifstream fin("data.out");
		filePath = FDlg.GetPathName();
		ifstream fin(filePath);
		AddressBook.DeleteAllNodes();
		m_Names.DeleteAllItems();
		m_nRecords = 0;
		AddressBook.ReadTree(fin);
		Modified = FALSE;	
		fin.close();
		ShowAllRecords();
		EnableSave();
	}
}

void CAssignment3Dlg::OnSave() 
{
	// TODO: Add your control notification handler code here
	if (AddressBook.GetRootNode()){
		ofstream fout(filePath);
		AddressBook.WriteTree(fout);
		Modified = FALSE;	
		fout.close();
	}
	else 
		MessageBox("There are no records to save",NULL,MB_ICONINFORMATION);
}

void CAssignment3Dlg::OnSaveas() 
{
	// TODO: Add your control notification handler code here
	CFileDialog FDlg(FALSE, "adb",filePath, OFN_HIDEREADONLY,"Address Book Files (*.adb) |*.adb| All Files (*.*) |*.*||");
	if(FDlg.DoModal() == IDOK){
		//ifstream fin("data.out");
		filePath = FDlg.GetPathName();
		EnableSave();
		OnSave();
	}
}

void CAssignment3Dlg::EnableSave(BOOL e){
	m_Save.EnableWindow(e);
	//OnUpdateFileSave();
	(GetMenu())->EnableMenuItem(ID_FILE_SAVE, !e);


}

void CAssignment3Dlg::OnExit() 
{
	// TODO: Add your control notification handler code here
	Close();
	CDialog::OnCancel();
}

void CAssignment3Dlg::OnClickNames(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int pos = (int) m_Names.GetFirstSelectedItemPosition();
	Record Rec(m_Names.GetItemText( pos - 1, 0 ),m_Names.GetItemText( pos - 1, 1 ),"","","","");
	Record *editRec = &Rec;
	if (AddressBook.SearchForNodeData(editRec)){
		CString Info[6];
		editRec->GetAllInfo(Info);
		CEdit * eBox;
		for (int i = 0; i < 6; i++){
			eBox = (CEdit *) GetDlgItem( IDC_FIRST_NAME + i);	
			eBox->SetWindowText(Info[i]);
		}
		(GetDlgItem(IDC_FIRST_NAME))->SetFocus();
	}
	
	*pResult = 0;
}



void CAssignment3Dlg::OnUpdateRecord() 
{
	// TODO: Add your control notification handler code here
	UpdateRecord(1);	
}

void CAssignment3Dlg::OnEditUpdaterecord() 
{
	// TODO: Add your command handler code here
	UpdateRecord(1);		
}
