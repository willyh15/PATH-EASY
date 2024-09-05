#ifndef ALIASMANAGER_H
#define ALIASMANAGER_H

#include <string>
#include <unordered_map>
#include <vector>
#include <json/json.h> // Ensure the JSON library is properly linked
#include <fstream>

// Include necessary Qt headers
#include <QString>
#include <QMessageBox>

// AliasManager class definition
class AliasManager {
public:
    static void LoadPowerShellCommands(const std::string& filepath);
    static Json::Value LoadAliases();
    static void SaveAliases(const Json::Value& aliases);
    static bool AliasExists(const std::string& alias);
    static void CreateBatchAlias(const std::string& alias, const std::string& command);
    static std::vector<std::string> SuggestCommands(const std::string& input);
    static void BulkAliasCreation(const std::vector<std::pair<std::string, std::string>>& aliases);
    static std::string translateAlias(const std::string& aliasDefinition); // Add this declaration

private:
    static std::unordered_map<std::string, std::string> ps_command_dict_;
};

#endif // ALIASMANAGER_H
