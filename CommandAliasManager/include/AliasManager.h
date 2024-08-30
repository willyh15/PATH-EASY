#pragma once

#include <string>               // For std::string
#include <vector>               // For std::vector
#include <unordered_map>        // For std::unordered_map
#include <json/json.h>          // For JSON handling

class AliasManager {
public:
    // Load aliases from the JSON file
    static Json::Value LoadAliases();

    // Save aliases to the JSON file
    static void SaveAliases(const Json::Value& aliases);

    // Check if an alias already exists
    static bool AliasExists(const std::string& alias);

    // Create or update an alias in the JSON file
    static void CreateBatchAlias(const std::string& alias, const std::string& command);

    // Translate custom alias syntax to shell syntax
    static std::string translateAlias(const std::string& aliasDefinition);

    // Load PowerShell commands into a dictionary
    static void LoadPowerShellCommands(const std::string& filepath);

    // Get suggestions for a command based on input
    static std::vector<std::string> SuggestCommands(const std::string& input);

    // Function for bulk alias creation
    static void BulkAliasCreation(const std::vector<std::pair<std::string, std::string>>& aliases);

private:
    // Dictionary to store PowerShell commands and their descriptions
    static std::unordered_map<std::string, std::string> ps_command_dict_;
};
