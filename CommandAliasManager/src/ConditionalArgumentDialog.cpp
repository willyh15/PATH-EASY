#include "ConditionalArgumentDialog.h"
#include <QMessageBox>
#include <QRegExp>

// Constructor
ConditionalArgumentDialog::ConditionalArgumentDialog(QWidget *parent)
    : QDialog(parent) {
  setupUI();
  setupConnections();
}

// Set up the user interface
void ConditionalArgumentDialog::setupUI() {
  setWindowTitle("Define Conditional Argument");

  QVBoxLayout *layout = new QVBoxLayout(this);

  // Argument Name Input
  layout->addWidget(new QLabel("Argument Name:", this));
  argumentNameInput = new QLineEdit(this);
  layout->addWidget(argumentNameInput);

  // Condition Input
  layout->addWidget(new QLabel("Condition (e.g., {placeholder} == value):", this));
  argumentConditionInput = new QLineEdit(this);
  layout->addWidget(argumentConditionInput);

  // Argument Value Input
  layout->addWidget(new QLabel("Argument Value (applied if condition is met):", this));
  argumentValueInput = new QTextEdit(this);
  layout->addWidget(argumentValueInput);

  // Save Button
  saveButton = new QPushButton("Save Conditional Argument", this);
  layout->addWidget(saveButton);

  setLayout(layout);
}

// Set up signal-slot connections
void ConditionalArgumentDialog::setupConnections() {
  connect(saveButton, &QPushButton::clicked, this, &ConditionalArgumentDialog::saveConditionalArgument);
}

// Set the condition for the dialog
void ConditionalArgumentDialog::setCondition(const QString &condition) {
  argumentConditionInput->setText(condition);
}

// Get the defined condition
QString ConditionalArgumentDialog::getCondition() const {
  return argumentConditionInput->text().trimmed();
}

// Set the argument details
void ConditionalArgumentDialog::setArgumentDetails(const ConditionalArgument &argument) {
  currentArgument = argument;

  // Set UI elements with argument details
  argumentNameInput->setText(currentArgument.argumentName);
  argumentConditionInput->setText(currentArgument.condition);
  argumentValueInput->setPlainText(currentArgument.argumentValue);
}

// Get the argument details
ConditionalArgument ConditionalArgumentDialog::getArgumentDetails() const {
  ConditionalArgument argument;
  argument.argumentName = argumentNameInput->text().trimmed();
  argument.condition = argumentConditionInput->text().trimmed();
  argument.argumentValue = argumentValueInput->toPlainText().trimmed();
  return argument;
}

// Validate the entered condition
bool ConditionalArgumentDialog::validateCondition(const QString &condition) const {
  // Simple validation: Check if the condition has the format {placeholder} == value
  QRegExp conditionRegex(R"(\{(\w+)\}\s*==\s*(\w+))");
  if (!conditionRegex.exactMatch(condition)) {
    return false;
  }

  // Ensure the placeholder and value are not empty
  QString placeholder = conditionRegex.cap(1);
  QString value = conditionRegex.cap(2);
  return !placeholder.isEmpty() && !value.isEmpty();
}

// Slot to handle saving the condition and argument details
void ConditionalArgumentDialog::saveConditionalArgument() {
  QString condition = getCondition();
  if (!validateCondition(condition)) {
    QMessageBox::warning(this, "Invalid Condition",
                         "The condition must follow the format: {placeholder} == value");
    return;
  }

  // Save the argument details if validation passes
  currentArgument.argumentName = argumentNameInput->text().trimmed();
  currentArgument.condition = condition;
  currentArgument.argumentValue = argumentValueInput->toPlainText().trimmed();
  
  if (currentArgument.argumentName.isEmpty() || currentArgument.argumentValue.isEmpty()) {
    QMessageBox::warning(this, "Incomplete Argument",
                         "Both the argument name and value must be specified.");
    return;
  }

  accept();  // Close the dialog and indicate success
}
