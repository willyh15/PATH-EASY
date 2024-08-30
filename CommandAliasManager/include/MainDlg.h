#ifndef MAINDLG_H
#define MAINDLG_H

#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/combox.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/widgets/treebox.hpp>

class CMainDlg {
public:
    CMainDlg();
    ~CMainDlg();
    void show();

private:
    void onAddToPathClicked();
    void onAddAliasClicked();
    void UpdateAliasList();
    void onPathInputChanged();
    void onBrowseClicked();
    void onPreferencesClicked();
    void onManageCommandsClicked();
    
    // UI components
    nana::form form_;
    nana::button browse_button_, preferences_button_, manage_commands_button_, add_to_path_button_, add_alias_button_;
    nana::textbox alias_input_;
    nana::combox path_input_combo_, command_input_combo_;
    nana::listbox directory_list_, alias_list_;
    nana::treebox directory_tree_;
};

#endif // MAINDLG_H