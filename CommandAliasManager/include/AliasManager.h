#ifndef ALIASMANAGER_H
#define ALIASMANAGER_H

#include <QMap>
#include <QString>
#include <QMessageBox>
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <json/json.h>

// AliasManager Class: Handles alias creation, management, and translation
class AliasManager {
public:
  // Load aliases from the alias file
  static Json::Value LoadAliases();

  // Save aliases to the alias file
  static void SaveAliases(const Json::Value &aliases);

  // Check if an alias exists
  static bool AliasExists(const std::string &alias);

  // Create a new alias with a given command
  static void CreateAlias(const std::string &alias, const std::string &command);

  // Translate an alias to its corresponding command
  static std::string TranslateAlias(const std::string &aliasDefinition);

  // Bulk alias creation for batch operations
  static void BulkAliasCreation(const std::vector<std::pair<std::string, std::string>> &aliases);

  // Load PowerShell commands into the alias manager for suggestions
  static void LoadPowerShellCommands(const std::string &filepath);

  // Suggest commands based on a partial input
  static std::vector<std::string> SuggestCommands(const std::string &input);

private:
  // Private helper functions for internal file handling
  static std::string GetAliasFilePath();
  static std::string GetPowerShellFilePath();

  // Command dictionary for PowerShell commands
  static std::unordered_map<std::string, std::string> ps_command_dict_;
};

#endif // ALIASMANAGER_H