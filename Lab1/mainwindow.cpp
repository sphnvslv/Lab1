#include "mainwindow.h"
#include "settingsdialog.h"
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Калькулятор гиперболических функций");

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QVBoxLayout(centralWidget);

    inputEdit = new QTextEdit();
    inputEdit->setPlaceholderText("Введите значение x в радианах");
    inputEdit->setMaximumHeight(100);
    mainLayout->addWidget(inputEdit);

    functionComboBox = new QComboBox();
    functionComboBox->addItems({"sinh x", "cosh x", "tanh x", "coth x", "sech x", "csch x"});
    mainLayout->addWidget(functionComboBox);

    buttonLayout = new QHBoxLayout();
    calculateButton = new QPushButton("Вычислить");
    settingsButton = new QPushButton("Настройки");
    buttonLayout->addWidget(calculateButton);
    buttonLayout->addWidget(settingsButton);
    mainLayout->addLayout(buttonLayout);

    enableFileOperationsCheck = new QCheckBox("Сохранять историю в файл");
    mainLayout->addWidget(enableFileOperationsCheck);

    resultLabel = new QLabel("");
    resultLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(resultLabel);

    connect(calculateButton, &QPushButton::clicked, this, &MainWindow::calculate);
    connect(settingsButton, &QPushButton::clicked, this, &MainWindow::openSettings);
    connect(enableFileOperationsCheck, &QCheckBox::toggled, this, &MainWindow::toggleFileOperations);
}

MainWindow::~MainWindow() {}

void MainWindow::calculate()
{
    QString input = inputEdit->toPlainText().trimmed();
    if (input.isEmpty()) {
        showError("Введите значение x");
        return;
    }

    bool correct;
    qreal x = input.toDouble(&correct);
    if (!correct) {
        showError("Некорректный ввод числа");
        return;
    }

    QString funcDisplay = functionComboBox->currentText(); // "sinh x"
    QString funcName = funcDisplay.split(" ").first();     // "sinh"

    try {
        qreal result = calculateHyperbolicFunc(funcName, x);
        QString output = QString("%1(%2) = %3").arg(funcName).arg(x).arg(result);
        resultLabel->setText(output);

        if (enableFileOperations) {
            QFile file(logFileName);
            if (file.open(QIODevice::Append | QIODevice::Text)) {
                QTextStream stream(&file);
                stream << QDateTime::currentDateTime().toString("dd.mm.yyyy hh:mm | ")  << output << "\n";
                file.close();
            }
        }
    } catch (const std::exception &e) {
        showError(e.what());
    }
}

qreal MainWindow::calculateAndLog(const QString &funcName, qreal x)
{
    qreal result = calculateHyperbolicFunc(funcName, x);
    QString output = QString("%1(%2) = %3").arg(funcName).arg(x).arg(result);
    resultLabel->setText(output);

    if (enableFileOperations) {
        QFile file(logFileName);
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream stream(&file);
            stream << QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm | ") << output << "\n";
            file.close();
        }
    }
    return result;
}



qreal MainWindow::calculateHyperbolicFunc(const QString &funcName, qreal x)
{
    if (funcName == "sinh") {
        return sinh(x);
    } else if (funcName == "cosh") {
        return cosh(x);
    } else if (funcName == "tanh") {
        return tanh(x);
    } else if (funcName == "coth") {
        if (x == 0) {
            throw std::runtime_error("Деление на ноль, coth(0) не определен");
        }
        return cosh(x) / sinh(x);
    } else if (funcName == "sech") {
        return 1 / cosh(x);
    } else if (funcName == "csch") {
        if (x == 0) {
            throw std::runtime_error("Деление на ноль, csch(0) не определен");
        }
        return 1 / sinh(x);
    } else {
        throw std::runtime_error("Неизвестная функция");
    }
}

void MainWindow::showError(const QString &message)
{
    QMessageBox::critical(this, "Ошибка", message);
}

void MainWindow::openSettings()
{
    SettingsDialog *dialog = new SettingsDialog(this);
    dialog->exec(); // Модальное окно (нечётный вариант)
    delete dialog;
}

void MainWindow::toggleFileOperations(bool checked)
{
    enableFileOperations = checked;
}
