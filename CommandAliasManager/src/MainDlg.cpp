#include "stdafx.h"
#include "MainDlg.h"
#include "afxdialogex.h"

BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BROWSE, &CMainDlg::OnBnClickedBrowse)
    ON_BN_CLICKED(IDC_PREFERENCES, &CMainDlg::OnBnClickedPreferences)
    ON_BN_CLICKED(IDC_MANAGE_COMMANDS, &CMainDlg::OnBnClickedManageCommands)
END_MESSAGE_MAP()

CMainDlg::CMainDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_MAIN_DIALOG, pParent), m_pFileBrowserDlg(nullptr), m_pPreferencesDlg(nullptr), m_pCommandAliasDlg(nullptr) {}

void CMainDlg::DoDataExchange(CDataExchange* pDX) {
    CDialogEx::DoDataExchange(pDX);
}

BOOL CMainDlg::OnInitDialog() {
    CDialogEx::OnInitDialog();
    ApplyDarkTheme();  // Apply dark theme to the dialog
    return TRUE;
}

void CMainDlg::ApplyDarkTheme() {
    SetBackgroundColor(RGB(30, 30, 30));  // Dark background color
    CWnd* pChild = GetWindow(GW_CHILD);
    while (pChild) {
        pChild->SetTextColor(RGB(220, 220, 220));  // Light text color
        pChild = pChild->GetNextWindow();
    }
    Invalidate();
}

void CMainDlg::OnBnClickedBrowse() {
    if (!m_pFileBrowserDlg) {
        m_pFileBrowserDlg = new CFileBrowserDlg(this);
    }
    m_pFileBrowserDlg->DoModal();
}

void CMainDlg::OnBnClickedPreferences() {
    if (!m_pPreferencesDlg) {
        m_pPreferencesDlg = new CPreferencesDlg(this);
    }
    m_pPreferencesDlg->DoModal();
}

void CMainDlg::OnBnClickedManageCommands() {
    if (!m_pCommandAliasDlg) {
        m_pCommandAliasDlg = new CCommandAliasDlg(this);
    }
    m_pCommandAliasDlg->DoModal();
}