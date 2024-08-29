#include "MainDlg.h"
#include <regex>
#include "AliasManager.h"
#include "PathManager.h"
#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/combox.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/widgets/treebox.hpp>  // Include treebox for directory navigation
#include <nana/gui/msgbox.hpp>
#include <boost/filesystem.hpp>
#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>

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

    // Create textboxes and combox for path input with autocomplete
    path_input_combo_.create(form_);
    alias_input_.create(form_);
    command_input_combo_.create(form_);

    // Create a listbox for directory selection
    directory_list_.create(form_);

    // Create a treebox for file explorer-like directory navigation
    directory_tree_.create(form_);

    // Populate the listbox with commonly used directories
    directory_list_.append_header("Common Directories", 200);
    directory_list_.append({ "C:\\Program Files", "C:\\Program Files (x86)", "C:\\Windows\\System32" });

    // Set placeholders for textboxes
    path_input_combo_.tip_string("Enter directory path...");
    alias_input_.tip_string("Enter alias...");
    command_input_combo_.tip_string("Enter command...");

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

    // Event handler for path input to provide autocomplete with debounce
    path_input_combo_.events().text_changed([this] {
        static auto last_call = std::chrono::steady_clock::now();
        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - last_call).count() > 300) { // 300ms debounce
            last_call = now;
            onPathInputChanged();
        }
    });

    // Event handler for directory list selection
    directory_list_.events().selected([this] {
        auto selected = directory_list_.selected();
        if (!selected.empty()) {
            path_input_combo_.caption(directory_list_.at(0).at(selected.front().item).text());
        }
    });

    // Set layout for the form
    form_.div("<vertical <browse_button><preferences_button><manage_commands_button>"
              "<weight=10% <path_input_combo><add_to_path_button>>"
              "<weight=10% <alias_input><command_input_combo><add_alias_button>>"
              "<weight=20% <directory_list><directory_tree>>");
    form_["browse_button"] << browse_button_;
    form_["preferences_button"] << preferences_button_;
    form_["manage_commands_button"] << manage_commands_button_;
    form_["path_input_combo"] << path_input_combo_;
    form_["add_to_path_button"] << add_to_path_button_;
    form_["alias_input"] << alias_input_;
    form_["command_input_combo"] << command_input_combo_;
    form_["add_alias_button"] << add_alias_button_;
    form_["directory_list"] << directory_list_;
    form_["directory_tree"] << directory_tree_;
    form_.collocate();
}

// Destructor
CMainDlg::~CMainDlg() {}

// Show the form
void CMainDlg::show() {
    form_.show();
    nana::exec();
}

// In MainDlg.cpp
void CMainDlg::onSearchTextChanged() {
    std::string query = search_input_.caption();
    // Filter aliases or PATH entries based on the query
    alias_list_.clear();
    Json::Value aliases = AliasManager::LoadAliases();
    for (const auto& alias : aliases.getMemberNames()) {
        if (alias.find(query) != std::string::npos) {
            alias_list_.at(0).append({ alias, aliases[alias].asString() });
        }
    }
}

// Function to scan directories and suggest paths
void CMainDlg::scanAndSuggestPaths() {
    std::vector<std::string> common_dirs = {"C:\\Program Files", "C:\\Program Files (x86)", "C:\\Windows\\System32"};
    std::set<std::string> suggestions;

    for (const auto& dir : common_dirs) {
        if (boost::filesystem::exists(dir)) {
            for (boost::filesystem::recursive_directory_iterator it(dir), end; it != end; ++it) {
                if (boost::filesystem::is_regular_file(it->path()) && (it->path().extension() == ".exe")) {
                    suggestions.insert(it->path().string());
                }
            }
        }
    }

    // Update the UI with suggestions
    path_input_combo_.clear();
    for (const auto& suggestion : suggestions) {
        path_input_combo_.push_back(suggestion);
    }
}

// Batch add directories to PATH
void CMainDlg::onBatchAddToPathClicked() {
    std::vector<std::string> directories = { "C:\\Dir1", "C:\\Dir2", "C:\\Dir3" }; // Example input
    for (const auto& dir : directories) {
        PathManager::AddToPath(dir);
    }
}

// In MainDlg.cpp
void CMainDlg::onSettingsClicked() {
    // Create and show the settings dialog
    CSettingsDlg settingsDialog;
    settingsDialog.show();
}

