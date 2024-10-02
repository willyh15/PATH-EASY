#include "PathManager.h"
#include <QMessageBox>
#include <boost/filesystem.hpp>
#include <cstdlib>
#include <windows.h>

// Add a directory to the system PATH variable
bool PathManager::AddToPath(const std::string &directory) {
  std::string currentPath = GetCurrentPath();
  if (DirectoryExistsInPath(directory, currentPath)) {
    QMessageBox::information(nullptr, "Information",
                             "Directory is already in PATH.");
    return false;
  }

  currentPath += ";" + directory;
  return UpdatePath(currentPath);
}

// Scan common directories and suggest executable paths
std::set<std::string> PathManager::ScanAndSuggestPaths() {
  std::vector<std::string> common_dirs = {
      "C:\\Program Files", "C:\\Program Files (x86)", "C:\\Windows\\System32"};
  std::set<std::string> suggestions;

  for (const auto &dir : common_dirs) {
    if (boost::filesystem::exists(dir)) {
      for (boost::filesystem::recursive_directory_iterator it(dir), end;
           it != end; ++it) {
        if (boost::filesystem::is_regular_file(it->path()) &&
            (it->path().extension() == ".exe")) {
          suggestions.insert(it->path().string());
        }
      }
    }
  }

  return suggestions;
}

// Batch add directories to the PATH variable
void PathManager::BatchAddToPath(const std::vector<std::string> &directories) {
  for (const auto &dir : directories) {
    AddToPath(dir);
  }
}

// Retrieve the current PATH environment variable
std::string PathManager::GetCurrentPath() {
  std::string path;
  char *buffer = nullptr;
  size_t size = 0;

  if (_dupenv_s(&buffer, &size, "PATH") == 0 && buffer != nullptr) {
    path = buffer;
    free(buffer);
  } else {
    QMessageBox::critical(nullptr, "Error",
                          "Failed to retrieve the current PATH.");
  }
  return path;
}

// Update the PATH environment variable
bool PathManager::UpdatePath(const std::string &newPath) {
  if (_putenv_s("PATH", newPath.c_str()) != 0) {
    QMessageBox::critical(nullptr, "Error", "Failed to update PATH.");
    return false;
  }

  QMessageBox::information(nullptr, "Success", "Successfully updated PATH.");
  return true;
}

// Check if a directory already exists in the PATH variable
bool PathManager::DirectoryExistsInPath(const std::string &directory,
                                        const std::string &pathVariable) {
  size_t pos = pathVariable.find(directory);
  if (pos == std::string::npos) {
    return false;
  }

  // Ensure it's not a substring of another path
  if ((pos > 0 && pathVariable[pos - 1] != ';') ||
      (pos + directory.length() < pathVariable.length() &&
       pathVariable[pos + directory.length()] != ';')) {
    return false;
  }
  return true;
}