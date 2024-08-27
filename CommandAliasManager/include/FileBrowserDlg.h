#pragma once

#include <afxdlgs.h> // For CFileDialog
#include <vector>    // For std::vector
#include <string>    // For std::string

class CFileBrowserDlg : public CFileDialog {
public:
    // Constructor: Initializes the file dialog box
    CFileBrowserDlg(BOOL bOpenFileDialog, LPCTSTR lpszDefExt = nullptr, LPCTSTR lpszFileName = nullptr,
                    DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, LPCTSTR lpszFilter = nullptr,
                    CWnd* pParentWnd = nullptr);

    // Getter for selected file
    CString GetSelectedFile() const;

    // Set the file type filter for the dialog
    void SetFileTypeFilter(const CString& filter);

    // Directory management functions
    void RememberLastDirectory();
    void LoadLastDirectory();

    // Recent files management functions
    void UpdateRecentFiles(const CString& file);
    void LoadRecentFiles();
    void SaveRecentFiles();
    std::vector<CString> GetRecentFiles() const;

private:
    // Member variables for storing dialog state and recent files
    CString m_selectedFile;      // Selected file path
    CString m_lastDirectory;     // Last used directory
    std::vector<CString> m_recentFiles; // List of recent files
    CString m_fileTypeFilter;    // File type filter for the dialog
};
