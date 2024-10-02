#ifndef NESTEDVARIANTDIALOG_H
#define NESTEDVARIANTDIALOG_H

#include "CommandTemplate.h"
#include <QDialog>
#include <QLineEdit>
#include <QListWidget>
#include <QMap>
#include <QPushButton>
#include <QTextEdit>
#include <QTreeWidget>
#include <QVBoxLayout>

// Data structure for storing a nested command variant
struct CommandVariant {
  QString variantName;                  // Variant name
  QString condition;                    // Condition for using this variant
  QString commandStructure;             // Command structure for this variant
  QStringList placeholders;             // Placeholders specific to this variant
  QList<CommandVariant> nestedVariants; // Nested variants within this variant
};

// Nested Variant Management Dialog Class
class NestedVariantDialog : public QDialog {
  Q_OBJECT

public:
  NestedVariantDialog(QWidget *parent = nullptr);

  // Set the list of variants for the selected template
  void setVariants(const QList<CommandVariant> &variants);

  // Get the updated list of variants
  QList<CommandVariant> getVariants() const;

private slots:
  // Slot to add a new nested variant
  void addNestedVariant();

  // Slot to save changes to the current nested variant
  void saveVariant();

  // Slot to delete the selected nested variant
  void deleteVariant();

  // Slot to handle variant selection in the tree
  void onVariantSelected(QTreeWidgetItem *item);

private:
  // UI Setup
  void setupUI();
  void setupConnections();

  // Helper function to update the variant tree
  void updateVariantTree();

  // Helper function to add nested items to the tree
  void addNestedItems(QTreeWidgetItem *parentItem,
                      const QList<CommandVariant> &nestedVariants);

  // Helper function to clear the variant details
  void clearVariantDetails();

  // Variant List and Current Selection
  QList<CommandVariant> commandVariants; // List of command variants
  int selectedVariantIndex; // Index of the currently selected variant

  // UI Elements
  QTreeWidget *variantTree;    // Tree widget for displaying nested variants
  QLineEdit *variantName;      // Input field for variant name
  QLineEdit *variantCondition; // Input field for variant condition
  QTextEdit *variantCommandStructure; // Text area for the command structure

  // Buttons for managing variants
  QPushButton *addVariantButton;
  QPushButton *saveVariantButton;
  QPushButton *deleteVariantButton;
};

#endif // NESTEDVARIANTDIALOG_H
