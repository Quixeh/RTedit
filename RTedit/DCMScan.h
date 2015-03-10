#ifndef DCMSCAN_H
#define DCMSCAN_H

#include <QObject>
#include <DCMHeader.h>

class DCMScan {
    public:
        DCMScan();
        ~DCMScan();
        void importAll();
        void openSingle(QString);
        void openFolder(QString);
        bool hasImages();

        void nextSlice();
        void previousSlice();
        void clearAll();

    private:
        std::vector<DCMHeader*> images;
        std::vector<DCMHeader*> structures;
        std::vector<DCMHeader*> plans;
        std::vector<DCMHeader*> doses;
        int currentSlice;
        int maxSlices;
};

#endif // DCMSCAN_H
