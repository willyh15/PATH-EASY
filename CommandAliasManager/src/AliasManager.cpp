// AliasManager.cpp
#include "AliasManager.h"
#include <fstream>
#include <nana/gui/msgbox.hpp>
#include <regex>

// Define the path for the aliases JSON file
const std::string alias_file_path = "aliases.json";

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