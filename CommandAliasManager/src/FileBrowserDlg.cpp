#include "FileBrowserDlg.h"

CFileBrowserDlg::CFileBrowserDlg() {
    form_.caption("File Browser");

    path_input_.create(form_);
    browse_button_.create(form_);
    file_list_.create(form_);

    browse_button_.caption("Browse");
    browse_button_.events().click([this] {
        onBrowse();
    });

    form_.div("<vertical <path_input weight=10%><browse_button weight=10%><file_list weight=80%>>");
    form_["path_input"] << path_input_;
    form_["browse_button"] << browse_button_;
    form_["file_list"] << file_list_;
    form_.collocate();
}

CFileBrowserDlg::~CFileBrowserDlg() {}

void CFileBrowserDlg::show() {
    form_.show();
    nana::exec();
}

void CFileBrowserDlg::onBrowse() {
    boost::filesystem::path path(path_input_.caption());
    if (boost::filesystem::exists(path) && boost::filesystem::is_directory(path)) {
        updateFileList();
    }
}

void CFileBrowserDlg::updateFileList() {
    file_list_.clear();
    boost::filesystem::path path(path_input_.caption());
    if (boost::filesystem::exists(path) && boost::filesystem::is_directory(path)) {
        for (const auto& entry : boost::filesystem::directory_iterator(path)) {
            file_list_.at(0).append(entry.path().string());
        }
    }
}

std::string CFileBrowserDlg::getSelectedFile() const {
    return selected_file_;
}