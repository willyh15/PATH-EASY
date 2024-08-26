#include "stdafx.h"
#include "MainApp.h"
#include "MainDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CMainApp, CWinApp)
END_MESSAGE_MAP()

CMainApp::CMainApp() : m_bDarkModeEnabled(TRUE) {}

CMainApp theApp;

BOOL CMainApp::InitInstance() {
    CWinApp::InitInstance();

    // Enable dark mode
    EnableDarkMode();

    // Create main dialog
    CMainDlg dlg;
    m_pMainWnd = &dlg;
    ApplyDarkTheme(m_pMainWnd);  // Apply dark theme to the main dialog
    INT_PTR nResponse = dlg.DoModal();
    if (nResponse == IDOK) {
        // Handle dialog OK
    } else if (nResponse == IDCANCEL) {
        // Handle dialog cancel
    }

    return FALSE;
}

void CMainApp::EnableDarkMode() {
    // This function enables the dark mode for the application.
    // You might want to use Windows API or custom drawing code to set dark mode here.
    // For example, use Windows 10+ dark mode APIs if available.
    // Below is a pseudo-code representation:
    m_bDarkModeEnabled = TRUE;  // Set your flag for dark mode
    // Apply dark mode to all existing windows
    POSITION pos = m_pMainWnd->GetFirstChildWindow();
    while (pos) {
        CWnd* pWnd = m_pMainWnd->GetNextChildWindow(pos);
        ApplyDarkTheme(pWnd);
    }
}

void CMainApp::ApplyDarkTheme(CWnd* pWnd) {
    if (!pWnd || !m_bDarkModeEnabled) return;

    // Apply dark theme settings to the window
    pWnd->ModifyStyleEx(0, WS_EX_COMPOSITED);  // Enable double buffering
    pWnd->SetBackgroundColor(RGB(30, 30, 30)); // Dark background

    // Update controls' appearances
    CWnd* pChild = pWnd->GetWindow(GW_CHILD);
    while (pChild) {
        pChild->SetTextColor(RGB(220, 220, 220)); // Light text color
        pChild = pChild->GetNextWindow();
    }

    // Apply to child dialogs and controls
    pWnd->Invalidate();
}