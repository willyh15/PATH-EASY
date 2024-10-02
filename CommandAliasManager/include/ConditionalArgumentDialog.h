#ifndef CONDITIONALARGUMENTDIALOG_H
#define CONDITIONALARGUMENTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMap>
#include <QString>
#include <QLabel>

// Structure to represent a conditional argument
struct ConditionalArgument {
  QString argumentName;   // Name of the argument
  QString condition;      // Condition for including this argument
  QString argumentValue;  // Value of the argument when the condition is met
};

// Conditional Argument Dialog Class
class ConditionalArgumentDialog : public QDialog {
  Q_OBJECT

public:
  ConditionalArgumentDialog(QWidget *parent = nullptr);

  // Set the condition for the dialog
  void setCondition(const QString &condition);

  // Get the defined condition
  QString getCondition() const;

  // Set the argument details
  void setArgumentDetails(const ConditionalArgument &argument);

  // Get the argument details
  ConditionalArgument getArgumentDetails() const;

  // Validate the entered condition
  bool validateCondition(const QString &condition) const;

private slots:
  // Slot to handle saving the condition and argument details
  void saveConditionalArgument();

private:
  // UI Setup
  void setupUI();
  void setupConnections();

  // UI Elements
  QLineEdit *argumentNameInput;         // Input field for argument name
  QLineEdit *argumentConditionInput;    // Input field for condition
  QTextEdit *argumentValueInput;        // Text area for argument value

  // Buttons for managing the dialog
  QPushButton *saveButton;

  // Argument structure for storing condition and value
  ConditionalArgument currentArgument;
};

#endif // CONDITIONALARGUMENTDIALOG_H
