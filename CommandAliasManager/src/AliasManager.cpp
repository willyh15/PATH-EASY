#include "AliasManager.h"
#include <filesystem>
#include <regex>
#include <sstream>
#include <algorithm> // For std::transform
#include <QMessageBox>

#ifdef _WIN32
const std::string user_data_dir = std::string(getenv("APPDATA")) + "\\CommandAliasManager\\";
#else
const std::string user_data_dir = std::string(getenv("HOME")) + "/.CommandAliasManager/";
#endif

const std::string alias_file_path = user_data_dir + "aliases.json";
const std::string ps_commands_file_path = user_data_dir + "PowerShellCommands.csv";

std::unordered_map<std::string, std::string> AliasManager::ps_command_dict_;

// Load PowerShell commands into a command dictionary
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

// Improved suggestion mechanism using fuzzy matching and filtering
std::vector<std::string> AliasManager::SuggestCommands(const std::string &input) {
  std::vector<std::string> suggestions;

  // Convert input to lowercase for case-insensitive matching
  std::string loweredInput = input;
  std::transform(loweredInput.begin(), loweredInput.end(), loweredInput.begin(), ::tolower);

  for (const auto &cmd : ps_command_dict_) {
    std::string loweredCmd = cmd.first;
    std::transform(loweredCmd.begin(), loweredCmd.end(), loweredCmd.begin(), ::tolower);
    
    // Use simple fuzzy matching (contains the input substring)
    if (loweredCmd.find(loweredInput) != std::string::npos) {
      suggestions.push_back(cmd.first);
    }
  }

  // Sort suggestions based on length and relevance
  std::sort(suggestions.begin(), suggestions.end(), [](const std::string &a, const std::string &b) {
    return a.length() < b.length(); // Shorter commands have higher priority
  });

  return suggestions;
}

// Load aliases from a JSON file
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

// Save aliases to a JSON file
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

// Check if an alias already exists in the JSON
bool AliasManager::AliasExists(const std::string &alias) {
  Json::Value aliases = LoadAliases();
  return !aliases[alias].isNull();
}

// Create a batch alias and save to the JSON file
void AliasManager::CreateBatchAlias(const std::string &alias, const std::string &command) {
  Json::Value aliases = LoadAliases();
  aliases[alias] = command;
  SaveAliases(aliases);
}

// Translate alias definitions with regex support for advanced rules
std::string AliasManager::translateAlias(const std::string &aliasDefinition) {
  std::regex openPattern(R"(^open\s+(.+))");
  if (std::regex_match(aliasDefinition, openPattern)) {
    return "start " + aliasDefinition.substr(5);
  }
  return aliasDefinition;
}

// Create multiple aliases at once and save them to the JSON file
void AliasManager::BulkAliasCreation(const std::vector<std::pair<std::string, std::string>> &aliases) {
  Json::Value aliasJson = LoadAliases();
  for (const auto &[alias, command] : aliases) {
    aliasJson[alias] = command;
  }
  SaveAliases(aliasJson);
}