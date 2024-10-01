#include "MainDlg.h"
#include "AliasManager.h"
#include "ManageCommandsDialog.h"
#include "PathManager.h"
#include <QFile>
#include <QInputDialog>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QTextStream>
#include <QVBoxLayout>

const QString COMMANDS_FILE_PATH = "commands.txt";

// Constructor: Initializes the main dialog with UI elements and loads existing
// commands
CMainDlg::CMainDlg() {
  setupUI();          // Setup UI components
  setupConnections(); // Setup signal-slot connections

  // Load existing commands and update the UI
  existingCommands = loadCommandsFromFile();
  UpdateAliasList();
}

// Destructor: Saves the commands to file on exit
CMainDlg::~CMainDlg() { saveCommandsToFile(existingCommands); }

// Sets up the UI elements and layout
void CMainDlg::setupUI() {
  aliasList = new QListWidget(this);
  QPushButton *manageCommandsButton = new QPushButton("Manage Commands", this);

  QVBoxLayout *layout = new QVBoxLayout();
  layout->addWidget(aliasList);
  layout->addWidget(manageCommandsButton);
  setLayout(layout);
}

// Sets up the connections between buttons and corresponding slots
void CMainDlg::setupConnections() {
  connect(manageCommandsButton, &QPushButton::clicked, this,
          &CMainDlg::onManageCommandsClicked);
}

// Save commands to file
void CMainDlg::saveCommandsToFile(const QMap<QString, QString> &commands) {
  QFile file(COMMANDS_FILE_PATH);
  if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    QTextStream out(&file);
    for (auto it = commands.begin(); it != commands.end(); ++it) {
      out << it.key() << ":" << it.value() << "\n";
    }
    file.close();
  } else {
    showError("Unable to save commands to file.");
  }
}

// Load commands from file
QMap<QString, QString> CMainDlg::loadCommandsFromFile() {
  QMap<QString, QString> commands;
  QFile file(COMMANDS_FILE_PATH);
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QTextStream in(&file);
    while (!in.atEnd()) {
      QString line = in.readLine();
      QStringList parts = line.split(":");
      if (parts.size() == 2) {
        commands.insert(parts[0], parts[1]);
      }
    }
    file.close();
  } else {
    showError("Unable to load commands from file.");
  }
  return commands;
}

// Handles the "Manage Commands" button click
void CMainDlg::onManageCommandsClicked() {
  ManageCommandsDialog dialog(this);

  populateDialogWithExistingCommands(
      dialog); // Populate the dialog with current commands

  if (dialog.exec() == QDialog::Accepted) {
    QMap<QString, QString> updatedCommands = dialog.getCommands();
    existingCommands = updatedCommands;
    UpdateAliasList();
    saveCommandsToFile(existingCommands);
    showMessage("The commands have been updated successfully.");
  }
}

// Updates the alias list displayed in the UI
void CMainDlg::UpdateAliasList() {
  aliasList->clear();
  for (auto it = existingCommands.begin(); it != existingCommands.end(); ++it) {
    QListWidgetItem *item = new QListWidgetItem(it.key());
    item->setData(Qt::UserRole, it.value());
    aliasList->addItem(item);
  }
}

// Populates the ManageCommandsDialog with the existing commands
void CMainDlg::populateDialogWithExistingCommands(
    ManageCommandsDialog &dialog) {
  for (auto it = existingCommands.begin(); it != existingCommands.end(); ++it) {
    dialog.getCommandsList()->addItem(new QListWidgetItem(it.key()));
    dialog.getCommandMap().insert(it.key(), it.value());
  }
}

// Displays a simple message box for information
void CMainDlg::showMessage(const QString &message) {
  QMessageBox::information(this, "Information", message);
}

// Displays a simple error message box
void CMainDlg::showError(const QString &error) {
  QMessageBox::warning(this, "Error", error);
}