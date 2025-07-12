#include "mainwindow.h"
#include "computer.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QListView>
#include <QTableWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMenu>
#include <QAction>
#include <QKeyEvent>
#include <QPixmap>
#include <QFileDialog>
#include <QMessageBox>
#include <QHeaderView>
#include <QStandardItem>
#include <QFile>
#include <QTextStream>
#include <QItemSelectionModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    listViewModel(new QStandardItemModel(this)),
    listView(new QListView(this)),
    tableWidget(new QTableWidget(this)),
    listWidget(new QListWidget(this)),
    modelEdit(new QLineEdit(this)),
    hddEdit(new QLineEdit(this)),
    cpuEdit(new QLineEdit(this)),
    addBtn(new QPushButton("Добавить", this)),
    deleteBtn(new QPushButton("Удалить", this)),
    loadBtn(new QPushButton("Загрузить", this)),
    saveBtn(new QPushButton("Сохранить", this)),
    refreshBtn(new QPushButton("Обновить", this)),
    sortBtn(new QPushButton("Сортировать", this)),
    currentImageLabel(new QLabel(this)),

    imageLabel(new QLabel(this)),
    searchEdit(new QLineEdit(this)),
    searchBtn(new QPushButton("Поиск", this)),
    mainLayout(new QVBoxLayout())
{
    setupUI();
    setupConnections();
    loadInitialData();
    setWindowTitle("Информация о компьютерах");
}

void MainWindow::setupUI()
{

    listView->setModel(listViewModel);
    listView->setContextMenuPolicy(Qt::CustomContextMenu);

    tableWidget->setColumnCount(3);
    tableWidget->setHorizontalHeaderLabels({"Модель", "HDD (GB)", "Процессор"});
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    currentImageLabel->setFixedSize(200, 200);
    currentImageLabel->setAlignment(Qt::AlignCenter);

    QHBoxLayout *searchLayout = new QHBoxLayout();
    searchLayout->addWidget(new QLabel("Поиск:", this));
    searchLayout->addWidget(searchEdit);
    searchLayout->addWidget(searchBtn);


    mainLayout->addLayout(searchLayout);


    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow("Модель:", modelEdit);
    formLayout->addRow("HDD (GB):", hddEdit);
    formLayout->addRow("Процессор:", cpuEdit);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addBtn);
    buttonLayout->addWidget(deleteBtn);
    buttonLayout->addWidget(loadBtn);
    buttonLayout->addWidget(saveBtn);
    buttonLayout->addWidget(refreshBtn);
    buttonLayout->addWidget(sortBtn);

    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(currentImageLabel);
    mainLayout->addWidget(listView);
    mainLayout->addWidget(tableWidget);
    mainLayout->addWidget(listWidget);
    mainLayout->addWidget(imageLabel);

    resize(800, 600);
}

void MainWindow::setupConnections()
{
    connect(addBtn, &QPushButton::clicked, this, &MainWindow::addComputer);
    connect(deleteBtn, &QPushButton::clicked, this, &MainWindow::deleteSelectedComputer);
    connect(loadBtn, &QPushButton::clicked, this, &MainWindow::loadFromFile);
    connect(saveBtn, &QPushButton::clicked, this, &MainWindow::saveToFile);
    connect(refreshBtn, &QPushButton::clicked, this, &MainWindow::refreshData);
    connect(sortBtn, &QPushButton::clicked, this, &MainWindow::sortItems);
    connect(listView, &QListView::customContextMenuRequested, this, &MainWindow::showContextMenu);
    connect(listView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &MainWindow::updateSelectedImage);
    connect(searchBtn, &QPushButton::clicked, this, &MainWindow::searchComputer);
}

void MainWindow::searchComputer()
{
    QString searchText = searchEdit->text().trimmed().toLower();
    if (searchText.isEmpty()) {
        refreshData();
        return;
    }

    for (int i = 0; i < tableWidget->rowCount(); ++i) {
        bool match = false;
        for (int j = 0; j < tableWidget->columnCount(); ++j) {
            if (tableWidget->item(i, j)->text().toLower().contains(searchText)) {
                match = true;
                break;
            }
        }
        tableWidget->setRowHidden(i, !match);
    }

    for (int i = 0; i < listViewModel->rowCount(); ++i) {
        QStandardItem *item = listViewModel->item(i);
        bool match = item->text().toLower().contains(searchText);
        listView->setRowHidden(i, !match);
    }

    for (int i = 0; i < listWidget->count(); ++i) {
        QListWidgetItem *item = listWidget->item(i);
        bool match = item->text().toLower().contains(searchText);
        item->setHidden(!match);
    }
}

void MainWindow::loadInitialData()
{}

