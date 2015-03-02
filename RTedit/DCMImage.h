#ifndef DCMIMAGE_H
#define DCMIMAGE_H

#include <QImage>

class DCMImage{
    public:
        DCMImage();
        ~DCMImage();
        void setDimensions(int, int);
        void setPixel(int, int, int);
        int getPixel(int, int);
        void save(QString);
        void update();
        void show();

    private:
        std::vector<std::vector<int> > pixelData;
        QImage* image;
        int height;
        int width;
};

#endif // DCMIMAGE_H
