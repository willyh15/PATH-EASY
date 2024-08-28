#include "MainDlg.h"

CMainDlg::CMainDlg() {
    form_.caption("Main Dialog");

    browse_button_.create(form_);
    preferences_button_.create(form_);
    manage_commands_button_.create(form_);

    browse_button_.caption("Browse");
    preferences_button_.caption("Preferences");
    manage_commands_button_.caption("Manage Commands");

    browse_button_.events().click([this] {
        onBrowseClicked();
    });
    preferences_button_.events().click([this] {
        onPreferencesClicked();
    });
    manage_commands_button_.events().click([this] {
        onManageCommandsClicked();
    });

    form_.div("<vertical <browse_button><preferences_button><manage_commands_button>>");
    form_["browse_button"] << browse_button_;
    form_["preferences_button"] << preferences_button_;
    form_["manage_commands_button"] << manage_commands_button_;
    form_.collocate();
}

CMainDlg::~CMainDlg() {}

void CMainDlg::show() {
    form_.show();
    nana::exec();
}

void CMainDlg::onBrowseClicked() {
    file_browser_dlg_.show();
}

void CMainDlg::onPreferencesClicked() {
    preferences_dlg_.show();
}

void CMainDlg::onManageCommandsClicked() {
    command_alias_dlg_.show();
}