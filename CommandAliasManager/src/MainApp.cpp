#include <nana/gui.hpp>
#include "MainDlg.h"

int main() {
    CMainDlg mainDialog;
    mainDialog.show();
    nana::exec(); // Start the Nana event loop
    return 0;
}