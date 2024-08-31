#include "ManageCommandsDialog.h"
#include <QVBoxLayout>
#include <QInputDialog>
#include <QMessageBox>

ManageCommandsDialog::ManageCommandsDialog(QWidget *parent) : QDialog(parent) {
    commandsList = new QListWidget(this);
    addButton = new QPushButton("Add", this);
    editButton = new QPushButton("Edit", this);
    removeButton = new QPushButton("Remove", this);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(commandsList);
    layout->addWidget(addButton);
    layout->addWidget(editButton);
    layout->addWidget(removeButton);
    setLayout(layout);

    connect(addButton, &QPushButton::clicked, this, &ManageCommandsDialog::addCommand);
    connect(editButton, &QPushButton::clicked, this, &ManageCommandsDialog::editCommand);
    connect(removeButton, &QPushButton::clicked, this, &ManageCommandsDialog::removeCommand);
}

QMap<QString, QString> ManageCommandsDialog::getCommands() const {
    return commandMap;
}

void ManageCommandsDialog::addCommand() {
    bool ok;
    QString commandName = QInputDialog::getText(this, "Add Command", "Command Name:", QLineEdit::Normal, "", &ok);
    if (!ok || commandName.isEmpty()) {
        QMessageBox::warning(this, "Error", "Command name cannot be empty.");
        return;
    }

    if (commandMap.contains(commandName)) {
        QMessageBox::warning(this, "Error", "A command with this name already exists.");
        return;
    }

    QString commandDefinition = QInputDialog::getText(this, "Add Command", "Command Definition:", QLineEdit::Normal, "", &ok);
    if (!ok || commandDefinition.isEmpty()) {
        QMessageBox::warning(this, "Error", "Command definition cannot be empty.");
        return;
    }

    QListWidgetItem *newItem = new QListWidgetItem(commandName, commandsList);
    newItem->setData(Qt::UserRole, commandDefinition);
    commandMap.insert(commandName, commandDefinition);
}

void ManageCommandsDialog::editCommand() {
    QListWidgetItem *currentItem = commandsList->currentItem();
    if (!currentItem) {
        QMessageBox::warning(this, "Warning", "Please select a command to edit.");
        return;
    }

    QString currentName = currentItem->text();
    QString currentDefinition = currentItem->data(Qt::UserRole).toString();

    bool ok;
    QString newDefinition = QInputDialog::getText(this, "Edit Command", "Command Definition:", QLineEdit::Normal, currentDefinition, &ok);
    if (!ok || newDefinition.isEmpty()) {
        QMessageBox::warning(this, "Error", "Command definition cannot be empty.");
        return;
    }

    currentItem->setData(Qt::UserRole, newDefinition);
    commandMap[currentName] = newDefinition;
}

void ManageCommandsDialog::removeCommand() {
    QListWidgetItem *currentItem = commandsList->currentItem();
    if (!currentItem) {
        QMessageBox::warning(this, "Warning", "Please select a command to remove.");
        return;
    }

    QString currentName = currentItem->text();
    commandMap.remove(currentName);
    delete commandsList->takeItem(commandsList->row(currentItem));
}