// PathManager.cpp
#include "PathManager.h"
#include <windows.h>
#include <iostream>

// Adds a directory to the system PATH
bool PathManager::AddToPath(const std::string& directory) {
    std::string path;
    char* buffer = nullptr;
    size_t size = 0;

    // Get the current PATH
    if (_dupenv_s(&buffer, &size, "PATH") == 0 && buffer != nullptr) {
        path = buffer;
        free(buffer);
    }

    // Check if the directory is already in the PATH
    if (path.find(directory) != std::string::npos) {
        std::cout << "Directory is already in PATH." << std::endl;
        return false;
    }

    // Append the new directory to the PATH
    path += ";" + directory;
    if (_putenv_s("PATH", path.c_str()) != 0) {
        std::cerr << "Failed to update PATH." << std::endl;
        return false;
    }

    std::cout << "Successfully added to PATH." << std::endl;
    return true;
}