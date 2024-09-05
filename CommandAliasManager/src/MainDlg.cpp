#include "MainDlg.h"
#include "ManageCommandsDialog.h"
#include "AliasManager.h"
#include "PathManager.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QInputDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>

const QString COMMANDS_FILE_PATH = "commands.txt";

CMainDlg::CMainDlg() {
    // Set up UI
    aliasList = new QListWidget(this);
    QPushButton *manageCommandsButton = new QPushButton("Manage Commands", this);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(aliasList);
    layout->addWidget(manageCommandsButton);
    setLayout(layout);

    // Connect signals to slots
    connect(manageCommandsButton, &QPushButton::clicked, this, &CMainDlg::onManageCommandsClicked);

    // Load existing commands on startup
    existingCommands = loadCommandsFromFile();
    UpdateAliasList();
}

CMainDlg::~CMainDlg() {
    saveCommandsToFile(existingCommands);
}

void CMainDlg::saveCommandsToFile(const QMap<QString, QString>& commands) {
    QFile file(COMMANDS_FILE_PATH);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (auto it = commands.begin(); it != commands.end(); ++it) {
            out << it.key() << ":" << it.value() << "\n";
        }
        file.close();
    } else {
        QMessageBox::warning(this, "Error", "Unable to save commands to file.");
    }
}

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
        QMessageBox::warning(this, "Error", "Unable to load commands from file.");
    }
    return commands;
}

void CMainDlg::onManageCommandsClicked() {
    ManageCommandsDialog dialog(this);

    // Use getters to access private members
    for (auto it = existingCommands.begin(); it != existingCommands.end(); ++it) {
        dialog.getCommandsList()->addItem(new QListWidgetItem(it.key()));
        dialog.getCommandMap().insert(it.key(), it.value());
    }

    if (dialog.exec() == QDialog::Accepted) {
        QMap<QString, QString> updatedCommands = dialog.getCommands();
        existingCommands = updatedCommands;
        UpdateAliasList();
        saveCommandsToFile(existingCommands);
        QMessageBox::information(this, "Commands Updated", "The commands have been updated successfully.");
    }
}

void CMainDlg::UpdateAliasList() {
    aliasList->clear();
    for (auto it = existingCommands.begin(); it != existingCommands.end(); ++it) {
        QListWidgetItem *item = new QListWidgetItem(it.key());
        item->setData(Qt::UserRole, it.value());
        aliasList->addItem(item);
    }
}
