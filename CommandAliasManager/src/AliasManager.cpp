// AliasManager.cpp
#include "AliasManager.h"
#include <fstream>
#include <nana/gui/msgbox.hpp>

// Define the path for the aliases JSON file
const std::string alias_file_path = "aliases.json";

// Load aliases from the JSON file
Json::Value AliasManager::LoadAliases() {
    std::ifstream file(alias_file_path, std::ifstream::binary);
    Json::Value aliases;
    if (file) {
        file >> aliases;
    }
    return aliases;
}

// Save aliases to the JSON file
void AliasManager::SaveAliases(const Json::Value& aliases) {
    std::ofstream file(alias_file_path, std::ofstream::binary);
    if (file) {
        file << aliases;
    } else {
        nana::msgbox m("Error");
        m << "Unable to save aliases.";
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