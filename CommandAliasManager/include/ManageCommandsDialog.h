#ifndef MANAGECOMMANDSDIALOG_H
#define MANAGECOMMANDSDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMap>
#include <QString>

// ManageCommandsDialog Class: Manages the addition, editing, and removal of commands
class ManageCommandsDialog : public QDialog {
  Q_OBJECT

public:
  // Constructor
  ManageCommandsDialog(QWidget *parent = nullptr);

  // Retrieve the command map
  QMap<QString, QString> getCommands() const;

  // Accessor to get the commands list widget for external population
  QListWidget *getCommandsList();

  // Accessor to get the command map for modification
  QMap<QString, QString> &getCommandMap();

private slots:
  // Slot to add a new command
  void addCommand();

  // Slot to edit the currently selected command
  void editCommand();

  // Slot to remove the currently selected command
  void removeCommand();

private:
  // UI Setup
  void setupUI();
  void setupConnections();

  // UI Elements
  QListWidget *commandsList;     // List widget for displaying commands
  QPushButton *addButton;        // Button to add a new command
  QPushButton *editButton;       // Button to edit the selected command
  QPushButton *removeButton;     // Button to remove the selected command

  // Command Map: Holds command name and its corresponding definition
  QMap<QString, QString> commandMap;
};

#endif // MANAGECOMMANDSDIALOG_H