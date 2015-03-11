#include "DCMScan.h"
#include <QDir>
#include <QDirIterator>
#include <QDebug>
#include <DCMHeader.h>
#include <QImage>
#include <QProgressDialog>
#include <QApplication>

extern compareSlices(DCMHeader*, DCMHeader*);
extern QImage* displayedSag;
extern QImage* displayedCor;

DCMScan::DCMScan(){
    currentSlice = 0;
    maxSlices = 0;
    sliceWidth = 0;
    pixelSpacing = 0;
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

    int fileNo = 0;

    QProgressDialog* progressDialog = new QProgressDialog("Loading DICOM Data...", "Abort", 0, directory.count());
    //progressDialog->setWindowIcon(QIcon(":/images/icons/silk/user_green.png"));
    progressDialog->show();
    progressDialog->setWindowModality(Qt::WindowModal);

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
        fileNo++;
        progressDialog->setValue(fileNo);
        QApplication::processEvents();
        if (progressDialog->wasCanceled()){
            return;
        }
    }

    if(hasImages()){
        buildIndex();

        qDebug() << "Sorted.";
        currentSlice = (maxSlices/float(2.0));
        getSlice(currentSlice)->display();
   }

    setupOrthogonal();
    createCoronal(256);
    createSaggital(256);
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

void DCMScan::nextSlice(int axis){
    switch (axis) {
        case 2: // Coronal
            if (currentCorSlice < maxCorSlices){
                 currentCorSlice++;
                 createCoronal(currentCorSlice);
            }
            break;
        case 1: // Sagital
            if (currentSagSlice < maxSagSlices){
                 currentSagSlice++;
                 createSaggital(currentSagSlice);
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

void DCMScan::previousSlice(int axis){
    if (currentSlice > 1){
        currentSlice--;
        getSlice(currentSlice)->display();
        getSlice(currentSlice)->putInTable();
    }

    switch (axis) {
        case 2: // Coronal
            if (currentCorSlice > 1){
                 currentCorSlice--;
                 createCoronal(currentCorSlice);
            }
            break;
        case 1: // Sagital
            if (currentSagSlice > 1){
                 currentSagSlice--;
                 createSaggital(currentSagSlice);
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


void DCMScan::createSaggital(int pos){
    qDebug() << "Creating Saggital " << pos;
    if(hasImages()){
        int width = floor(maxSlices*sliceWidth/pixelSpacing);
        int height = images[0]->getHeight();

        delete sagImage;
        sagImage = new QImage(width, height, QImage::Format_Indexed8);

        QVector<QRgb> greyscaleTable;
        for(int i = 0; i < 256; i++) greyscaleTable.push_back(qRgb(i,i,i));
        sagImage->setColorTable(greyscaleTable);

        if ((pos >= 0) && (pos < images[0]->getWidth())){
            for (int i = 0; i<width; i++){
                for (int j = 0; j<height; j++){
                    int lower = floor(i/sliceWidth);
                    int upper = ceil(i/sliceWidth);
                    float remainder = (i/sliceWidth) - lower;

                    int value = (((1-remainder)*images[lower]->getPixelValue(pos, j)) + (remainder * images[upper]->getPixelValue(pos, j)));


                    sagImage->setPixel(i, j, value);
                }
            }
        }
        sagImage->save("Test3.png");
        displayedSag = sagImage;
        emit updateSaggitalView();
        qDebug() << "Created Saggital";
    }
}

void DCMScan::createCoronal(int pos){

    qDebug() << "Creating Coronal " << pos;
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
        corImage->save("Test2.png");
        displayedCor = corImage;
        emit updateCoronalView();
        qDebug() << "Created Coronal";
    }
}

void DCMScan::setupOrthogonal(){
    int maxCorSlices = images[0]->getHeight();
    int maxSagSlices = images[0]->getWidth();

    sliceWidth = abs(getSlice(1)->getSlicePos() - getSlice(2)->getSlicePos());
    pixelSpacing = images[0]->getPixelSpacing();
}
