#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDateTime>
#include <QDialog>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    qreal calculateHyperbolicFunc(const QString &funcName, qreal x);
    void toggleFileOperations(bool checked);
    QString logFileName = "hyperbolic_log.txt";
HEAD
    qreal calculateAndLog(const QString &funcName, qreal x);

    qreal calculateAndLog(const QString &funcName, qreal x); 
9cb8957d27945d536644c2d9c05caf80c020696c



private slots:
    void calculate();
    void openSettings();

private:
    QTextEdit *inputEdit;
    QLabel *resultLabel;
    QPushButton *calculateButton;
    QPushButton *settingsButton;
    QCheckBox *enableFileOperationsCheck;
    QComboBox *functionComboBox;
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;

    bool enableFileOperations = false;

    void showError(const QString &message);
    void setupUI();
};

#endif // MAINWINDOW_H
