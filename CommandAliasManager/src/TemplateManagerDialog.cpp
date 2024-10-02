#include "TemplateManagerDialog.h"
#include "ConditionalArgumentDialog.h"
#include "VariantDialog.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QTreeWidgetItem>
#include <QVBoxLayout>

// Constructor
TemplateManagerDialog::TemplateManagerDialog(QWidget *parent)
    : QDialog(parent), selectedTemplateIndex(-1) {
  setupUI();
  setupConnections();
}

// Set up the user interface
void TemplateManagerDialog::setupUI() {
  setWindowTitle("Manage Command Templates");

  QVBoxLayout *layout = new QVBoxLayout(this);

  // Template List
  layout->addWidget(new QLabel("Templates:", this));
  templateList = new QListWidget(this);
  layout->addWidget(templateList);

  // Template Details Area
  QGroupBox *detailsGroup = new QGroupBox("Template Details", this);
  QVBoxLayout *detailsLayout = new QVBoxLayout(detailsGroup);

  templateName = new QLineEdit(this);
  commandStructure = new QTextEdit(this);
  templateCategory = new QLineEdit(this);

  detailsLayout->addWidget(new QLabel("Template Name:", this));
  detailsLayout->addWidget(templateName);
  detailsLayout->addWidget(new QLabel("Command Structure:", this));
  detailsLayout->addWidget(commandStructure);
  detailsLayout->addWidget(new QLabel("Category:", this));
  detailsLayout->addWidget(templateCategory);

  // Nested Placeholder Tree
  placeholderTree = new QTreeWidget(this);
  placeholderTree->setHeaderLabel("Placeholders");
  detailsLayout->addWidget(new QLabel("Nested Placeholders:", this));
  detailsLayout->addWidget(placeholderTree);

  // Buttons for Managing Conditions and Variants
  addConditionButton = new QPushButton("Add Conditional Argument", this);
  manageVariantsButton = new QPushButton("Manage Variants", this);
  detailsLayout->addWidget(addConditionButton);
  detailsLayout->addWidget(manageVariantsButton);

  layout->addWidget(detailsGroup);

  // OK and Cancel buttons
  addButton = new QPushButton("Add Template", this);
  saveButton = new QPushButton("Save Changes", this);
  deleteButton = new QPushButton("Delete Template", this);

  QHBoxLayout *buttonLayout = new QHBoxLayout();
  buttonLayout->addWidget(addButton);
  buttonLayout->addWidget(saveButton);
  buttonLayout->addWidget(deleteButton);

  layout->addLayout(buttonLayout);

  setLayout(layout);
}

// Set up signal-slot connections
void TemplateManagerDialog::setupConnections() {
  connect(addButton, &QPushButton::clicked, this, &TemplateManagerDialog::addTemplate);
  connect(saveButton, &QPushButton::clicked, this, &TemplateManagerDialog::saveTemplate);
  connect(deleteButton, &QPushButton::clicked, this, &TemplateManagerDialog::deleteTemplate);
  connect(addConditionButton, &QPushButton::clicked, this, &TemplateManagerDialog::addConditionalArgument);
  connect(manageVariantsButton, &QPushButton::clicked, this, &TemplateManagerDialog::openVariantManager);
  connect(templateList, &QListWidget::itemClicked, this, &TemplateManagerDialog::onTemplateSelected);
}

// Set templates and update the template list
void TemplateManagerDialog::setTemplates(const QList<CommandTemplate> &templates) {
  commandTemplates = templates;
  updateTemplateList();
}

// Get the current list of templates
QList<CommandTemplate> TemplateManagerDialog::getTemplates() const {
  return commandTemplates;
}

// Clear the template details area
void TemplateManagerDialog::clearTemplateDetails() {
  templateName->clear();
  commandStructure->clear();
  templateCategory->clear();
  placeholderTree->clear();
}

// Add a new template to the list
void TemplateManagerDialog::addTemplate() {
  QString newTemplateName = QInputDialog::getText(this, "New Template", "Template Name:");
  if (newTemplateName.isEmpty()) return;

  CommandTemplate newTemplate;
  newTemplate.templateName = newTemplateName;
  newTemplate.commandStructure = "";
  newTemplate.category = "General";
  commandTemplates.append(newTemplate);
  updateTemplateList();
}

