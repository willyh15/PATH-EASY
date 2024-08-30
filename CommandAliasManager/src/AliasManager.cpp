#include "AliasManager.h"
#include <nana/gui/msgbox.hpp>
#include <regex>
#include <sstream>
#include <filesystem>

#ifdef _WIN32
const std::string user_data_dir = std::string(getenv("APPDATA")) + "\\YourAppName\\";
#else
const std::string user_data_dir = std::string(getenv("HOME")) + "/.YourAppName/";
#endif

const std::string alias_file_path = user_data_dir + "aliases.json";
const std::string ps_commands_file_path = user_data_dir + "PowerShellCommands.csv";

std::unordered_map<std::string, std::string> AliasManager::ps_command_dict_;

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

std::vector<std::string> AliasManager::SuggestCommands(const std::string& input) {
    std::vector<std::string> suggestions;
    for (const auto& cmd : ps_command_dict_) {
        if (cmd.first.find(input) != std::string::npos) {
            suggestions.push_back(cmd.first);
        }
    }
    return suggestions;
}

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

bool AliasManager::AliasExists(const std::string& alias) {
    Json::Value aliases = LoadAliases();
    return !aliases[alias].isNull();
}

void AliasManager::CreateBatchAlias(const std::string& alias, const std::string& command) {
    Json::Value aliases = LoadAliases();
    aliases[alias] = command;
    SaveAliases(aliases);
}

std::string AliasManager::translateAlias(const std::string& aliasDefinition) {
    std::regex openPattern(R"(^open\s+(.+))");
    if (std::regex_match(aliasDefinition, openPattern)) {
        return "start " + aliasDefinition.substr(5);
    }
    return aliasDefinition;
}

void AliasManager::BulkAliasCreation(const std::vector<std::pair<std::string, std::string>>& aliases) {
    for (const auto& [alias, command] : aliases) {
        CreateBatchAlias(alias, command);
    }
}