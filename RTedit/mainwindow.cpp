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

bool compareSlices(DCMHeader* h1, DCMHeader* h2){
    int a = h1->getSlicePos();
    int b = h2->getSlicePos();
    if(a == b){
        return false;
    } else if (a<b){
        return true;
    } else {
        return false;
    }
}

QString rtrim(const QString& str) {
  int n = str.size() - 1;
  for (; n >= 0; --n) {
    if (!str.at(n).isSpace()) {
      return str.left(n + 1);
    }
  }
  return "";
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);

    scan = new DCMScan;

    sceneTl = new QGraphicsScene();
    sceneBl = new QGraphicsScene();
    sceneTr = new QGraphicsScene();
    sceneBr = new QGraphicsScene();

    QPixmap blank(1,1);
    blank.fill(Qt::black);
    itemBl.setPixmap(blank);
    itemTl.setPixmap(blank);
    itemBr.setPixmap(blank);

    sceneBl->addItem(&itemBl);
    sceneBr->addItem(&itemBr);
    sceneTl->addItem(&itemTl);

    ui->viewBl->setScene(sceneBl);
    ui->viewBr->setScene(sceneBr);
    ui->viewTl->setScene(sceneTl);
    ui->viewAxial->setScene(sceneBl);

    ui->viewTl->setAxis(2);
    ui->viewBr->setAxis(1);

    setupTable();

    connect(&s, SIGNAL(elementsSig(QString, QString, int, QString, QString)), this,  SLOT(addTableValue(QString, QString, int, QString, QString)));
    connect(&s, SIGNAL(clearSig()), this,  SLOT(clearSlot()));
    connect(&s, SIGNAL(updateTransverseViewsSig()), this,  SLOT(updateTransverseViewsSlot()));
    connect(scan, SIGNAL(updateCoronalView()), this,  SLOT(updateCoronalViewsSlot()));
    connect(scan, SIGNAL(updateSaggitalView()), this,  SLOT(updateSaggitalViewsSlot()));
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
        itemBl.setPixmap(QPixmap::fromImage(*displayedTra));
        ui->viewBl->fitInView(sceneBl->sceneRect(), Qt::KeepAspectRatio);
        ui->viewAxial->fitInView(sceneBl->sceneRect(), Qt::KeepAspectRatio);
    }
}

void MainWindow::updateCoronalViews(){
    if (scan->hasImages()){
        qDebug() << "Coronal Updated";
        itemTl.setPixmap(QPixmap::fromImage(*displayedCor));
        ui->viewTl->fitInView(sceneTl->sceneRect(), Qt::KeepAspectRatio);
    }
}

void MainWindow::updateSaggitalViews(){
    if (scan->hasImages()){
        itemBr.setPixmap(QPixmap::fromImage(*displayedSag));
        ui->viewBr->fitInView(sceneBr->sceneRect(), Qt::KeepAspectRatio);
    }
}

void MainWindow::updateTransverseViewsSlot(){
    updateTransverseViews();
}

void MainWindow::updateCoronalViewsSlot(){
    updateCoronalViews();
}

void MainWindow::updateSaggitalViewsSlot(){
    updateSaggitalViews();
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
