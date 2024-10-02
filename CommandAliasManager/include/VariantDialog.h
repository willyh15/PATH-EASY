#ifndef VARIANTDIALOG_H
#define VARIANTDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QMap>
#include <QLabel>
#include "CommandTemplate.h"

// Data structure for storing a command variant
struct CommandVariant {
  QString variantName;       // Variant name
  QString condition;         // Condition for using this variant
  QString commandStructure;  // Command structure for this variant
  QStringList placeholders;  // Placeholders specific to this variant
  QList<CommandVariant> nestedVariants;  // Nested variants within this variant
};

// Variant Management Dialog Class
class VariantDialog : public QDialog {
  Q_OBJECT

public:
  VariantDialog(QWidget *parent = nullptr);

  // Set the list of variants for the selected template
  void setVariants(const QList<CommandVariant> &variants);

  // Get the updated list of variants
  QList<CommandVariant> getVariants() const;

private slots:
  // Slot to add a new variant
  void addVariant();

  // Slot to save changes to the current variant
  void saveVariant();

  // Slot to delete the selected variant
  void deleteVariant();

  // Slot to handle variant selection
  void onVariantSelected(QListWidgetItem *item);

private:
  // UI Setup
  void setupUI();
  void setupConnections();

  // Helper function to update the variant list
  void updateVariantList();

  // Helper function to clear variant details
  void clearVariantDetails();

  // UI Elements
  QList<CommandVariant> commandVariants;  // List of command variants
  int selectedVariantIndex;               // Index of the currently selected variant

  QListWidget *variantList;               // List widget for displaying variants
  QLineEdit *variantName;                 // Input field for variant name
  QLineEdit *variantCondition;            // Input field for variant condition
  QTextEdit *variantCommandStructure;     // Text area for the command structure
};

#endif // VARIANTDIALOG_H
