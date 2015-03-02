#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDir>
#include <QPixmap>
#include <QGraphicsPixmapItem>

#include <DCMFile.h>
#include <DCMHeader.h>
#include <DCMElement.h>
#include <SlotTransfer.h>
#include <QObject>

DCMHeader* dicomFile;
QImage* displayed;
SlotTransfer s;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);

    //s = new SlotTransfer();
    dicomFile = new DCMHeader;

    QGraphicsScene* scene = new QGraphicsScene();
    scene->addRect(1,1,1,1,QPen(QColor(Qt::black)),QBrush());

    ui->viewTl->setScene(scene);
    ui->viewBl->setScene(scene);
    ui->viewBr->setScene(scene);

    setupTable();

    connect(&s, SIGNAL(elementsSig(QString, QString, int, QString, QString)), this,  SLOT(addTableValue(QString, QString, int, QString, QString)));
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_actionOpen_triggered(){
    QString fileName = QFileDialog::getOpenFileName(0, "Open DICOM File...", QDir::currentPath(), "DICOM Files (*.dcm);;All files (*.*)", new QString("DICOM Files (*.dcm)"));
    dicomFile->openFile(fileName);
    dicomFile->import();

    QGraphicsScene* scene = new QGraphicsScene();
//   QGraphicsView* view = new QGraphicsView(scene);
    ui->viewBl->setScene(scene);
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(*displayed));
    scene->addItem(item);
    ui->viewBl->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    //view->show();
}

void MainWindow::setupTable(){
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(5);

    ui->tableWidget->verticalHeader()->setVisible(false);
}

void MainWindow::addTableValue(QString tag, QString vr, int vl, QString description, QString value){
    int rowID = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(rowID);
    ui->tableWidget->setItem(rowID, 0, new QTableWidgetItem(tag));
    ui->tableWidget->setItem(rowID, 1, new QTableWidgetItem(vr));
    ui->tableWidget->setItem(rowID, 2, new QTableWidgetItem(vl));
    ui->tableWidget->setItem(rowID, 3, new QTableWidgetItem(description));
    ui->tableWidget->setItem(rowID, 4, new QTableWidgetItem(value));
}

void MainWindow::on_actionExit_triggered(){
    QApplication::quit();
}
