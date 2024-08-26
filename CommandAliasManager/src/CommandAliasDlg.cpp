#include "stdafx.h"
#include "CommandAliasDlg.h"
#include "afxdialogex.h"

BEGIN_MESSAGE_MAP(CCommandAliasDlg, CDialogEx)
    ON_BN_CLICKED(IDC_ADD_COMMAND, &CCommandAliasDlg::OnBnClickedAdd)
    ON_BN_CLICKED(IDC_EDIT_COMMAND, &CCommandAliasDlg::OnBnClickedEdit)
    ON_BN_CLICKED(IDC_DELETE_COMMAND, &CCommandAliasDlg::OnBnClickedDelete)
    ON_BN_CLICKED(IDC_ENABLE_COMMAND, &CCommandAliasDlg::OnBnClickedEnable)
    ON_BN_CLICKED(IDC_DISABLE_COMMAND, &CCommandAliasDlg::OnBnClickedDisable)
    ON_BN_CLICKED(IDC_IMPORT_COMMANDS, &CCommandAliasDlg::OnBnClickedImport)
    ON_BN_CLICKED(IDC_EXPORT_COMMANDS, &CCommandAliasDlg::OnBnClickedExport)
END_MESSAGE_MAP()

CCommandAliasDlg::CCommandAliasDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_COMMAND_ALIAS_DIALOG, pParent) {}

void CCommandAliasDlg::DoDataExchange(CDataExchange* pDX) {
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMMAND_LIST, m_listCommands);
}

BOOL CCommandAliasDlg::OnInitDialog() {
    CDialogEx::OnInitDialog();
    ApplyDarkTheme();
    LoadCommands();
    UpdateCommandList();
    return TRUE;
}

void CCommandAliasDlg::ApplyDarkTheme() {
    SetBackgroundColor(RGB(30, 30, 30));  // Dark background color
    m_listCommands.SetTextColor(RGB(220, 220, 220));  // Light text color for list box
    Invalidate();
}

void CCommandAliasDlg::UpdateCommandList() {
    m_listCommands.ResetContent();
    for (const auto& cmd : m_commands) {
        m_listCommands.AddString(cmd.c_str());
    }
}

void CCommandAliasDlg::LoadCommands() {
    // Load commands from file or registry
    // Example: Load commands from a file
    // m_commands.push_back(L"alias ls=dir");
    // m_commands.push_back(L"alias rm=del");
}

void CCommandAliasDlg::SaveCommands() {
    // Save commands to file or registry
    // Example: Save commands to a file
}

void CCommandAliasDlg::OnBnClickedAdd() {
    // Logic to add a new command
    // For example, show an input dialog to enter the new command
}

void CCommandAliasDlg::OnBnClickedEdit() {
    // Logic to edit a selected command
    // For example, show an input dialog with the current command
}

void CCommandAliasDlg::OnBnClickedDelete() {
    // Logic to delete a selected command
    int sel = m_listCommands.GetCurSel();
    if (sel != LB_ERR) {
        m_commands.erase(m_commands.begin() + sel);
        UpdateCommandList();
    }
}

void CCommandAliasDlg::OnBnClickedEnable() {
    // Logic to enable a selected command
}

void CCommandAliasDlg::OnBnClickedDisable() {
    // Logic to disable a selected command
}

void CCommandAliasDlg::OnBnClickedImport() {
    // Logic to import commands from a file
}

void CCommandAliasDlg::OnBnClickedExport() {
    // Logic to export commands to a file
}