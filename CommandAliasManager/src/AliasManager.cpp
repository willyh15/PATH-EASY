#include "AliasManager.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <filesystem>
#include <sstream>
#include <regex>

// Define paths for storing alias data
#ifdef _WIN32
const std::string user_data_dir = std::string(getenv("APPDATA")) + "\\YourAppName\\";
#else
const std::string user_data_dir = std::string(getenv("HOME")) + "/.YourAppName/";
#endif

const std::string alias_file_path = user_data_dir + "aliases.json";
const std::string ps_commands_file_path = user_data_dir + "PowerShellCommands.csv";

// Static command dictionary for PowerShell commands
std::unordered_map<std::string, std::string> AliasManager::ps_command_dict_;

// Load aliases from the alias file
Json::Value AliasManager::LoadAliases() {
  std::ifstream file(alias_file_path, std::ifstream::binary);
  Json::Value aliases;
  if (file) {
    try {
      file >> aliases;
    } catch (const std::exception &e) {
      QMessageBox::critical(nullptr, "Error", "Failed to load aliases: " + QString::fromStdString(e.what()));
    }
  } else {
    QMessageBox::critical(nullptr, "Error", "Unable to open alias file for reading.");
  }
  return aliases;
}

// Save aliases to the alias file
void AliasManager::SaveAliases(const Json::Value &aliases) {
  std::ofstream file(alias_file_path, std::ofstream::binary);
  if (file) {
    try {
      file << aliases;
    } catch (const std::exception &e) {
      QMessageBox::critical(nullptr, "Error", "Failed to save aliases: " + QString::fromStdString(e.what()));
    }
  } else {
    QMessageBox::critical(nullptr, "Error", "Unable to open alias file for writing.");
  }
}

// Check if an alias already exists
bool AliasManager::AliasExists(const std::string &alias) {
  Json::Value aliases = LoadAliases();
  return !aliases[alias].isNull();
}

// Create a new alias with a given command
void AliasManager::CreateAlias(const std::string &alias, const std::string &command) {
  Json::Value aliases = LoadAliases();
  aliases[alias] = command;
  SaveAliases(aliases);
}

// Translate an alias to its corresponding command
std::string AliasManager::TranslateAlias(const std::string &aliasDefinition) {
  std::regex openPattern(R"(^open\s+(.+))");
  if (std::regex_match(aliasDefinition, openPattern)) {
    return "start " + aliasDefinition.substr(5);
  }
  return aliasDefinition;
}

// Bulk alias creation for batch operations
void AliasManager::BulkAliasCreation(const std::vector<std::pair<std::string, std::string>> &aliases) {
  Json::Value currentAliases = LoadAliases();
  for (const auto &[alias, command] : aliases) {
    currentAliases[alias] = command;
  }
  SaveAliases(currentAliases);
}

// Load PowerShell commands into the alias manager for suggestions
void AliasManager::LoadPowerShellCommands(const std::string &filepath) {
  std::ifstream file(filepath);
  if (!file.is_open()) {
    QMessageBox::critical(nullptr, "Error", "Failed to load PowerShell commands from file: " + QString::fromStdString(filepath));
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

// Suggest commands based on a partial input
std::vector<std::string> AliasManager::SuggestCommands(const std::string &input) {
  std::vector<std::string> suggestions;
  for (const auto &cmd : ps_command_dict_) {
    if (cmd.first.find(input) != std::string::npos) {
      suggestions.push_back(cmd.first);
    }
  }
  return suggestions;
}

// Helper function to get the alias file path
std::string AliasManager::GetAliasFilePath() {
  return alias_file_path;
}

// Helper function to get the PowerShell file path
std::string AliasManager::GetPowerShellFilePath() {
  return ps_commands_file_path;
}