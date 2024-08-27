#include "pch.h" // Ensure this is the first include if using precompiled headers
#include "CommandAliasDlg.h"
#include "Resource.h"
#include <afxdlgs.h>
#include <fstream>
#include <sstream>
#include <afxwin.h> // Make sure this is included for MFC classes

BEGIN_MESSAGE_MAP(CCommandAliasDlg, CDialogEx)
    ON_BN_CLICKED(IDC_ADD_COMMAND_BUTTON, &CCommandAliasDlg::OnBnClickedAdd)
    ON_BN_CLICKED(IDC_EDIT_COMMAND_BUTTON, &CCommandAliasDlg::OnBnClickedEdit)
    ON_BN_CLICKED(IDC_DELETE_COMMAND_BUTTON, &CCommandAliasDlg::OnBnClickedDelete)
END_MESSAGE_MAP()

CCommandAliasDlg::CCommandAliasDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_COMMAND_ALIAS_DIALOG, pParent)  // Use correct enum for dialog ID
{
}

void CCommandAliasDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_COMMANDS, m_listCommands);  // Link the list box control
    DDX_Control(pDX, IDC_COMMAND_INPUT, m_commandInput);  // Link the command input control
}

BOOL CCommandAliasDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    
    // Initialize your controls and load commands
    LoadCommands();
    UpdateCommandList();

    return TRUE;  // Return TRUE unless you set the focus to a control
}

void CCommandAliasDlg::OnBnClickedAdd()
{
    CString newCommand;
    m_commandInput.GetWindowText(newCommand);

    if (!newCommand.IsEmpty()) {
        m_commands.push_back(newCommand.GetString());
        UpdateCommandList();
        SaveCommands();
    } else {
        AfxMessageBox(_T("Command cannot be empty!"));
    }
}

void CCommandAliasDlg::UpdateCommandList()
{
    m_listCommands.ResetContent();
    for (const auto& cmd : m_commands) {
        m_listCommands.AddString(cmd.c_str());
    }
}

void CCommandAliasDlg::OnBnClickedEdit()
{
    // Logic to edit a command or alias
    int selIndex = m_listCommands.GetCurSel();
    if (selIndex != LB_ERR) {
        CString selectedCommand;
        m_listCommands.GetText(selIndex, selectedCommand);
        // Open an edit dialog or modify the selected command
    }
}

void CCommandAliasDlg::OnBnClickedDelete()
{
    // Logic to delete a command or alias
    int selIndex = m_listCommands.GetCurSel();
    if (selIndex != LB_ERR) {
        m_commands.erase(m_commands.begin() + selIndex);
        UpdateCommandList();
        SaveCommands();
    }
}

void CCommandAliasDlg::LoadCommands()
{
    std::ifstream infile("commands.txt");  // Use absolute path if necessary

    if (!infile.is_open()) {
        AfxMessageBox(_T("Failed to open commands file for loading."));
        return;
    }

    m_commands.clear();
    std::wstring line;
    while (std::getline(infile, line)) {
        if (!line.empty()) {
            m_commands.push_back(line);
        }
    }

    infile.close();
}

void CCommandAliasDlg::SaveCommands()
{
    std::ofstream outfile("commands.txt");  // Use absolute path if necessary

    if (!outfile.is_open()) {
        AfxMessageBox(_T("Failed to open commands file for saving."));
        return;
    }

    for (const auto& cmd : m_commands) {
        outfile << cmd << std::endl;
    }

    outfile.close();
}
