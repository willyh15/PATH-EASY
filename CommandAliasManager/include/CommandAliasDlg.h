#pragma once
#include "afxwin.h"
#include <vector>
#include <string>

class CCommandAliasDlg : public CDialogEx {
public:
    CCommandAliasDlg(CWnd* pParent = nullptr);
    enum { IDD = IDD_COMMAND_ALIAS_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    void ApplyDarkTheme();
    void UpdateCommandList();
    void LoadCommands();
    void SaveCommands();

private:
    CListBox m_listCommands;
    std::vector<std::wstring> m_commands;

    afx_msg void OnBnClickedAdd();
    afx_msg void OnBnClickedEdit();
    afx_msg void OnBnClickedDelete();
    afx_msg void OnBnClickedEnable();
    afx_msg void OnBnClickedDisable();
    afx_msg void OnBnClickedImport();
    afx_msg void OnBnClickedExport();

    DECLARE_MESSAGE_MAP()
};