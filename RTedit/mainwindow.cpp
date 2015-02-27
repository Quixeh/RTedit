#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDir>

#include <DCMFile.h>
#include <DCMHeader.h>

DCMHeader* dicomFile;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){

    ui->setupUi(this);


    dicomFile = new DCMHeader;
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_actionOpen_triggered(){
    QString fileName = QFileDialog::getOpenFileName(0, "Open DICOM File...", QDir::currentPath(), "DICOM Files (*.dcm);;All files (*.*)", new QString("DICOM Files (*.dcm)"));
    dicomFile->openFile(fileName);
    dicomFile->import();
}
