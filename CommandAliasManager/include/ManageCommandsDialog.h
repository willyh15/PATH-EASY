#ifndef MANAGECOMMANDSDIALOG_H
#define MANAGECOMMANDSDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QPushButton>
#include <QMap>

class ManageCommandsDialog : public QDialog {
    Q_OBJECT

public:
    explicit ManageCommandsDialog(QWidget *parent = nullptr);
    QMap<QString, QString> getCommands() const;

private slots:
    void addCommand();
    void editCommand();
    void removeCommand();

private:
    QListWidget *commandsList;
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *removeButton;
    QMap<QString, QString> commandMap;

    // Add getters for private members
public:
    QListWidget* getCommandsList() const { return commandsList; }
    QMap<QString, QString>& getCommandMap() { return commandMap; }
};

#endif // MANAGECOMMANDSDIALOG_H