void MainWindow::addComputerToViews(const QString &model, double hdd, const QString &cpu, const QString &imagePath)
{

    QStandardItem *item = new QStandardItem();
    item->setText(QString("%1 (%2GB, %3)").arg(model).arg(hdd).arg(cpu));

    if (!imagePath.isEmpty()) {
        item->setData(imagePath, Qt::UserRole);
    }

    if (!imagePath.isEmpty() && QFile::exists(imagePath)) {
        QPixmap pix(imagePath);
        if (!pix.isNull()) {
            item->setIcon(QIcon(pix.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
        }
    }


    listViewModel->appendRow(item);

    int row = tableWidget->rowCount();
    tableWidget->insertRow(row);

    QTableWidgetItem *modelItem = new QTableWidgetItem(model);
    tableWidget->setItem(row, 0, modelItem);
    tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(hdd)));
    tableWidget->setItem(row, 2, new QTableWidgetItem(cpu));

    QListWidgetItem *listItem = new QListWidgetItem();
    listItem->setText(QString("%1 - %2GB - %3").arg(model).arg(hdd).arg(cpu));

    if (!imagePath.isEmpty() && QFile::exists(imagePath)) {
        QPixmap pix(imagePath);
        if (!pix.isNull()) {
            listItem->setIcon(QIcon(pix.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
        }
    }

    listWidget->addItem(listItem);
}

void MainWindow::updateSelectedImage(const QItemSelection &selected)
{
    if (selected.isEmpty()) {
        currentImageLabel->clear();
        return;
    }

    int row = selected.indexes().first().row();
    QStandardItem *item = listViewModel->item(row);

    QString imagePath = item->data(Qt::UserRole).toString();

    if (!imagePath.isEmpty() && QFile::exists(imagePath)) {
        QPixmap pix(imagePath);
        if (!pix.isNull()) {
            currentImageLabel->setPixmap(pix.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            currentImageLabel->setText("");
            return;
        }
    }

    currentImageLabel->clear();
}

void MainWindow::addComputer()
{
    QString model = modelEdit->text();
    QString hddText = hddEdit->text();
    QString cpu = cpuEdit->text();

    if (model.isEmpty() || hddText.isEmpty() || cpu.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Все обязательные поля должны быть заполнены");
        return;
    }

    bool ok;
    double hdd = hddText.toDouble(&ok);
    if (!ok || hdd <= 0) {
        QMessageBox::warning(this, "Ошибка", "Объем HDD должен быть положительным числом");
        return;
    }

    QString imagePath = QFileDialog::getOpenFileName(this,
                                                     "Выберите изображение компьютера",
                                                     "",
                                                     "Images (*.png *.jpg *.jpeg *.bmp);;Все файлы (*)");

    addComputerToViews(model, hdd, cpu, imagePath);

    modelEdit->clear();
    hddEdit->clear();
    cpuEdit->clear();

}

void MainWindow::deleteSelectedComputer()
{

    QModelIndexList selected = listView->selectionModel()->selectedIndexes();
    if (!selected.isEmpty()) {
        listViewModel->removeRow(selected.first().row());
    }

    selected = tableWidget->selectionModel()->selectedRows();
    if (!selected.isEmpty()) {
        tableWidget->removeRow(selected.first().row());
    }

    QList<QListWidgetItem*> items = listWidget->selectedItems();
    if (!items.isEmpty()) {
        delete listWidget->takeItem(listWidget->row(items.first()));
    }
}

void MainWindow::showContextMenu(const QPoint &pos)
{
    QMenu contextMenu("Контекстное меню", this);

    QAction *deleteAction = new QAction("Удалить", this);
    connect(deleteAction, &QAction::triggered, this, &MainWindow::deleteSelectedComputer);

    QAction *refreshAction = new QAction("Обновить", this);
    connect(refreshAction, &QAction::triggered, this, &MainWindow::refreshData);

    contextMenu.addAction(deleteAction);
    contextMenu.addAction(refreshAction);

    contextMenu.exec(listView->mapToGlobal(pos));
}

void MainWindow::loadFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Загрузить данные", "", "Текстовые файлы (*.txt);;Все файлы (*)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл");
        return;
    }

    refreshData();

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(',');
        if (parts.size() >= 3) {
            bool ok;
            double hdd = parts[1].trimmed().toDouble(&ok);
            if (ok) {
                QString imagePath = parts.size() > 3 ? parts[3].trimmed() : "";
                addComputerToViews(parts[0].trimmed(), hdd, parts[2].trimmed(), imagePath);
            }
        }
    }

    file.close();
    QMessageBox::information(this, "Успех", "Данные успешно загружены из файла");
}

void MainWindow::saveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить данные", "",
                                                    "Текстовые файлы (*.txt);;Все файлы (*)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл");
        return;
    }

    QTextStream out(&file);
    for (int i = 0; i < tableWidget->rowCount(); ++i) {
        out << tableWidget->item(i, 0)->text() << ", "
            << tableWidget->item(i, 1)->text() << ", "
            << tableWidget->item(i, 2)->text();

        QStandardItem *item = listViewModel->item(i);
        QString imagePath = item->data(Qt::UserRole).toString();
        if (!imagePath.isEmpty()) {
            out << ", " << imagePath;
        }
        out << "\n";
    }

    file.close();
    QMessageBox::information(this, "Успех", "Данные успешно сохранены в файл");
}

void MainWindow::refreshData()
{
    tableWidget->clearContents();
    tableWidget->setRowCount(0);
    listViewModel->clear();
    listWidget->clear();
    loadInitialData();
}

void MainWindow::sortItems(){
    listWidget->sortItems();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete) {
        deleteSelectedComputer();
    } else if (event->key() == Qt::Key_F5) {
        refreshData();
    }
    QMainWindow::keyPressEvent(event);
}

MainWindow::~MainWindow()
{}
