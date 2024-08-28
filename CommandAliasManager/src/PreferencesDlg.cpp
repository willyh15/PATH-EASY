#include "PreferencesDlg.h"

CPreferencesDlg::CPreferencesDlg() {
    form_.caption("Preferences");

    preferences_input_.create(form_);
    save_button_.create(form_);
    save_button_.caption("Save");

    save_button_.events().click([this] {
        onSaveClicked();
    });

    form_.div("<vertical <preferences_input><save_button>>");
    form_["preferences_input"] << preferences_input_;
    form_["save_button"] << save_button_;
    form_.collocate();
}

CPreferencesDlg::~CPreferencesDlg() {}

void CPreferencesDlg::show() {
    form_.show();
    nana::exec();
}

void CPreferencesDlg::onSaveClicked() {
    // Save preferences logic here
}