#ifndef LABELINGDIALOG_H
#define LABELINGDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QListWidget>
#include <QMap>
#include <QPushButton>
#include <QString>
#include <QTextEdit>
#include <QVBoxLayout>

// Data structure for storing command labels, tags, and annotations
struct CommandMetadata {
  QString label;      // Command label
  QStringList tags;   // List of tags for categorization
  QString annotation; // Detailed description or notes
};

// Labeling and Tagging Dialog Class
class LabelingDialog : public QDialog {
  Q_OBJECT

public:
  LabelingDialog(QWidget *parent = nullptr);

  // Set the metadata for the selected command or template
  void setMetadata(const CommandMetadata &metadata);

  // Get the updated metadata
  CommandMetadata getMetadata() const;

private slots:
  // Slot to add a new tag
  void addTag();

  // Slot to remove the selected tag
  void removeTag();

  // Slot to save changes to the command metadata
  void saveMetadata();

private:
  // UI Setup
  void setupUI();
  void setupConnections();

  // Helper function to update the tag list
  void updateTagList();

  // Command Metadata
  CommandMetadata
      commandMetadata; // Metadata for the selected command or template

  // UI Elements
  QLineEdit *labelInput;      // Input field for the label
  QListWidget *tagList;       // List widget for displaying tags
  QLineEdit *tagInput;        // Input field for adding a new tag
  QTextEdit *annotationInput; // Text area for detailed annotations

  // Buttons for managing tags and metadata
  QPushButton *addTagButton;
  QPushButton *removeTagButton;
  QPushButton *saveButton;
};

#endif // LABELINGDIALOG_H
