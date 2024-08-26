#include "PreferencesDlg.h"
#include <afxdlgs.h>

BEGIN_MESSAGE_MAP(PreferencesDlg, CDialogEx)
    ON_BN_CLICKED(IDC_SAVE_BUTTON, &PreferencesDlg::OnSavePreferences)
END_MESSAGE_MAP()

PreferencesDlg::PreferencesDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_PREFERENCESDIALOG, pParent)
{
}

void PreferencesDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BOOL PreferencesDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    LoadPreferences();
    return TRUE;
}

void PreferencesDlg::OnSavePreferences() {
    // Assume m_recentFilesCountCtrl and m_fileTypeFilterCtrl are input controls
    CString numRecentFilesStr, fileTypeFilterStr;
    m_recentFilesCountCtrl.GetWindowText(numRecentFilesStr);
    m_fileTypeFilterCtrl.GetWindowText(fileTypeFilterStr);
    
    int numRecentFiles = _ttoi(numRecentFilesStr);
    if (numRecentFiles < 0 || numRecentFiles > 100) {
        AfxMessageBox(_T("Number of recent files must be between 0 and 100."));
        return;
    }

    m_numRecentFiles = numRecentFiles;
    m_defaultFileTypeFilter = fileTypeFilterStr;

    SavePreferences();
    AfxMessageBox(_T("Preferences saved successfully!"));
}

void PreferencesDlg::LoadPreferences() {
    // Load preferences from a config file or registry
}


void PreferencesDlg::LoadPreferences()
{
    // Logic to load user preferences
}
