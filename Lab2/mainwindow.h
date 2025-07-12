#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QListView>
#include <QTableWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QKeyEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addComputerToViews(const QString &model, double hdd, const QString &cpu, const QString &imagePath = "");
    void deleteSelectedComputer();

    QStandardItemModel *listViewModel;
    QListView *listView;

    QTableWidget *tableWidget;
    QListWidget *listWidget;

    QPushButton *refreshBtn;
    QPushButton *sortBtn;
    QLabel *currentImageLabel;
    QLabel *imageLabel;

    QLineEdit *searchEdit;
    QPushButton *searchBtn;
    void searchComputer();



protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void addComputer();
    void showContextMenu(const QPoint &pos);
    void loadFromFile();
    void saveToFile();
    void refreshData();
    void sortItems();
    void updateSelectedImage(const QItemSelection &selected);

private:
    void setupUI();
    void setupConnections();
    void loadInitialData();

    QLineEdit *modelEdit;
    QLineEdit *hddEdit;
    QLineEdit *cpuEdit;

    QPushButton *addBtn;
    QPushButton *deleteBtn;
    QPushButton *loadBtn;
    QPushButton *saveBtn;




    QVBoxLayout *mainLayout;



};

#endif // MAINWINDOW_H
