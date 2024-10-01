#include "ManageCommandsDialog.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QSortFilterProxyModel>
#include <QLineEdit>

// Constructor: Sets up the command management dialog with UI components
ManageCommandsDialog::ManageCommandsDialog(QWidget *parent) : QDialog(parent) {
  commandsList = new QListWidget(this);
  addButton = new QPushButton("Add", this);
  editButton = new QPushButton("Edit", this);
  removeButton = new QPushButton("Remove", this);
  filterBox = new QLineEdit(this);

  QVBoxLayout *layout = new QVBoxLayout();
  layout->addWidget(filterBox);
  layout->addWidget(commandsList);
  layout->addWidget(addButton);
  layout->addWidget(editButton);
  layout->addWidget(removeButton);
  setLayout(layout);

  // Set up connections for buttons
  connect(addButton, &QPushButton::clicked, this, &ManageCommandsDialog::addCommand);
  connect(editButton, &QPushButton::clicked, this, &ManageCommandsDialog::editCommand);
  connect(removeButton, &QPushButton::clicked, this, &ManageCommandsDialog::removeCommand);

  // Setup filtering functionality
  connect(filterBox, &QLineEdit::textChanged, this, &ManageCommandsDialog::filterCommands);

  // Real-time validation and suggestions
  filterBox->setPlaceholderText("Search or filter commands...");
}

// Returns the current command map
QMap<QString, QString> ManageCommandsDialog::getCommands() const {
  return commandMap;
}

// Add a new command with validation and suggestions
void ManageCommandsDialog::addCommand() {
  bool ok;
  QString commandName = QInputDialog::getText(this, "Add Command", "Command Name:", QLineEdit::Normal, "", &ok);
  
  // Validate the command name
  if (!ok || commandName.isEmpty()) {
    showError("Command name cannot be empty.");
    return;
  }

  if (commandMap.contains(commandName)) {
    showError("A command with this name already exists.");
    return;
  }

  QString commandDefinition = QInputDialog::getText(this, "Add Command", "Command Definition:", QLineEdit::Normal, "", &ok);
  
  // Validate the command definition
  if (!ok || commandDefinition.isEmpty()) {
    showError("Command definition cannot be empty.");
    return;
  }

  // Create and add a new command item
  QListWidgetItem *newItem = new QListWidgetItem(commandName, commandsList);
  newItem->setData(Qt::UserRole, commandDefinition);
  commandMap.insert(commandName, commandDefinition);
}

// Edit an existing command
void ManageCommandsDialog::editCommand() {
  QListWidgetItem *currentItem = commandsList->currentItem();
  if (!currentItem) {
    showError("Please select a command to edit.");
    return;
  }

  QString currentName = currentItem->text();
  QString currentDefinition = currentItem->data(Qt::UserRole).toString();

  bool ok;
  QString newDefinition = QInputDialog::getText(this, "Edit Command", "Command Definition:", QLineEdit::Normal, currentDefinition, &ok);
  
  // Validate the new definition
  if (!ok || newDefinition.isEmpty()) {
    showError("Command definition cannot be empty.");
    return;
  }

  currentItem->setData(Qt::UserRole, newDefinition);
  commandMap[currentName] = newDefinition;
}

// Remove the selected command
void ManageCommandsDialog::removeCommand() {
  QListWidgetItem *currentItem = commandsList->currentItem();
  if (!currentItem) {
    showError("Please select a command to remove.");
    return;
  }

  QString currentName = currentItem->text();
  commandMap.remove(currentName);
  delete commandsList->takeItem(commandsList->row(currentItem));
}

// Filter commands in real-time based on the text input
void ManageCommandsDialog::filterCommands(const QString &text) {
  for (int i = 0; i < commandsList->count(); ++i) {
    QListWidgetItem *item = commandsList->item(i);
    if (item->text().contains(text, Qt::CaseInsensitive)) {
      item->setHidden(false); // Show matching items
    } else {
      item->setHidden(true); // Hide non-matching items
    }
  }
}

// Show a simple error message
void ManageCommandsDialog::showError(const QString &error) {
  QMessageBox::warning(this, "Error", error);
}