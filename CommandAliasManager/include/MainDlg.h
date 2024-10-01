#ifndef MAINDLG_H
#define MAINDLG_H

#include <QDialog>
#include <QListWidget>
#include <QMap>

class CMainDlg : public QDialog {
  Q_OBJECT

public:
  CMainDlg();  // Constructor
  ~CMainDlg(); // Destructor

private slots:
  void onManageCommandsClicked(); // Slot for managing commands
  void UpdateAliasList();         // Updates the alias list UI

private:
  void saveCommandsToFile(const QMap<QString, QString> &commands);
  QMap<QString, QString> loadCommandsFromFile();

  // Member variables
  QListWidget *aliasList; // UI element for displaying command aliases
  QMap<QString, QString> existingCommands;
};

#endif // MAINDLG_H