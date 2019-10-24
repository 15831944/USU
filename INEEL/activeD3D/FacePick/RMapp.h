#ifndef RMAPP_H
#define RMAPP_H


class RMApp : public CWinApp
{
public:
	RMApp();
	virtual BOOL InitInstance();
	BOOL OnIdle(LONG lCount);
protected:
	//{{AFX_MSG(RMApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	friend class RMWin;
	RMWin* rmwin;
};

#endif
