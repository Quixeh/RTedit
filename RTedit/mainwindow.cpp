#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDir>
#include <QPixmap>
#include <QGraphicsPixmapItem>

#include <DCMScan.h>
#include <DCMFile.h>
#include <DCMHeader.h>
#include <DCMElement.h>
#include <SlotTransfer.h>
#include <QObject>
#include <qdebug.h>

DCMScan* scan;
QImage* displayedTra;
QImage* displayedSag;
QImage* displayedCor;
SlotTransfer s;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);

    scan = new DCMScan;

    QGraphicsScene* scene = new QGraphicsScene();
    scene->addRect(1,1,1,1,QPen(QColor(Qt::black)),QBrush());

    ui->viewTl->setScene(scene);
    ui->viewBl->setScene(scene);
    ui->viewBr->setScene(scene);
    ui->viewAxial->setScene(scene);

    sceneTl = new QGraphicsScene();
    sceneBl = new QGraphicsScene();
    sceneTr = new QGraphicsScene();
    sceneBr = new QGraphicsScene();

    QPixmap blank(1,1);
    blank.fill(Qt::black);
    itemBl.setPixmap(blank);
    sceneBr->addItem(&itemBl);

    ui->viewBl->setScene(sceneBr);
    ui->viewAxial->setScene(sceneBr);

    setupTable();

    connect(&s, SIGNAL(elementsSig(QString, QString, int, QString, QString)), this,  SLOT(addTableValue(QString, QString, int, QString, QString)));
    connect(&s, SIGNAL(clearSig()), this,  SLOT(clearSlot()));
    connect(&s, SIGNAL(updateTransverseViewsSig()), this,  SLOT(updateTransverseViewsSlot()));
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_actionOpen_triggered(){
    QString fileName = QFileDialog::getOpenFileName(0, "Open DICOM File...", QDir::currentPath(), "DICOM Files (*.dcm);;All files (*.*)", new QString("DICOM Files (*.dcm)"));
    scan->openSingle(fileName);
    scan->importAll();
    updateTransverseViews();
}

void MainWindow::on_actionOpen_Folder_triggered(){
    QString folderName = QFileDialog::getExistingDirectory(0, "Select DICOM Folder...", QDir::currentPath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    scan->openFolder(folderName);
    scan->importAll();
    updateTransverseViews();
}

void MainWindow::updateTransverseViews(){
    if (scan->hasImages()){
       // delete sceneBl;
       // sceneBl = new QGraphicsScene();
        //ui->viewBl->setScene(sceneBr);
       // ui->viewAxial->setScene(sceneBr);
        itemBl.setPixmap(QPixmap::fromImage(*displayedTra));
       // sceneBr->addItem(&itemBl);
        ui->viewBl->fitInView(sceneBr->sceneRect(), Qt::KeepAspectRatio);
        ui->viewAxial->fitInView(sceneBr->sceneRect(), Qt::KeepAspectRatio);
    }
}

void MainWindow::updateTransverseViewsSlot(){
    updateTransverseViews();
}

void MainWindow::setupTable(){
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setColumnWidth(0, 80);
    ui->tableWidget->setColumnWidth(1, 30);
    ui->tableWidget->setColumnWidth(2, 60);
    ui->tableWidget->setColumnWidth(3, 200);
    ui->tableWidget->setColumnWidth(4, 200);
}

void MainWindow::addTableValue(QString tag, QString vr, int vl, QString description, QString value){
    int rowID = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(rowID);
    ui->tableWidget->setItem(rowID, 0, new QTableWidgetItem(tag));
    ui->tableWidget->setItem(rowID, 1, new QTableWidgetItem(vr));
    ui->tableWidget->setItem(rowID, 2, new QTableWidgetItem(QString::number(vl)));
    ui->tableWidget->setItem(rowID, 3, new QTableWidgetItem(description));
    ui->tableWidget->setItem(rowID, 4, new QTableWidgetItem(value));
}

void MainWindow::on_actionExit_triggered(){
    QApplication::quit();
}

void MainWindow::resizeEvent(QResizeEvent* event){
   QMainWindow::resizeEvent(event);
   updateViews();
}

void MainWindow::updateViews(){
    ui->viewBl->fitInView(ui->viewBl->sceneRect(), Qt::KeepAspectRatio);
    ui->viewAxial->fitInView(ui->viewAxial->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::on_Tabs_currentChanged(int){
    updateViews();
}

void MainWindow::clearSlot(){
    ui->tableWidget->setRowCount(0);
}
