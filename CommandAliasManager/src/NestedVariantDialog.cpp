#include "NestedVariantDialog.h"
#include <QInputDialog>
#include <QMessageBox>

// Constructor
NestedVariantDialog::NestedVariantDialog(QWidget *parent)
    : QDialog(parent), selectedVariantIndex(-1) {
  setupUI();
  setupConnections();
}

// Set up the user interface
void NestedVariantDialog::setupUI() {
  setWindowTitle("Manage Nested Template Variants");

  QVBoxLayout *layout = new QVBoxLayout(this);

  // Variant Tree for Nested Structures
  layout->addWidget(new QLabel("Variant Structure:", this));
  variantTree = new QTreeWidget(this);
  variantTree->setHeaderLabel("Variants");
  layout->addWidget(variantTree);

  // Variant Details
  variantName = new QLineEdit(this);
  variantCondition = new QLineEdit(this);
  variantCommandStructure = new QTextEdit(this);

  layout->addWidget(new QLabel("Variant Name:", this));
  layout->addWidget(variantName);
  layout->addWidget(new QLabel("Condition:", this));
  layout->addWidget(variantCondition);
  layout->addWidget(new QLabel("Command Structure:", this));
  layout->addWidget(variantCommandStructure);

  // OK, Save, and Delete buttons
  addVariantButton = new QPushButton("Add Nested Variant", this);
  saveVariantButton = new QPushButton("Save Changes", this);
  deleteVariantButton = new QPushButton("Delete Variant", this);

  QHBoxLayout *buttonLayout = new QHBoxLayout();
  buttonLayout->addWidget(addVariantButton);
  buttonLayout->addWidget(saveVariantButton);
  buttonLayout->addWidget(deleteVariantButton);

  layout->addLayout(buttonLayout);
  setLayout(layout);
}

// Set up signal-slot connections
void NestedVariantDialog::setupConnections() {
  connect(addVariantButton, &QPushButton::clicked, this,
          &NestedVariantDialog::addNestedVariant);
  connect(saveVariantButton, &QPushButton::clicked, this,
          &NestedVariantDialog::saveVariant);
  connect(deleteVariantButton, &QPushButton::clicked, this,
          &NestedVariantDialog::deleteVariant);
  connect(variantTree, &QTreeWidget::itemClicked, this,
          &NestedVariantDialog::onVariantSelected);
}

// Set the list of variants for the selected template
void NestedVariantDialog::setVariants(const QList<CommandVariant> &variants) {
  commandVariants = variants;
  updateVariantTree();
}

// Get the updated list of variants
QList<CommandVariant> NestedVariantDialog::getVariants() const {
  return commandVariants;
}

// Add a new nested variant to the selected variant
void NestedVariantDialog::addNestedVariant() {
  QString newVariantName =
      QInputDialog::getText(this, "New Nested Variant", "Variant Name:");
  if (newVariantName.isEmpty())
    return;

  CommandVariant newVariant;
  newVariant.variantName = newVariantName;
  newVariant.condition = "";
  newVariant.commandStructure = "";

  if (selectedVariantIndex >= 0 &&
      selectedVariantIndex < commandVariants.size()) {
    commandVariants[selectedVariantIndex].nestedVariants.append(newVariant);
  } else {
    commandVariants.append(newVariant);
  }
  updateVariantTree();
}

// Save changes to the currently selected variant
void NestedVariantDialog::saveVariant() {
  if (selectedVariantIndex >= 0 &&
      selectedVariantIndex < commandVariants.size()) {
    commandVariants[selectedVariantIndex].variantName = variantName->text();
    commandVariants[selectedVariantIndex].condition = variantCondition->text();
    commandVariants[selectedVariantIndex].commandStructure =
        variantCommandStructure->toPlainText();
    updateVariantTree();
  }
}

// Delete the selected nested variant
void NestedVariantDialog::deleteVariant() {
  if (selectedVariantIndex >= 0 &&
      selectedVariantIndex < commandVariants.size()) {
    commandVariants.removeAt(selectedVariantIndex);
    updateVariantTree();
    clearVariantDetails();
  }
}

// Handle variant selection and display details
void NestedVariantDialog::onVariantSelected(QTreeWidgetItem *item) {
  if (!item)
    return;

  selectedVariantIndex = item->data(0, Qt::UserRole).toInt();

  if (selectedVariantIndex >= 0 &&
      selectedVariantIndex < commandVariants.size()) {
    CommandVariant selectedVariant = commandVariants[selectedVariantIndex];
    variantName->setText(selectedVariant.variantName);
    variantCondition->setText(selectedVariant.condition);
    variantCommandStructure->setText(selectedVariant.commandStructure);
  }
}

// Update the variant tree in the dialog
void NestedVariantDialog::updateVariantTree() {
  variantTree->clear();
  for (int i = 0; i < commandVariants.size(); ++i) {
    QTreeWidgetItem *item = new QTreeWidgetItem(variantTree);
    item->setText(0, commandVariants[i].variantName);
    item->setData(0, Qt::UserRole, i);
    addNestedItems(item, commandVariants[i].nestedVariants);
  }
}

// Add nested variants to the tree
void NestedVariantDialog::addNestedItems(
    QTreeWidgetItem *parentItem, const QList<CommandVariant> &nestedVariants) {
  for (int i = 0; i < nestedVariants.size(); ++i) {
    QTreeWidgetItem *nestedItem = new QTreeWidgetItem(parentItem);
    nestedItem->setText(0, nestedVariants[i].variantName);
    parentItem->addChild(nestedItem);
    addNestedItems(nestedItem, nestedVariants[i].nestedVariants);
  }
}

// Clear the variant details area
void NestedVariantDialog::clearVariantDetails() {
  variantName->clear();
  variantCondition->clear();
  variantCommandStructure->clear();
}
