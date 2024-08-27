#pragma once

#include "pch.h"
#include "afxwin.h"
#include "Resource.h"  // Ensure Resource IDs are included
#include <string>
#include <vector>

class CCommandAliasDlg : public CDialogEx {
public:
    CCommandAliasDlg(CWnd* pParent = nullptr);
    enum { IDD = IDD_COMMAND_ALIAS_DIALOG };  // Ensure this is defined in Resource.h

protected:
    virtual void DoDataExchange(CDataExchange* pDX) override;
    virtual BOOL OnInitDialog() override;
    void ApplyDarkTheme();
    void UpdateCommandList();
    void LoadCommands();
    void SaveCommands();

private:
    CListBox m_listCommands;
    std::vector<std::wstring> m_commands;
    CEdit m_commandInput;  // Ensure this is declared for OnAddCommand

    afx_msg void OnBnClickedAdd();
    afx_msg void OnBnClickedEdit();
    afx_msg void OnBnClickedDelete();
    afx_msg void OnBnClickedEnable();
    afx_msg void OnBnClickedDisable();
    afx_msg void OnBnClickedImport();
    afx_msg void OnBnClickedExport();

    DECLARE_MESSAGE_MAP()
};
