#pragma once

#include "pch.h"
#include <nana/gui.hpp>
#include <nana/gui/widgets/form.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <boost/filesystem.hpp>

class CFileBrowserDlg {
public:
    CFileBrowserDlg();
    ~CFileBrowserDlg();

    void show();
    std::string getSelectedFile() const;

private:
    void onBrowse();
    void updateFileList();

    nana::form form_;
    nana::textbox path_input_;
    nana::button browse_button_;
    nana::listbox file_list_;
    std::string selected_file_;
};