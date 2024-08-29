// PathManager.h
#pragma once
#include <string>

class PathManager {
public:
    // Adds a directory to the system PATH
    static bool AddToPath(const std::string& directory);
};