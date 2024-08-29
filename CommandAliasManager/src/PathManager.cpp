// PathManager.cpp
#include "PathManager.h"
#include <windows.h>
#include <iostream>
#include <nana/gui/msgbox.hpp>

// Adds a directory to the system PATH
bool PathManager::AddToPath(const std::string& directory) {
    std::string path;
    char* buffer = nullptr;
    size_t size = 0;

    // Get the current PATH
    if (_dupenv_s(&buffer, &size, "PATH") == 0 && buffer != nullptr) {
        path = buffer;
        free(buffer);
    } else {
        nana::msgbox m("Error");
        m << "Failed to retrieve the current PATH.";
        m.show();
        return false;
    }

    // Check if the directory is already in the PATH
    if (path.find(directory) != std::string::npos) {
        nana::msgbox m("Information");
        m << "Directory is already in PATH.";
        m.show();
        return false;
    }

    // Append the new directory to the PATH
    path += ";" + directory;
    if (_putenv_s("PATH", path.c_str()) != 0) {
        nana::msgbox m("Error");
        m << "Failed to update PATH.";
        m.show();
        return false;
    }

    nana::msgbox m("Success");
    m << "Successfully added to PATH.";
    m.show();
    return true;
}