#include "MainDlg.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  CMainDlg mainDialog;
  mainDialog.show();
  return app.exec();
}
