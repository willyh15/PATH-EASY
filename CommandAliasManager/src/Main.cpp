#include "MainDlg.h"
#include <afxwin.h>

class CommandAliasManagerApp : public CWinApp
{
public:
    virtual BOOL InitInstance();
};

BOOL CommandAliasManagerApp::InitInstance()
{
    CWinApp::InitInstance();
    MainDlg dlg;
    m_pMainWnd = &dlg;
    dlg.DoModal();
    return FALSE;
}

CommandAliasManagerApp theApp;