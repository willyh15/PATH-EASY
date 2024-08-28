#pragma once

#include "pch.h"
#include <nana/gui.hpp>
#include <nana/gui/widgets/form.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/label.hpp>
#include "FileBrowserDlg.h"
#include "PreferencesDlg.h"
#include "CommandAliasDlg.h"

class CMainDlg {
public:
    CMainDlg();
    ~CMainDlg();

    void show();

private:
    void onBrowseClicked();
    void onPreferencesClicked();
    void onManageCommandsClicked();

    nana::form form_;
    nana::button browse_button_, preferences_button_, manage_commands_button_;
    CFileBrowserDlg file_browser_dlg_;
    CPreferencesDlg preferences_dlg_;
    CCommandAliasDlg command_alias_dlg_;
};