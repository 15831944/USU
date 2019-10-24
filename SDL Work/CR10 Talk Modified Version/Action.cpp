
#include "Event.h"
#include "global defs.h"

SetInputLocation::SetInputLocation()
: Action (SetInputLocationItem, "default description") {
	whichLocation = 0;
	value = NULL;
	AfxMessageBox("Warning: Default constructor for SetInputLocation called");
}

SetInputLocation::SetInputLocation(int wLocation, ExpressionItem *v)
: Action (SetInputLocationItem) {
	whichLocation = wLocation;
	value = v;
	//char desc[100]; 
	//wsprintf(desc,"Location %s = %s",AvailableInputLocations[wLocation],v->GetItemText()); 
	//SetDescription(desc);
	SetDescription("Location "+AvailableInputLocations[wLocation]+" = "+(*v->GetItemText()));
}

void SetInputLocation::DoAction(){

}

ToggleFlag::ToggleFlag()
: Action (ToggleFlagItem) {
	whichSet = 0;
	whichFlag = 0;
	value = NULL;
	AfxMessageBox("Warning: Default constructor for ToggleFlag called");
}

ToggleFlag::ToggleFlag(int wSet, int wFlag, ExpressionItem *v)
: Action (ToggleFlagItem) {
	whichSet = wSet;
	whichFlag = wFlag;
	value = v;
}

void ToggleFlag::DoAction(){

}
	
SetTimer::SetTimer()
: Action (SetTimerItem) {
	whichTimer = 0;
	AfxMessageBox("Warning: Default constructor for SetTimer called");
}

SetTimer::SetTimer(int wTimer)
: Action (SetTimerItem) {
	whichTimer = wTimer;
}

void SetTimer::DoAction(){

}

DisplayMessage::DisplayMessage()
: Action (DisplayMessageItem) {
	MessageText = "";
	MessageType = 0;
	AfxMessageBox("Warning: Default constructor for DisplayMessage called");
}

DisplayMessage::DisplayMessage(CString text, int mType)
: Action (DisplayMessageItem) {
	MessageText = text;
	MessageType = mType;
}

void DisplayMessage::DoAction(){

}

WriteLog::WriteLog ()
: Action (WriteLogItem) {
	fileName = "";
	Message = NULL;
	AfxMessageBox("Warning: Default constructor for WriteLog called");
}
	
WriteLog::WriteLog (CString fName, Expression *m)
: Action (WriteLogItem) {
	fileName = fName;
	Message = m;
}

void WriteLog::DoAction(){

}

SetTest::SetTest()
: Action (SetTestItem) {
	whichTest = 0;
	AfxMessageBox("Warning: Default constructor for SetTest called");
}

SetTest::SetTest(int wTest)
: Action (SetTestItem) {
	whichTest = wTest;
}

void SetTest::DoAction()
{

}

SetVariable::SetVariable()
: Action (SetVariableItem) {
	destination = NULL;
	source = NULL;
	AfxMessageBox("Warning: Default constructor for SetVariable called");
}

SetVariable::SetVariable(ExpressionItem *d, ExpressionItem *s)
: Action (SetVariableItem) {
	destination = d;
	source = s;	
}

void SetVariable::DoAction(){

}

// write Input Locations to a file?  I'm not sure
// what I want this action to do yet.

WriteToFile::WriteToFile()
: Action (WriteToFileItem) {
	fileName = "";
	AfxMessageBox("Warning: Default constructor for WriteToFile called");
}

WriteToFile::WriteToFile(CString fName)
: Action (WriteToFileItem) {
	fileName = fName;
}

void WriteToFile::DoAction(){

}
	
Action::Action()
{
	aItem = ActionTypes(0);
	description = "";
	AfxMessageBox("Warning: Default constructor for Action called");
}

Action::Action(ActionTypes a, CString c /*=""*/){
	aItem = a;
	description = c;
}

Action::SetDescription(CString c){
	description = c;
}

void Action::DoAction(){
	AfxMessageBox("Warning:  Base class function DoAction was called");
}

