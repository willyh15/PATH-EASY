#ifndef MAINDLG_H
#define MAINDLG_H

#include <QListWidget>
#include <QMainWindow>
#include <QMap>

class CMainDlg : public QMainWindow {
  Q_OBJECT

public:
  CMainDlg();
  ~CMainDlg();

private slots:
  void onAddToPathClicked();
  void onAddAliasClicked();
  void onPathInputChanged();
  void onBrowseClicked();
  void onPreferencesClicked();
  void onManageCommandsClicked();
  void UpdateAliasList();

private:
  void saveCommandsToFile(const QMap<QString, QString> &commands);
  QMap<QString, QString> loadCommandsFromFile();

  // UI components
  QListWidget *aliasList;
  QMap<QString, QString> existingCommands; // Store commands in the main dialog
};

#endif // MAINDLG_H