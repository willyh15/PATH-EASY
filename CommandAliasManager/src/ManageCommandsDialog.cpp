#include "ManageCommandsDialog.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QVBoxLayout>

// Constructor
ManageCommandsDialog::ManageCommandsDialog(QWidget *parent) : QDialog(parent) {
  setupUI();
  setupConnections();
}

// Set up the user interface
void ManageCommandsDialog::setupUI() {
  setWindowTitle("Manage Commands");

  QVBoxLayout *layout = new QVBoxLayout(this);

  // Commands List
  commandsList = new QListWidget(this);
  layout->addWidget(commandsList);

  // Buttons for managing commands
  addButton = new QPushButton("Add", this);
  editButton = new QPushButton("Edit", this);
  removeButton = new QPushButton("Remove", this);

  QHBoxLayout *buttonLayout = new QHBoxLayout();
  buttonLayout->addWidget(addButton);
  buttonLayout->addWidget(editButton);
  buttonLayout->addWidget(removeButton);

  layout->addLayout(buttonLayout);
  setLayout(layout);
}

// Set up signal-slot connections
void ManageCommandsDialog::setupConnections() {
  connect(addButton, &QPushButton::clicked, this, &ManageCommandsDialog::addCommand);
  connect(editButton, &QPushButton::clicked, this, &ManageCommandsDialog::editCommand);
  connect(removeButton, &QPushButton::clicked, this, &ManageCommandsDialog::removeCommand);
}

// Retrieve the current command map
QMap<QString, QString> ManageCommandsDialog::getCommands() const {
  return commandMap;
}

// Accessor to get the commands list widget for external population
QListWidget *ManageCommandsDialog::getCommandsList() {
  return commandsList;
}

// Accessor to get the command map for modification
QMap<QString, QString> &ManageCommandsDialog::getCommandMap() {
  return commandMap;
}

// Slot to add a new command
void ManageCommandsDialog::addCommand() {
  bool ok;
  QString commandName = QInputDialog::getText(this, "Add Command", "Command Name:", QLineEdit::Normal, "", &ok);
  if (!ok || commandName.isEmpty()) {
    QMessageBox::warning(this, "Invalid Input", "Command name cannot be empty.");
    return;
  }

  if (commandMap.contains(commandName)) {
    QMessageBox::warning(this, "Duplicate Command", "A command with this name already exists.");
    return;
  }

  QString commandDefinition = QInputDialog::getText(this, "Add Command", "Command Definition:", QLineEdit::Normal, "", &ok);
  if (!ok || commandDefinition.isEmpty()) {
    QMessageBox::warning(this, "Invalid Input", "Command definition cannot be empty.");
    return;
  }

  // Add the new command to the list and map
  QListWidgetItem *newItem = new QListWidgetItem(commandName, commandsList);
  newItem->setData(Qt::UserRole, commandDefinition);
  commandMap.insert(commandName, commandDefinition);
}

// Slot to edit the currently selected command
void ManageCommandsDialog::editCommand() {
  QListWidgetItem *currentItem = commandsList->currentItem();
  if (!currentItem) {
    QMessageBox::warning(this, "No Selection", "Please select a command to edit.");
    return;
  }

  QString currentName = currentItem->text();
  QString currentDefinition = currentItem->data(Qt::UserRole).toString();

  bool ok;
  QString newDefinition = QInputDialog::getText(this, "Edit Command", "Command Definition:", QLineEdit::Normal, currentDefinition, &ok);
  if (!ok || newDefinition.isEmpty()) {
    QMessageBox::warning(this, "Invalid Input", "Command definition cannot be empty.");
    return;
  }

  // Update the command definition in the list and map
  currentItem->setData(Qt::UserRole, newDefinition);
  commandMap[currentName] = newDefinition;
}

// Slot to remove the currently selected command
void ManageCommandsDialog::removeCommand() {
  QListWidgetItem *currentItem = commandsList->currentItem();
  if (!currentItem) {
    QMessageBox::warning(this, "No Selection", "Please select a command to remove.");
    return;
  }

  QString currentName = currentItem->text();
  commandMap.remove(currentName);
  delete commandsList->takeItem(commandsList->row(currentItem));
}