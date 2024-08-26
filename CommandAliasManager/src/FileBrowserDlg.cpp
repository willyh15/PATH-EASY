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

void FileBrowserDlg::OnBrowse()
{
    CFileDialog fileDlg(TRUE);
    if (fileDlg.DoModal() == IDOK)
    {
        CString filePath = fileDlg.GetPathName();
        // Do something with the file path
    }
}