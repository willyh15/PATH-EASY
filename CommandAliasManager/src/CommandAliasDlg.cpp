#include "CommandAliasDlg.h"
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <fstream>

CCommandAliasDlg::CCommandAliasDlg() {
    form_.caption("Command Alias Manager");
    
    list_commands_.create(form_);
    list_commands_.append_header("Commands", 150);

    command_input_.create(form_);

    btn_add_.create(form_);
    btn_add_.caption("Add");
    btn_add_.events().click([this] {
        std::wstring command = command_input_.caption_wstring();
        if (!command.empty()) {
            addCommand(command);
            command_input_.caption(L"");
        }
    });

    btn_edit_.create(form_);
    btn_edit_.caption("Edit");
    btn_edit_.events().click([this] {
        auto index = list_commands_.selected();
        if (!index.empty()) {
            auto selected = index.front();
            editCommand(selected.item, command_input_.caption_wstring());
        }
    });

    btn_delete_.create(form_);
    btn_delete_.caption("Delete");
    btn_delete_.events().click([this] {
        auto index = list_commands_.selected();
        if (!index.empty()) {
            auto selected = index.front();
            deleteCommand(selected.item);
        }
    });

    // Layout
    form_.div("<vertical <list_commands weight=80%> <weight=10% <command_input> <weight=10% <btn_add> <btn_edit> <btn_delete>>>>");
    form_["list_commands"] << list_commands_;
    form_["command_input"] << command_input_;
    form_["btn_add"] << btn_add_;
    form_["btn_edit"] << btn_edit_;
    form_["btn_delete"] << btn_delete_;
    form_.collocate();
}

CCommandAliasDlg::~CCommandAliasDlg() {}

void CCommandAliasDlg::show() {
    form_.show();
    nana::exec();
}

void CCommandAliasDlg::addCommand(const std::wstring& command) {
    commands_.push_back(command);
    list_commands_.at(0).append(command);
    // SaveCommands(); // Implement saving logic using Boost or standard C++ I/O
}

void CCommandAliasDlg::editCommand(size_t index, const std::wstring& command) {
    if (index < commands_.size()) {
        commands_[index] = command;
        list_commands_.at(0).at(index).text(command);
        // SaveCommands();
    }
}

void CCommandAliasDlg::deleteCommand(size_t index) {
    if (index < commands_.size()) {
        commands_.erase(commands_.begin() + index);
        list_commands_.at(0).erase(index);
        // SaveCommands();
    }
}