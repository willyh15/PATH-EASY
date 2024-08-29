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

#include <windows.h>
#include <iostream>
#include <string>

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
