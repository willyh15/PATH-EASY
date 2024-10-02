#include "VariantDialog.h"
#include <QInputDialog>
#include <QMessageBox>

// Constructor
VariantDialog::VariantDialog(QWidget *parent)
    : QDialog(parent), selectedVariantIndex(-1) {
  setupUI();
  setupConnections();
}

// Set up the user interface
void VariantDialog::setupUI() {
  setWindowTitle("Manage Command Variants");

  QVBoxLayout *layout = new QVBoxLayout(this);

  // Variant List
  layout->addWidget(new QLabel("Variants:", this));
  variantList = new QListWidget(this);
  layout->addWidget(variantList);

  // Variant Details Area
  QGroupBox *detailsGroup = new QGroupBox("Variant Details", this);
  QVBoxLayout *detailsLayout = new QVBoxLayout(detailsGroup);

  variantName = new QLineEdit(this);
  variantCondition = new QLineEdit(this);
  variantCommandStructure = new QTextEdit(this);

  detailsLayout->addWidget(new QLabel("Variant Name:", this));
  detailsLayout->addWidget(variantName);
  detailsLayout->addWidget(new QLabel("Condition:", this));
  detailsLayout->addWidget(variantCondition);
  detailsLayout->addWidget(new QLabel("Command Structure:", this));
  detailsLayout->addWidget(variantCommandStructure);

  layout->addWidget(detailsGroup);

  // Buttons for managing variants
  QPushButton *addVariantButton = new QPushButton("Add Variant", this);
  QPushButton *saveVariantButton = new QPushButton("Save Changes", this);
  QPushButton *deleteVariantButton = new QPushButton("Delete Variant", this);

  QHBoxLayout *buttonLayout = new QHBoxLayout();
  buttonLayout->addWidget(addVariantButton);
  buttonLayout->addWidget(saveVariantButton);
  buttonLayout->addWidget(deleteVariantButton);

  layout->addLayout(buttonLayout);

  setLayout(layout);
}

// Set up signal-slot connections
void VariantDialog::setupConnections() {
  connect(variantList, &QListWidget::itemClicked, this,
          &VariantDialog::onVariantSelected);
  connect(addVariantButton, &QPushButton::clicked, this,
          &VariantDialog::addVariant);
  connect(saveVariantButton, &QPushButton::clicked, this,
          &VariantDialog::saveVariant);
  connect(deleteVariantButton, &QPushButton::clicked, this,
          &VariantDialog::deleteVariant);
}

// Set the list of variants for the selected template
void VariantDialog::setVariants(const QList<CommandVariant> &variants) {
  commandVariants = variants;
  updateVariantList();
}

// Get the updated list of variants
QList<CommandVariant> VariantDialog::getVariants() const {
  return commandVariants;
}

// Add a new variant to the list
void VariantDialog::addVariant() {
  QString newVariantName =
      QInputDialog::getText(this, "New Variant", "Variant Name:");
  if (newVariantName.isEmpty())
    return;

  CommandVariant newVariant;
  newVariant.variantName = newVariantName;
  newVariant.condition = "";
  newVariant.commandStructure = "";
  commandVariants.append(newVariant);
  updateVariantList();
}

// Save changes to the currently selected variant
void VariantDialog::saveVariant() {
  if (selectedVariantIndex >= 0 &&
      selectedVariantIndex < commandVariants.size()) {
    commandVariants[selectedVariantIndex].variantName = variantName->text();
    commandVariants[selectedVariantIndex].condition = variantCondition->text();
    commandVariants[selectedVariantIndex].commandStructure =
        variantCommandStructure->toPlainText();
    updateVariantList();
  }
}

// Delete the selected variant from the list
void VariantDialog::deleteVariant() {
  if (selectedVariantIndex >= 0 &&
      selectedVariantIndex < commandVariants.size()) {
    commandVariants.removeAt(selectedVariantIndex);
    updateVariantList();
    clearVariantDetails();
  }
}

// Handle variant selection and display details
void VariantDialog::onVariantSelected(QListWidgetItem *item) {
  if (!item)
    return;

  selectedVariantIndex = item->data(Qt::UserRole).toInt();

  if (selectedVariantIndex >= 0 &&
      selectedVariantIndex < commandVariants.size()) {
    CommandVariant selectedVariant = commandVariants[selectedVariantIndex];
    variantName->setText(selectedVariant.variantName);
    variantCondition->setText(selectedVariant.condition);
    variantCommandStructure->setText(selectedVariant.commandStructure);
  }
}

// Update the variant list in the dialog
void VariantDialog::updateVariantList() {
  variantList->clear();
  for (int i = 0; i < commandVariants.size(); ++i) {
    QListWidgetItem *item =
        new QListWidgetItem(commandVariants[i].variantName, variantList);
    item->setData(Qt::UserRole, i);
  }
}

// Clear the variant details area
void VariantDialog::clearVariantDetails() {
  variantName->clear();
  variantCondition->clear();
  variantCommandStructure->clear();
}
