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
        std::vector<DCMElement> elements;
        DCMElement* curElement;

        bool readTag(int = 0);
        bool readTagReturn(int = 0);
        bool readVR();
        bool readVL();
        bool readValue();

    protected:

};

#endif // DCMHEADER_H
