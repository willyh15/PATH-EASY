#include "LabelingDialog.h"
#include <QInputDialog>
#include <QMessageBox>

// Constructor
LabelingDialog::LabelingDialog(QWidget *parent) : QDialog(parent) {
  setupUI();
  setupConnections();
}

// Set up the user interface
void LabelingDialog::setupUI() {
  setWindowTitle("Manage Labels and Tags");

  QVBoxLayout *layout = new QVBoxLayout(this);

  // Label Input
  layout->addWidget(new QLabel("Command Label:", this));
  labelInput = new QLineEdit(this);
  layout->addWidget(labelInput);

  // Tag List and Input
  layout->addWidget(new QLabel("Tags:", this));
  tagList = new QListWidget(this);
  layout->addWidget(tagList);

  tagInput = new QLineEdit(this);
  tagInput->setPlaceholderText("Enter a new tag...");
  layout->addWidget(tagInput);

  addTagButton = new QPushButton("Add Tag", this);
  removeTagButton = new QPushButton("Remove Selected Tag", this);
  QHBoxLayout *tagButtonLayout = new QHBoxLayout();
  tagButtonLayout->addWidget(addTagButton);
  tagButtonLayout->addWidget(removeTagButton);
  layout->addLayout(tagButtonLayout);

  // Annotation Input
  layout->addWidget(new QLabel("Annotation:", this));
  annotationInput = new QTextEdit(this);
  layout->addWidget(annotationInput);

  // Save Button
  saveButton = new QPushButton("Save Metadata", this);
  layout->addWidget(saveButton);

  setLayout(layout);
}

// Set up signal-slot connections
void LabelingDialog::setupConnections() {
  connect(addTagButton, &QPushButton::clicked, this, &LabelingDialog::addTag);
  connect(removeTagButton, &QPushButton::clicked, this,
          &LabelingDialog::removeTag);
  connect(saveButton, &QPushButton::clicked, this,
          &LabelingDialog::saveMetadata);
}

// Set the metadata for the selected command or template
void LabelingDialog::setMetadata(const CommandMetadata &metadata) {
  commandMetadata = metadata;

  // Set UI elements with metadata values
  labelInput->setText(commandMetadata.label);
  annotationInput->setPlainText(commandMetadata.annotation);

  // Populate tag list
  updateTagList();
}

// Get the updated metadata
CommandMetadata LabelingDialog::getMetadata() const { return commandMetadata; }

// Slot to add a new tag to the tag list
void LabelingDialog::addTag() {
  QString newTag = tagInput->text().trimmed();
  if (newTag.isEmpty()) {
    QMessageBox::warning(this, "Invalid Tag", "Tag cannot be empty.");
    return;
  }

  if (commandMetadata.tags.contains(newTag)) {
    QMessageBox::warning(this, "Duplicate Tag", "Tag already exists.");
    return;
  }

  commandMetadata.tags.append(newTag);
  updateTagList();
  tagInput->clear();
}

// Slot to remove the selected tag from the tag list
void LabelingDialog::removeTag() {
  QListWidgetItem *selectedItem = tagList->currentItem();
  if (!selectedItem) {
    QMessageBox::warning(this, "No Tag Selected",
                         "Please select a tag to remove.");
    return;
  }

  QString tagToRemove = selectedItem->text();
  commandMetadata.tags.removeAll(tagToRemove);
  updateTagList();
}

// Slot to save changes to the command metadata
void LabelingDialog::saveMetadata() {
  commandMetadata.label = labelInput->text();
  commandMetadata.annotation = annotationInput->toPlainText();
  accept(); // Close the dialog and indicate success
}

// Update the tag list with current tags
void LabelingDialog::updateTagList() {
  tagList->clear();
  for (const QString &tag : commandMetadata.tags) {
    tagList->addItem(tag);
  }
}
