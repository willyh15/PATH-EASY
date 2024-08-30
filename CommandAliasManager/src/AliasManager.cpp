// AliasManager.cpp
#include "AliasManager.h"
#include <fstream>
#include <nana/gui/msgbox.hpp>
#include <regex>
#include <sstream>
#include <filesystem>

// Determine the user-specific data directory path based on the operating system
#ifdef _WIN32
const std::string user_data_dir = std::string(getenv("APPDATA")) + "\\YourAppName\\";
#else
const std::string user_data_dir = std::string(getenv("HOME")) + "/.YourAppName/";
#endif

// Define the paths for the aliases JSON file and PowerShell commands CSV file
const std::string alias_file_path = user_data_dir + "aliases.json";
const std::string ps_commands_file_path = user_data_dir + "PowerShellCommands.csv";

// Ensure the user data directory exists
std::filesystem::create_directories(user_data_dir);

// Initialize the PowerShell command dictionary
std::unordered_map<std::string, std::string> AliasManager::ps_command_dict_;

// Load PowerShell commands from a CSV file into a dictionary
void AliasManager::LoadPowerShellCommands(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        nana::msgbox m("Error");
        m << "Failed to load PowerShell commands from file: " << filepath;
        m.show();
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, definition;
        if (std::getline(ss, name, ',') && std::getline(ss, definition)) {
            ps_command_dict_[name] = definition;
        }
    }
    file.close();
}

// Get suggestions for a command based on input
std::vector<std::string> AliasManager::SuggestCommands(const std::string& input) {
    std::vector<std::string> suggestions;
    for (const auto& cmd : ps_command_dict_) {
        if (cmd.first.find(input) != std::string::npos) {
            suggestions.push_back(cmd.first);
        }
    }
    return suggestions;
}

// Load aliases from the JSON file
Json::Value AliasManager::LoadAliases() {
    std::ifstream file(alias_file_path, std::ifstream::binary);
    Json::Value aliases;
    if (file) {
        try {
            file >> aliases;
        } catch (const std::exception& e) {
            nana::msgbox m("Error");
            m << "Failed to load aliases: " << e.what();
            m.show();
        }
    } else {
        nana::msgbox m("Error");
        m << "Unable to open alias file for reading.";
        m.show();
    }
    return aliases;
}

// Save aliases to the JSON file
void AliasManager::SaveAliases(const Json::Value& aliases) {
    std::ofstream file(alias_file_path, std::ofstream::binary);
    if (file) {
        try {
            file << aliases;
        } catch (const std::exception& e) {
            nana::msgbox m("Error");
            m << "Failed to save aliases: " << e.what();
            m.show();
        }
    } else {
        nana::msgbox m("Error");
        m << "Unable to open alias file for writing.";
        m.show();
    }
}

// Check if an alias already exists
bool AliasManager::AliasExists(const std::string& alias) {
    Json::Value aliases = LoadAliases();
    return !aliases[alias].isNull();
}

// Create or update an alias in the JSON file
void AliasManager::CreateBatchAlias(const std::string& alias, const std::string& command) {
    Json::Value aliases = LoadAliases();
    aliases[alias] = command;
    SaveAliases(aliases);
}

// Translate custom alias syntax to shell syntax
std::string AliasManager::translateAlias(const std::string& aliasDefinition) {
    std::regex openPattern(R"(^open\s+(.+))");
    if (std::regex_match(aliasDefinition, openPattern)) {
        return "start " + aliasDefinition.substr(5);
    }
    return aliasDefinition;
}

// Function for bulk alias creation
void AliasManager::BulkAliasCreation(const std::vector<std::pair<std::string, std::string>>& aliases) {
    for (const auto& [alias, command] : aliases) {
        CreateBatchAlias(alias, command);
    }
}

