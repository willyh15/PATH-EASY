#pragma once
#include <afxwin.h>

class CPreferencesDlg : public CDialogEx {
public:
    CPreferencesDlg(CWnd* pParent = nullptr);
    enum { IDD = IDD_PREFERENCES_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();

private:
    int m_numRecentFiles;
    CString m_defaultFileTypeFilter;

    void LoadPreferences();
    void SavePreferences();

    afx_msg void OnOK();

    DECLARE_MESSAGE_MAP()
};