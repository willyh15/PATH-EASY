#ifndef PATHMANAGER_H
#define PATHMANAGER_H

#include <set>
#include <string>
#include <vector>

// PathManager Class: Handles operations on the system PATH variable
class PathManager {
public:
  // Add a directory to the system PATH variable
  static bool AddToPath(const std::string &directory);

  // Scan common directories and suggest executable paths
  static std::set<std::string> ScanAndSuggestPaths();

  // Batch add directories to the PATH
  static void BatchAddToPath(const std::vector<std::string> &directories);

  // Retrieve the current PATH environment variable
  static std::string GetCurrentPath();

  // Update the PATH environment variable
  static bool UpdatePath(const std::string &newPath);

private:
  // Helper function to check if a directory already exists in PATH
  static bool DirectoryExistsInPath(const std::string &directory, const std::string &pathVariable);
};

#endif // PATHMANAGER_H