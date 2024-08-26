#include "CommandAliasDlg.h"
#include <afxdlgs.h>

BEGIN_MESSAGE_MAP(CommandAliasDlg, CDialogEx)
    ON_BN_CLICKED(IDC_ADD_COMMAND_BUTTON, &CommandAliasDlg::OnAddCommand)
    ON_BN_CLICKED(IDC_EDIT_COMMAND_BUTTON, &CommandAliasDlg::OnEditCommand)
    ON_BN_CLICKED(IDC_DELETE_COMMAND_BUTTON, &CommandAliasDlg::OnDeleteCommand)
END_MESSAGE_MAP()

CommandAliasDlg::CommandAliasDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_COMMANDALIASDIALOG, pParent)
{
}

void CommandAliasDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BOOL CommandAliasDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    // Initialize your controls here
    return TRUE;
}

void CommandAliasDlg::OnAddCommand() {
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

void CommandAliasDlg::UpdateCommandList() {
    m_listCommands.ResetContent();
    for (const auto& cmd : m_commands) {
        m_listCommands.AddString(cmd.c_str());
    }
}


void CommandAliasDlg::OnEditCommand()
{
    // Logic to edit a command or alias
}

void CommandAliasDlg::OnDeleteCommand()
{
    // Logic to delete a command or alias
}
