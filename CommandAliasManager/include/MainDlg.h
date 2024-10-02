#ifndef MAINDLG_H
#define MAINDLG_H

#include "AliasManager.h"
#include "PathManager.h"
#include "TemplateManagerDialog.h"
#include <QDialog>
#include <QInputDialog>
#include <QLabel>
#include <QListWidget>
#include <QMap>
#include <QPushButton>
#include <QTextEdit>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>

// Forward declaration for managing template variants
struct CommandVariant;

class CMainDlg : public QDialog {
  Q_OBJECT

public:
  CMainDlg(QWidget *parent = nullptr);
  ~CMainDlg();

  // Insert a variant into the command builder with dynamic placeholder
  // replacement
  void insertVariantIntoCommandBuilder(
      const CommandVariant &variant,
      const QMap<QString, QString> &placeholderValues);

  // Update live command preview with selected variants
  void updateLiveCommandPreviewWithVariants(
      const QList<CommandVariant> &variants,
      const QMap<QString, QString> &placeholderValues);

  // Evaluate a variant condition against placeholder values
  bool evaluateCondition(const QString &condition,
                         const QMap<QString, QString> &placeholderValues);

  // Function to dynamically replace placeholders in a variant
  QString replaceComplexPlaceholdersInVariant(
      const CommandVariant &variant,
      const QMap<QString, QString> &placeholderValues);

  // Function to handle nested placeholder replacement
  QString evaluateMultiLevelPlaceholders(
      const QString &commandStructure,
      const QMap<QString, QString> &placeholderValues);

  // Function to validate complex command templates
  bool validateComplexCommandTemplate(
      const QString &templateStructure,
      const QMap<QString, QString> &placeholderValues,
      const QStringList &conditionalArguments);

signals:
  // Signal to show a warning for unresolved placeholders
  void showWarning(const QString &message);

private slots:
  // Slot to manage template insertion
  void onInsertVariantClicked();

  // Slot to handle template management
  void openTemplateManager();

  // Slot to update live command preview dynamically
  void updateLiveCommandPreview();

  // Slot to update contextual help for complex structures
  void
  updateContextualHelpForComplexStructures(const QString &commandStructure);

private:
  // UI Components
  QLabel *contextualHelp;
  QTreeWidget *commandBuilderTree;
  QLabel *liveCommandPreview;
  QListWidget *commandLibrary;
  QTreeWidget *commandHistoryTree;

  // Template Management
  QPushButton *manageTemplatesButton;
  QPushButton *insertTemplateButton;

  // Placeholder Management
  QMap<QString, QString> resolvedPlaceholders;

  // Command Templates
  QList<CommandTemplate> commandTemplates;

  // Helper functions
  void setupUI();
  void setupConnections();
};

#endif // MAINDLG_H