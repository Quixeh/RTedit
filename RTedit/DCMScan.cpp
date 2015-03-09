#include "DCMScan.h"
#include <QDir>
#include <QDirIterator>
#include <QDebug>

DCMScan::DCMScan(){

}

DCMScan::~DCMScan(){

}

void DCMScan::importAll(){
    for (auto &currentItem : items){
        currentItem->import();
    }
}

void DCMScan::openSingle(QString fileName){
    DCMHeader* header = new DCMHeader;
    header->openFile(fileName);
    items.push_back(header);
}

void DCMScan::openFolder(QString folderName){
    QDir directory(folderName);
    QDirIterator it(directory);
    while (it.hasNext()) {
        QString fileName = it.next();

        if (fileName.right(4) == ".dcm"){
            qDebug() << "Filename: " << fileName;
            DCMHeader* header = new DCMHeader;
            header->openFile(fileName);
            items.push_back(header);
        }
    }
}
