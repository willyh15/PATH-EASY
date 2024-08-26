#include "FileBrowserDlg.h"
#include <afxdlgs.h>

BEGIN_MESSAGE_MAP(FileBrowserDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BROWSE_BUTTON, &FileBrowserDlg::OnBrowse)
END_MESSAGE_MAP()

FileBrowserDlg::FileBrowserDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_FILEBROWSERDIALOG, pParent)
{
}

void FileBrowserDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BOOL FileBrowserDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    return TRUE;
}

void FileBrowserDlg::OnBrowse() {
    try {
        CFileDialog fileDlg(TRUE);
        if (fileDlg.DoModal() == IDOK) {
            CString filePath = fileDlg.GetPathName();
            // Check if file exists
            if (PathFileExists(filePath)) {
                // Do something with the file path
            } else {
                AfxMessageBox(_T("The selected file does not exist."));
            }
        }
    } catch (const std::exception& e) {
        CString errorMessage;
        errorMessage.Format(_T("An error occurred while browsing: %s"), CString(e.what()));
        AfxMessageBox(errorMessage);
    }
}
