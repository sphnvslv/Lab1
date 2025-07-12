#include "settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Настройки");
    setModal(true);
    resize(400, 200);

    mainLayout = new QVBoxLayout(this);

    QLabel *pathLabel = new QLabel("Записать результат в файл:");
    logPathEdit = new QLineEdit("hyperbolic_log.txt");
    mainLayout->addWidget(pathLabel);
    mainLayout->addWidget(logPathEdit);

    buttonLayout = new QHBoxLayout();
    saveButton = new QPushButton("Сохранить");
    cancelButton = new QPushButton("Отмена");
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout);

    connect(saveButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}
