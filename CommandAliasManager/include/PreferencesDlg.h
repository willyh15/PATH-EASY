#pragma once

#include <afxwin.h>  // MFC core and standard components

class CPreferencesDlg : public CDialogEx {
public:
    // Constructor for the Preferences dialog
    CPreferencesDlg(CWnd* pParent = nullptr);
    enum { IDD = IDD_PREFERENCES_DIALOG };  // Dialog ID defined in Resource.h

protected:
    // MFC override functions for dialog initialization and data exchange
    virtual void DoDataExchange(CDataExchange* pDX) override;
    virtual BOOL OnInitDialog() override;

private:
    // Variables for storing user preferences
    int m_numRecentFiles;               // Number of recent files to remember
    CString m_defaultFileTypeFilter;    // Default file type filter for file dialogs

    // Methods to load and save preferences
    void LoadPreferences();  // Load preferences from storage (e.g., registry, file)
    void SavePreferences();  // Save preferences to storage

    // Message handler for the OK button click
    afx_msg void OnOK();

    // Macro for declaring the message map in MFC
    DECLARE_MESSAGE_MAP()
};

