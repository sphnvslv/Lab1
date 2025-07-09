#include "settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Настройки");
    setModal(true); // Модальное окно (нечётный вариант)
    resize(400, 200);

    // Главная компоновка
    mainLayout = new QVBoxLayout(this);

    // Поле для пути к лог-файлу
    QLabel *pathLabel = new QLabel("Записать результат в файл:");
    logPathEdit = new QLineEdit("hyperbolic_log.txt");
    mainLayout->addWidget(pathLabel);
    mainLayout->addWidget(logPathEdit);

    // Кнопки
    buttonLayout = new QHBoxLayout();
    saveButton = new QPushButton("Сохранить");
    cancelButton = new QPushButton("Отмена");
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout);

    // Подключение сигналов
    connect(saveButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}
