#include "DCMScan.h"
#include <QDir>
#include <QDirIterator>
#include <QDebug>
#include <DCMHeader.h>
#include <QImage>

extern compareSlices(DCMHeader*, DCMHeader*);
extern QImage* displayedSag;
extern QImage* displayedCor;

DCMScan::DCMScan(){
    currentSlice = 0;
    maxSlices = 0;
    corImage = new QImage();
    sagImage = new QImage();
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

    if(hasImages()){
        buildIndex();

        qDebug() << "Sorted.";
        currentSlice = (maxSlices/float(2.0));
        getSlice(currentSlice)->display();
   }
}

void DCMScan::buildIndex(){
    slices.clear();
    for (int i = 0; i<maxSlices; i++){
        slices.push_back(0);
    }

    std::vector<int> slicePositions;
    for (auto &currentItem : images){
        slicePositions.push_back(currentItem->getSlicePos());
    }

    std::vector<int> sortedSlicePos = slicePositions;
    std::sort(sortedSlicePos.begin(), sortedSlicePos.end());

    for (int i = 0; i<maxSlices; i++){
        slices[i] = find(slicePositions.begin(), slicePositions.end(), sortedSlicePos[i]) - slicePositions.begin();
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

void DCMScan::nextSlice(int){
    switch (axis) {
        case 2: // Coronal
            if (currentCorSlice < maxCorSlices){
                 currentCorSlice++;
                 createCoronal(int currentCorSlice);
            }
            break;
        case 1: // Sagital
            if (currentSagSlice < maxSagSlices){
                 currentSagSlice++;
                 createSaggital(int currentSagSlice);
            }
            break;
        case 0:
        default:
            if (currentSlice < maxSlices){
                 currentSlice++;
                 getSlice(currentSlice)->display();
                 getSlice(currentSlice)->putInTable();
            }
            break;
    }
}

void DCMScan::previousSlice(int){
    if (currentSlice > 1){
        currentSlice--;
        getSlice(currentSlice)->display();
        getSlice(currentSlice)->putInTable();
    }

    switch (axis) {
        case 2: // Coronal
            if (currentCorSlice > 1){
                 currentCorSlice--;
                 createCoronal(int currentCorSlice);
            }
            break;
        case 1: // Sagital
            if (currentSagSlice > 1){
                 currentSagSlice--;
                 createSaggital(int currentSagSlice);
            }
            break;
        case 0:
        default:
            if (currentSlice > 1){
                 currentSlice--;
                 getSlice(currentSlice)->display();
                 getSlice(currentSlice)->putInTable();
            }
            break;
    }
}

DCMHeader* DCMScan::getSlice(int pos){
    return images[slices[pos-1]];
}

void DCMScan::createCoronal(int pos){
    if(hasImages()){
        int width = images[0]->getWidth();
        int height = maxSlices;

        delete corImage;
        corImage = new QImage(width, height, QImage::Format_Indexed8);

        QVector<QRgb> greyscaleTable;
        for(int i = 0; i < 256; i++) greyscaleTable.push_back(qRgb(i,i,i));
        corImage->setColorTable(greyscaleTable);

        if ((pos >= 0) && (pos < width)){

            for (int i = 0; i<height; i++){
                for (int j = 0; j<width; j++){
                    corImage->setPixel(j, i, images[i]->getPixelValue(j, pos));
                }
            }
        }

        displayedCor = corImage;
        emit updateCoronalView();
    }
}

