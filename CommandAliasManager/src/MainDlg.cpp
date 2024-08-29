#include "MainDlg.h"
#include <nana/gui.hpp>

// Add includes for your new functions
#include <iostream>
#include <string>

// Add the new buttons to the constructor
CMainDlg::CMainDlg() {
    form_.caption("Main Dialog");

    browse_button_.create(form_);
    preferences_button_.create(form_);
    manage_commands_button_.create(form_);
    
    // New buttons for PATH and Alias management
    add_to_path_button_.create(form_);
    add_alias_button_.create(form_);

    browse_button_.caption("Browse");
    preferences_button_.caption("Preferences");
    manage_commands_button_.caption("Manage Commands");
    add_to_path_button_.caption("Add to PATH");
    add_alias_button_.caption("Add Alias");

    browse_button_.events().click([this] {
        onBrowseClicked();
    });
    preferences_button_.events().click([this] {
        onPreferencesClicked();
    });
    manage_commands_button_.events().click([this] {
        onManageCommandsClicked();
    });

    // Add event handlers for new buttons
    add_to_path_button_.events().click([this] {
        onAddToPathClicked();
    });
    add_alias_button_.events().click([this] {
        onAddAliasClicked();
    });

    form_.div("<vertical <browse_button><preferences_button><manage_commands_button><add_to_path_button><add_alias_button>>");
    form_["browse_button"] << browse_button_;
    form_["preferences_button"] << preferences_button_;
    form_["manage_commands_button"] << manage_commands_button_;
    form_["add_to_path_button"] << add_to_path_button_;
    form_["add_alias_button"] << add_alias_button_;
    form_.collocate();
}

CMainDlg::~CMainDlg() {}

void CMainDlg::show() {
    form_.show();
    nana::exec();
}

// Define new button event handlers
void CMainDlg::onAddToPathClicked() {
    // Example usage of AddToPath function
    std::string directory = "C:\\your\\path\\here"; // Replace with actual input from GUI
    if (AddToPath(directory)) {
        nana::msgbox m(form_, "Success");
        m << "Path added successfully.";
        m.show();
    } else {
        nana::msgbox m(form_, "Error");
        m << "Failed to add path.";
        m.show();
    }
}

void CMainDlg::onAddAliasClicked() {
    // Example usage of CreateBatchAlias function
    std::string alias = "ls"; // Replace with actual input from GUI
    std::string command = "dir"; // Replace with actual input from GUI
    CreateBatchAlias(alias, command);
    nana::msgbox m(form_, "Alias Created");
    m << "Alias created successfully.";
    m.show();
}
