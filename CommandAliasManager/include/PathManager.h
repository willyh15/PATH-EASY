#ifndef PATHMANAGER_H
#define PATHMANAGER_H

#include <string>
#include <set>
#include <vector>

class PathManager {
public:
    static bool AddToPath(const std::string& directory);
    static std::set<std::string> scanAndSuggestPaths();
    static void BatchAddToPath(const std::vector<std::string>& directories);
};

#endif // PATHMANAGER_H