#ifndef MANAGECOMMANDSDIALOG_H
#define MANAGECOMMANDSDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QMap>
#include <QPushButton>

class ManageCommandsDialog : public QDialog {
  Q_OBJECT

public:
  explicit ManageCommandsDialog(QWidget *parent = nullptr);
  QMap<QString, QString> getCommands() const; // Returns the current command map

  // Getter for accessing the commands list UI element from outside
  QListWidget *getCommandsList() { return commandsList; }
  QMap<QString, QString> &getCommandMap() { return commandMap; }

private slots:
  void addCommand();    // Slot for adding a command
  void editCommand();   // Slot for editing a command
  void removeCommand(); // Slot for removing a command

private:
  // Member variables
  QListWidget *commandsList;
  QPushButton *addButton;
  QPushButton *editButton;
  QPushButton *removeButton;
  QMap<QString, QString> commandMap; // Stores the command name-definition pairs
};

#endif // MANAGECOMMANDSDIALOG_H