// Save changes to the selected template
void TemplateManagerDialog::saveTemplate() {
  if (selectedTemplateIndex >= 0 && selectedTemplateIndex < commandTemplates.size()) {
    commandTemplates[selectedTemplateIndex].templateName = templateName->text();
    commandTemplates[selectedTemplateIndex].commandStructure = commandStructure->toPlainText();
    commandTemplates[selectedTemplateIndex].category = templateCategory->text();

    // Save placeholders and conditional arguments
    commandTemplates[selectedTemplateIndex].placeholders = extractPlaceholdersFromTree();
    updateTemplateList();
  }
}

// Delete the selected template from the list
void TemplateManagerDialog::deleteTemplate() {
  if (selectedTemplateIndex >= 0 && selectedTemplateIndex < commandTemplates.size()) {
    commandTemplates.removeAt(selectedTemplateIndex);
    updateTemplateList();
    clearTemplateDetails();
  }
}

// Handle template selection and display details
void TemplateManagerDialog::onTemplateSelected(QListWidgetItem *item) {
  if (!item) return;
  selectedTemplateIndex = item->data(Qt::UserRole).toInt();

  if (selectedTemplateIndex >= 0 && selectedTemplateIndex < commandTemplates.size()) {
    CommandTemplate selectedTemplate = commandTemplates[selectedTemplateIndex];
    templateName->setText(selectedTemplate.templateName);
    commandStructure->setText(selectedTemplate.commandStructure);
    templateCategory->setText(selectedTemplate.category);

    // Show placeholders in the tree view
    populatePlaceholderTree(selectedTemplate.placeholders);
  }
}

// Add a new conditional argument to the template
void TemplateManagerDialog::addConditionalArgument() {
  if (selectedTemplateIndex < 0 || selectedTemplateIndex >= commandTemplates.size()) {
    QMessageBox::warning(this, "No Template Selected", "Please select a template first.");
    return;
  }

  ConditionalArgumentDialog dialog(this);
  if (dialog.exec() == QDialog::Accepted) {
    QString condition = dialog.getCondition();
    if (!condition.isEmpty()) {
      commandTemplates[selectedTemplateIndex].conditionalArguments.append(condition);
      QMessageBox::information(this, "Condition Added", "Conditional argument added successfully.");
    }
  }
}

// Manage variants for the selected template
void TemplateManagerDialog::openVariantManager() {
  if (selectedTemplateIndex < 0 || selectedTemplateIndex >= commandTemplates.size()) {
    QMessageBox::warning(this, "No Template Selected", "Please select a template first.");
    return;
  }

  VariantDialog variantDialog(this);
  variantDialog.setVariants(commandTemplates[selectedTemplateIndex].variants);
  if (variantDialog.exec() == QDialog::Accepted) {
    commandTemplates[selectedTemplateIndex].variants = variantDialog.getVariants();
  }
}

// Extract placeholders from a command structure
QStringList TemplateManagerDialog::extractPlaceholdersFromStructure(const QString &structure) {
  QStringList placeholders;
  QRegExp placeholderRegex(R"(\{(\w+)\})");
  int pos = 0;
  while ((pos = placeholderRegex.indexIn(structure, pos)) != -1) {
    placeholders.append(placeholderRegex.cap(1));
    pos += placeholderRegex.matchedLength();
  }
  return placeholders;
}

// Populate the placeholder tree with nested structures
void TemplateManagerDialog::populatePlaceholderTree(const QStringList &placeholders) {
  placeholderTree->clear();
  for (const QString &placeholder : placeholders) {
    QTreeWidgetItem *placeholderItem = new QTreeWidgetItem(placeholderTree);
    placeholderItem->setText(0, placeholder);
    placeholderTree->addTopLevelItem(placeholderItem);
  }
}

// Extract placeholders from the tree structure
QStringList TemplateManagerDialog::extractPlaceholdersFromTree() const {
  QStringList placeholders;
  for (int i = 0; i < placeholderTree->topLevelItemCount(); ++i) {
    placeholders.append(placeholderTree->topLevelItem(i)->text(0));
  }
  return placeholders;
}

// Update the template list in the dialog
void TemplateManagerDialog::updateTemplateList() {
  templateList->clear();
  for (int i = 0; i < commandTemplates.size(); ++i) {
    QListWidgetItem *item = new QListWidgetItem(commandTemplates[i].templateName, templateList);
    item->setData(Qt::UserRole, i);
  }
}