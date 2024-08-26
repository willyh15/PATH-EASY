#pragma once
#include <afxdlgs.h>
#include <vector>
#include <string>

class CFileBrowserDlg : public CFileDialog {
public:
    CFileBrowserDlg(BOOL bOpenFileDialog, LPCTSTR lpszDefExt = nullptr, LPCTSTR lpszFileName = nullptr,
                    DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, LPCTSTR lpszFilter = nullptr,
                    CWnd* pParentWnd = nullptr);
    CString GetSelectedFile() const;

    void SetFileTypeFilter(const CString& filter);
    void RememberLastDirectory();
    void LoadLastDirectory();
    void UpdateRecentFiles(const CString& file);
    void LoadRecentFiles();
    void SaveRecentFiles();
    std::vector<CString> GetRecentFiles() const;

private:
    CString m_selectedFile;
    CString m_lastDirectory;
    std::vector<CString> m_recentFiles;
    CString m_fileTypeFilter;
};