#pragma once

#include "afxwin.h"          // For CDialogEx
#include "FileBrowserDlg.h"  // Include your custom dialog headers
#include "PreferencesDlg.h"
#include "CommandAliasDlg.h"

class CMainDlg : public CDialogEx {
public:
    // Constructor for the main dialog
    CMainDlg(CWnd* pParent = nullptr);  
    enum { IDD = IDD_MAIN_DIALOG };  // Dialog ID defined in Resource.h

protected:
    // MFC override functions for dialog initialization and data exchange
    virtual void DoDataExchange(CDataExchange* pDX) override;
    virtual BOOL OnInitDialog() override;

    // Custom function to apply dark theme to the dialog
    void ApplyDarkTheme();

private:
    // Pointers to other dialog classes used within this dialog
    CFileBrowserDlg* m_pFileBrowserDlg;   // File browser dialog
    CPreferencesDlg* m_pPreferencesDlg;   // Preferences dialog
    CCommandAliasDlg* m_pCommandAliasDlg; // Command alias dialog

    // Message handlers for button clicks
    afx_msg void OnBnClickedBrowse();
    afx_msg void OnBnClickedPreferences();
    afx_msg void OnBnClickedManageCommands();

    // Macro for declaring the message map in MFC
    DECLARE_MESSAGE_MAP()
};

