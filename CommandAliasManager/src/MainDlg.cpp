#include "MainDlg.h"
#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/msgbox.hpp>

// Add includes for your new functions
#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>

// Helper function to add a directory to the PATH
bool AddToPath(const std::string& directory) {
    std::string path;
    char* buffer = nullptr;
    size_t size = 0;

    // Get the current PATH
    if (_dupenv_s(&buffer, &size, "PATH") == 0 && buffer != nullptr) {
        path = buffer;
        free(buffer);
    }

    // Check if the directory is already in the PATH
    if (path.find(directory) != std::string::npos) {
        std::cout << "Directory is already in PATH." << std::endl;
        return false;
    }

    // Append the new directory to the PATH
    path += ";" + directory;
    if (_putenv_s("PATH", path.c_str()) != 0) {
        std::cerr << "Failed to update PATH." << std::endl;
        return false;
    }

    std::cout << "Successfully added to PATH." << std::endl;
    return true;
}

// Helper function to create a batch alias
void CreateBatchAlias(const std::string& alias, const std::string& command) {
    std::ofstream batchFile("alias.bat", std::ios::app);
    if (batchFile.is_open()) {
        batchFile << "doskey " << alias << "=" << command << "\n";
        batchFile.close();
        std::cout << "Alias created successfully." << std::endl;
    } else {
        std::cerr << "Unable to open batch file." << std::endl;
    }
}

// Constructor for the main dialog
CMainDlg::CMainDlg() {
    form_.caption("Main Dialog");

    // Create buttons
    browse_button_.create(form_);
    preferences_button_.create(form_);
    manage_commands_button_.create(form_);
    add_to_path_button_.create(form_);
    add_alias_button_.create(form_);

    // Set button captions
    browse_button_.caption("Browse");
    preferences_button_.caption("Preferences");
    manage_commands_button_.caption("Manage Commands");
    add_to_path_button_.caption("Add to PATH");
    add_alias_button_.caption("Add Alias");

    // Create textboxes
    path_input_.create(form_);
    alias_input_.create(form_);
    command_input_.create(form_);

    // Set placeholders for textboxes
    path_input_.tip_string("Enter directory path...");
    alias_input_.tip_string("Enter alias...");
    command_input_.tip_string("Enter command...");

    // Define event handlers for buttons
    browse_button_.events().click([this] {
        onBrowseClicked();
    });
    preferences_button_.events().click([this] {
        onPreferencesClicked();
    });
    manage_commands_button_.events().click([this] {
        onManageCommandsClicked();
    });
    add_to_path_button_.events().click([this] {
        onAddToPathClicked();
    });
    add_alias_button_.events().click([this] {
        onAddAliasClicked();
    });

    // Set layout for the form
    form_.div("<vertical <browse_button><preferences_button><manage_commands_button>"
              "<weight=10% <path_input><add_to_path_button>>"
              "<weight=10% <alias_input><command_input><add_alias_button>>>");
    form_["browse_button"] << browse_button_;
    form_["preferences_button"] << preferences_button_;
    form_["manage_commands_button"] << manage_commands_button_;
    form_["path_input"] << path_input_;
    form_["add_to_path_button"] << add_to_path_button_;
    form_["alias_input"] << alias_input_;
    form_["command_input"] << command_input_;
    form_["add_alias_button"] << add_alias_button_;
    form_.collocate();
}

// Destructor
CMainDlg::~CMainDlg() {}

// Show the form
void CMainDlg::show() {
    form_.show();
    nana::exec();
}

// Event handler for "Add to PATH" button
void CMainDlg::onAddToPathClicked() {
    std::string directory = path_input_.caption(); // Get input from textbox
    if (directory.empty()) {
        nana::msgbox m(form_, "Error");
        m << "Please enter a valid directory.";
        m.show();
        return;
    }

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

// Event handler for "Add Alias" button
void CMainDlg::onAddAliasClicked() {
    std::string alias = alias_input_.caption();  // Get input from textbox
    std::string command = command_input_.caption(); // Get input from textbox
    if (alias.empty() || command.empty()) {
        nana::msgbox m(form_, "Error");
        m << "Please enter both alias and command.";
        m.show();
        return;
    }

    CreateBatchAlias(alias, command);
    nana::msgbox m(form_, "Alias Created");
    m << "Alias created successfully.";
    m.show();
}

// Other event handlers for your buttons
void CMainDlg::onBrowseClicked() {
    file_browser_dlg_.show();
}

void CMainDlg::onPreferencesClicked() {
    preferences_dlg_.show();
}

void CMainDlg::onManageCommandsClicked() {
    command_alias_dlg_.show();
}
