#include "DCMImage.h"
#include <QImage>

extern QImage* displayedTra;

DCMImage::DCMImage(){
    height = 0;
    width = 0;
}

DCMImage::~DCMImage(){

}

void DCMImage::setDimensions(int xNew, int yNew){
    std::vector<int> row;

    height = yNew;
    width = xNew;

    for (int x = 0; x< xNew; x++){
            for (int y = 0; y< yNew; y++){
                row.push_back(0);
            }
            pixelData.push_back(row);
            row.clear();
    }

    image = new QImage(xNew, yNew, QImage::Format_Indexed8);

    QVector<QRgb> greyscaleTable;
    for(int i = 0; i < 256; i++) greyscaleTable.push_back(qRgb(i,i,i));
    image->setColorTable(greyscaleTable);
}

void DCMImage::setPixel(int x, int y, int value){
    pixelData[x][y] = value;
}

int DCMImage::getPixel(int x, int y){
    return pixelData[x][y];
}

void DCMImage::update(){
    int max = 0;
    int min = 0;

    for (int y = 0; y< height; y++){
        for (int x = 0; x< width; x++){
            if (pixelData[x][y] > max){
                max = pixelData[x][y];
            }
            if (pixelData[x][y] < min){
                min = pixelData[x][y];
            }
        }
    }

    for (int x = 0; x< width; x++){
        for (int y = 0; y< height; y++){
            int value = 255*((pixelData[x][y] - min)/float((max-min)));
            image->setPixel(x, y, value);
        }
    }
}

void DCMImage::save(QString filename){
    image->save(filename);
}

void DCMImage::show(){
    displayedTra = image;
}
