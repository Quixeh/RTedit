#ifndef DCMHEADER_H
#define DCMHEADER_H

#include "DCMFile.h"
#include "DCMElement.h"
#include "DCMImage.h"
#include "vector"
#include <QObject>
#include <QDebug>

class DCMHeader : public DCMFile{
    Q_OBJECT
    public:
        DCMHeader();
        ~DCMHeader();
        void import();
        void putInTable();
        QString getType();
        void display();
        int getSlicePos() const;
        int getWidth();
        int getHeight();
        int getPixelValue(int, int);

    private:
        std::vector<DCMElement*> elements;
        DCMElement* curElement;

        bool readTag(int = 0);
        bool readTagReturn(int = 0);
        bool readVR();
        bool readVL(int = 0, bool = false);
        bool readValue(int = 0, bool = false);
        void readSequence(int);

        int byteOrder;
        bool implicit;
        int slicePosition;

        QString type;
        DCMImage* image;

    protected:


    signals:
        void clearTableSig();
        void updateTransverseViewsSig();
};

#endif // DCMHEADER_H
