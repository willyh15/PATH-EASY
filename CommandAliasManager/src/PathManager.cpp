#include "PathManager.h"
#include <QMessageBox>
#include <boost/filesystem.hpp>
#include <windows.h>
#include <algorithm>
#include <iostream>

bool PathManager::AddToPath(const std::string &directory) {
  if (!validatePath(directory)) {
    showError("Invalid directory: " + directory);
    return false;
  }

  std::string path = getCurrentPath();
  if (path.find(directory) != std::string::npos) {
    showMessage("Directory is already in PATH: " + directory);
    return false;
  }

  path += ";" + directory;
  if (updateSystemPath(path)) {
    showMessage("Successfully added to PATH: " + directory);
    return true;
  } else {
    showError("Failed to update PATH.");
    return false;
  }
}

// Scans common directories and suggests executable paths for addition
std::set<std::string> PathManager::scanAndSuggestPaths() {
  std::vector<std::string> common_dirs = {"C:\\Program Files", "C:\\Program Files (x86)", "C:\\Windows\\System32"};
  std::set<std::string> suggestions;

  for (const auto &dir : common_dirs) {
    if (boost::filesystem::exists(dir)) {
      for (boost::filesystem::recursive_directory_iterator it(dir), end; it != end; ++it) {
        if (boost::filesystem::is_regular_file(it->path()) && (it->path().extension() == ".exe")) {
          suggestions.insert(it->path().string());
        }
      }
    }
  }
  return suggestions;
}

// Adds multiple directories to PATH in a single batch operation
void PathManager::BatchAddToPath(const std::vector<std::string> &directories) {
  std::string path = getCurrentPath();
  for (const auto &dir : directories) {
    if (path.find(dir) == std::string::npos) {
      path += ";" + dir;
    }
  }

  if (updateSystemPath(path)) {
    showMessage("Successfully added all directories to PATH.");
  } else {
    showError("Failed to update PATH for some directories.");
  }
}

// Validates the directory path to ensure it exists and is accessible
bool PathManager::validatePath(const std::string &directory) {
  return boost::filesystem::exists(directory);
}

// Retrieves the current PATH environment variable
std::string PathManager::getCurrentPath() {
  std::string path;
  char *buffer = nullptr;
  size_t size = 0;

  if (_dupenv_s(&buffer, &size, "PATH") == 0 && buffer != nullptr) {
    path = buffer;
    free(buffer);
  } else {
    showError("Failed to retrieve the current PATH.");
  }

  return path;
}

// Updates the system PATH environment variable
bool PathManager::updateSystemPath(const std::string &newPath) {
  if (_putenv_s("PATH", newPath.c_str()) != 0) {
    return false;
  }

  // Windows-specific: Update the registry for permanent PATH changes
#ifdef _WIN32
  HKEY hKey;
  if (RegOpenKeyEx(HKEY_CURRENT_USER, "Environment", 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) {
    RegSetValueEx(hKey, "PATH", 0, REG_SZ, (const BYTE *)newPath.c_str(), (DWORD)(newPath.size() + 1));
    RegCloseKey(hKey);
  }
#endif
  return true;
}

// Show an information message box
void PathManager::showMessage(const std::string &message) {
  QMessageBox::information(nullptr, "Information", QString::fromStdString(message));
}

// Show an error message box
void PathManager::showError(const std::string &error) {
  QMessageBox::critical(nullptr, "Error", QString::fromStdString(error));
}