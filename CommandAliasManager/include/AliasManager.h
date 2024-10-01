#ifndef ALIASMANAGER_H
#define ALIASMANAGER_H

#include <fstream>
#include <json/json.h> // Assuming you're using JsonCpp for handling JSON files
#include <string>
#include <unordered_map>
#include <vector>

class AliasManager {
public:
  static void LoadPowerShellCommands(const std::string &filepath);
  static std::vector<std::string> SuggestCommands(const std::string &input);
  static void SaveAliases(const Json::Value &aliases);
  static Json::Value LoadAliases();
  static bool AliasExists(const std::string &alias);
  static void CreateBatchAlias(const std::string &alias,
                               const std::string &command);
  static void BulkAliasCreation(
      const std::vector<std::pair<std::string, std::string>> &aliases);
  static std::string translateAlias(const std::string &aliasDefinition);

private:
  static std::unordered_map<std::string, std::string> ps_command_dict_;
};

#endif // ALIASMANAGER_H