// AliasManager.h
#pragma once
#include <string>
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
};