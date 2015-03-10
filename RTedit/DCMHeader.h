#ifndef DCMHEADER_H
#define DCMHEADER_H

#include "DCMFile.h"
#include "DCMElement.h"
#include "DCMImage.h"
#include "vector"
#include <QObject>

class DCMHeader : public DCMFile{
    Q_OBJECT
    public:
        DCMHeader();
        ~DCMHeader();
        void import();
        void putInTable();
        QString getType();
        void display();


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

        QString type;
        DCMImage* image;

    protected:


    signals:
        void clearTableSig();
        void updateTransverseViewsSig();

};

#endif // DCMHEADER_H
