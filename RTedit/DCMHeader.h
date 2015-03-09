#ifndef DCMHEADER_H
#define DCMHEADER_H

#include "DCMFile.h"
#include "DCMElement.h"
#include "vector"

class DCMHeader : public DCMFile {
    public:
        DCMHeader();
        ~DCMHeader();
        void import();

    private:
        std::vector<DCMElement*> elements;
        DCMElement* curElement;

        bool readTag(int = 0);
        bool readTagReturn(int = 0);
        bool readVR();
        bool readVL(int = 0, bool = false);
        bool readValue(int = 0, bool = false);

        int byteOrder;
        bool implicit;

    protected:

};

#endif // DCMHEADER_H