// In CSettingsDlg.cpp
CSettingsDlg::CSettingsDlg() {
    form_.caption("Settings");

    // Create UI elements for settings
    default_dir_input_.create(form_);
    alias_syntax_combo_.create(form_);
    
    // Populate UI elements with current settings
    default_dir_input_.caption(settings_.default_directory);
    alias_syntax_combo_.push_back("CMD");
    alias_syntax_combo_.push_back("PowerShell");
    alias_syntax_combo_.option(settings_.alias_syntax == "CMD" ? 0 : 1);

    // Event handlers to save settings
    save_button_.events().click([this] {
        settings_.default_directory = default_dir_input_.caption();
        settings_.alias_syntax = alias_syntax_combo_.caption();
        saveSettings();
        form_.close();
    });

    // Layout
    form_.div("<vertical <default_dir_input><alias_syntax_combo><save_button>>");
    form_["default_dir_input"] << default_dir_input_;
    form_["alias_syntax_combo"] << alias_syntax_combo_;
    form_["save_button"] << save_button_;
    form_.collocate();
}

// Bulk alias creation
void CMainDlg::onBulkAliasCreationClicked() {
    std::vector<std::pair<std::string, std::string>> aliases = {
        {"ll", "ls -l"},
        {"gs", "git status"},
        {"..", "cd .."}
    }; // Example input

    for (const auto& [alias, command] : aliases) {
        AliasManager::CreateBatchAlias(alias, command);
    }
}

// Event handler for "Add to PATH" button
void CMainDlg::onAddToPathClicked() {
    std::string directory = path_input_combo_.caption(); // Get input from combobox
    if (directory.empty()) {
        nana::msgbox m(form_, "Error");
        m << "Please enter a valid directory.";
        m.show();
        return;
    }

    if (PathManager::AddToPath(directory)) {
        nana::msgbox m(form_, "Success");
        m << "Path added successfully.";
        m.show();
    } else {
        // Error handling is now done in PathManager::AddToPath
    }
}

// Event handler for "Add Alias" button
void CMainDlg::onAddAliasClicked() {
    std::string alias = alias_input_.caption();  // Get input from textbox
    std::string command = command_input_combo_.caption(); // Get input from combobox
    if (alias.empty() || command.empty()) {
        nana::msgbox m(form_, "Error");
        m << "Please enter both alias and command.";
        m.show();
        return;
    }

    if (alias.find(' ') != std::string::npos || alias.find('=') != std::string::npos) {
        nana::msgbox m(form_, "Error");
        m << "Alias name cannot contain spaces or '='.";
        m.show();
        return;
    }

    if (AliasManager::AliasExists(alias)) {
        nana::msgbox m(form_, "Alias Exists");
        m << "An alias with this name already exists. Do you want to overwrite it?";
        m << nana::msgbox::yes_no;
        if (m.show() == nana::msgbox::pick_no) {
            return;
        }
    }

    AliasManager::CreateBatchAlias(alias, command);

    // Update alias list in GUI
    alias_list_.clear();
    Json::Value aliases = AliasManager::LoadAliases();
    for (const auto& alias : aliases.getMemberNames()) {
        alias_list_.at(0).append({ alias, aliases[alias].asString() });
    }

    nana::msgbox m(form_, "Alias Created");
    m << "Alias created successfully.";
    m.show();
}

// Event handler for path input text change with limited depth search and debounce
void CMainDlg::onPathInputChanged() {
    std::string input = path_input_combo_.caption(); // Get current input
    path_input_combo_.clear(); // Clear previous suggestions

    if (input.length() < 2) return; // Start suggesting after at least 2 characters

    boost::filesystem::path search_path(path_input_combo_.caption()); // Start from the selected directory
    bool found_any = false; // To track if any suggestions are found
    int max_depth = 2; // Limit depth of recursion

    try {
        for (boost::filesystem::recursive_directory_iterator it(search_path), end; it != end; ++it) {
            if (boost::filesystem::is_directory(it->path())) {
                if (it.level() > max_depth) { // Check if the current level exceeds the max depth
                    it.pop(); // Skip further processing in this directory
                    continue;
                }
            }

            if (boost::filesystem::is_regular_file(it->path()) && (it->path().extension() == ".exe")) { // Check for .exe files only
                std::string entry_name = it->path().filename().string();
                if (entry_name.find(input) != std::string::npos) { // If entry matches input
                    path_input_combo_.push_back(entry_name); // Add suggestion
                    found_any = true;
                }
            }
        }
    } catch (const boost::filesystem::filesystem_error& ex) {
        nana::msgbox m(form_, "Error");
        m << "Error reading directory: " << ex.what();
        m.show();
        return;
    }

    if (!found_any) { // If no matches found
        nana::msgbox m(form_, "No Matches");
        m << "No matching executable files found.";
        m.show();
    }
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