#pragma once
#include "afxwin.h"
#include "FileBrowserDlg.h"
#include "PreferencesDlg.h"
#include "CommandAliasDlg.h"

class CMainDlg : public CDialogEx {
public:
    CMainDlg(CWnd* pParent = nullptr);
    enum { IDD = IDD_MAIN_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    void ApplyDarkTheme();

private:
    CFileBrowserDlg* m_pFileBrowserDlg;
    CPreferencesDlg* m_pPreferencesDlg;
    CCommandAliasDlg* m_pCommandAliasDlg;

    afx_msg void OnBnClickedBrowse();
    afx_msg void OnBnClickedPreferences();
    afx_msg void OnBnClickedManageCommands();

    DECLARE_MESSAGE_MAP()
};