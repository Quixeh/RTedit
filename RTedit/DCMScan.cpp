#include "DCMScan.h"
#include <QDir>
#include <QDirIterator>
#include <QDebug>

DCMScan::DCMScan(){
    currentSlice = 0;
    maxSlices = 0;
}

DCMScan::~DCMScan(){

}

void DCMScan::importAll(){
}

void DCMScan::clearAll(){
    images.clear();
    structures.clear();
    plans.clear();
    doses.clear();
}

void DCMScan::openSingle(QString fileName){
    clearAll();
    DCMHeader* header = new DCMHeader;
    header->openFile(fileName);
    header->import();
    header->putInTable();
    if (header->getType() == "CT"){
        images.push_back(header);
        currentSlice = 1;
        maxSlices = 1;
    } else if (header->getType() == "RTSTRUCT"){
        structures.push_back(header);
    } else if (header->getType() == "RTDOSE"){
        doses.push_back(header);
    } else if (header->getType() == "RTPLAN"){
        plans.push_back(header);
    }
}

void DCMScan::openFolder(QString folderName){
    clearAll();
    currentSlice = 0;
    maxSlices = 0;
    QDir directory(folderName);
    QDirIterator it(directory);
    while (it.hasNext()) {
        QString fileName = it.next();
        if (fileName.right(4) == ".dcm"){
            //qDebug() << "Filename: " << fileName;
            DCMHeader* header = new DCMHeader;
            header->openFile(fileName);
            header->import();
            header->putInTable();
            if (header->getType() == "CT"){
                images.push_back(header);
                currentSlice++;
                maxSlices++;
            } else if (header->getType() == "RTSTRUCT"){
                structures.push_back(header);
            } else if (header->getType() == "RTDOSE"){
                doses.push_back(header);
            } else if (header->getType() == "RTPLAN"){
                plans.push_back(header);
            }
        }
    }
}

bool DCMScan::hasImages(){
    for (auto &currentItem : images){
        if (currentItem->getType() == "CT"){
            return true;
        }
    }
    return false;
}

void DCMScan::nextSlice(){
    qDebug() << "Next Slice...";
    if (currentSlice < maxSlices){
        currentSlice++;
        images[currentSlice-1]->display();
        images[currentSlice-1]->putInTable();
    }
    qDebug() << currentSlice;
}

void DCMScan::previousSlice(){
    qDebug() << "Prev Slice...";
    if (currentSlice > 1){
        currentSlice--;
        images[currentSlice-1]->display();
        images[currentSlice-1]->putInTable();
    }
    qDebug() << currentSlice;
}
