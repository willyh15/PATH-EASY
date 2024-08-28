#pragma once

#include "pch.h"
#include <nana/gui.hpp>
#include <nana/gui/widgets/form.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/textbox.hpp>

class CPreferencesDlg {
public:
    CPreferencesDlg();
    ~CPreferencesDlg();

    void show();

private:
    void onSaveClicked();

    nana::form form_;
    nana::textbox preferences_input_;
    nana::button save_button_;
};