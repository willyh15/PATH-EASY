#include "MainDlg.h"
#include "CommandAliasDlg.h"
#include "FileBrowserDlg.h"
#include "PreferencesDlg.h"

BEGIN_MESSAGE_MAP(MainDlg, CDialogEx)
    ON_BN_CLICKED(IDC_COMMAND_ALIAS_BUTTON, &MainDlg::OnCommandAliasClicked)
    ON_BN_CLICKED(IDC_FILE_BROWSER_BUTTON, &MainDlg::OnFileBrowserClicked)
    ON_BN_CLICKED(IDC_PREFERENCES_BUTTON, &MainDlg::OnPreferencesClicked)
END_MESSAGE_MAP()

MainDlg::MainDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_MAINDIALOG, pParent)
{
}

void MainDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BOOL MainDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    return TRUE;
}

void MainDlg::OnCommandAliasClicked()
{
    CommandAliasDlg commandAliasDlg;
    commandAliasDlg.DoModal();
}

void MainDlg::OnFileBrowserClicked()
{
    FileBrowserDlg fileBrowserDlg;
    fileBrowserDlg.DoModal();
}

void MainDlg::OnPreferencesClicked()
{
    PreferencesDlg preferencesDlg;
    preferencesDlg.DoModal();
}
