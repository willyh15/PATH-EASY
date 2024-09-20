#include "PathManager.h"
#include <QMessageBox>
#include <boost/filesystem.hpp>
#include <windows.h>

bool PathManager::AddToPath(const std::string &directory) {
  std::string path;
  char *buffer = nullptr;
  size_t size = 0;

  if (_dupenv_s(&buffer, &size, "PATH") == 0 && buffer != nullptr) {
    path = buffer;
    free(buffer);
  } else {
    QMessageBox::critical(nullptr, "Error",
                          "Failed to retrieve the current PATH.");
    return false;
  }

  if (path.find(directory) != std::string::npos) {
    QMessageBox::information(nullptr, "Information",
                             "Directory is already in PATH.");
    return false;
  }

  path += ";" + directory;
  if (_putenv_s("PATH", path.c_str()) != 0) {
    QMessageBox::critical(nullptr, "Error", "Failed to update PATH.");
    return false;
  }

  QMessageBox::information(nullptr, "Success", "Successfully added to PATH.");
  return true;
}

std::set<std::string> PathManager::scanAndSuggestPaths() {
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

void PathManager::BatchAddToPath(const std::vector<std::string> &directories) {
  for (const auto &dir : directories) {
    AddToPath(dir);
  }
}