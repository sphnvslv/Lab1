#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);

private:
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;
    QLineEdit *logPathEdit;
    QPushButton *saveButton;
    QPushButton *cancelButton;
};

#endif // SETTINGSDIALOG_H
