// AliasManager.h
#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <json/json.h>

class AliasManager {
public:
    // Loads aliases from the JSON file
    static Json::Value LoadAliases();

    // Saves aliases to the JSON file
    static void SaveAliases(const Json::Value& aliases);

    // Checks if an alias already exists
    static bool AliasExists(const std::string& alias);

    // Creates or updates an alias in the JSON file
    static void CreateBatchAlias(const std::string& alias, const std::string& command);

    // Translate custom alias syntax to shell syntax
    static std::string translateAlias(const std::string& aliasDefinition);

    // Load PowerShell commands into a dictionary
    static void LoadPowerShellCommands(const std::string& filepath);

    // Get suggestions for a command
    static std::vector<std::string> SuggestCommands(const std::string& input);

private:
    static std::unordered_map<std::string, std::string> ps_command_dict_;
};
