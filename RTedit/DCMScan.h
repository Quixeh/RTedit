#ifndef DCMSCAN_H
#define DCMSCAN_H

#include <QObject>
#include <DCMHeader.h>

class DCMScan : public QObject {
    Q_OBJECT
    public:
        DCMScan();
        ~DCMScan();
        void importAll();
        void openSingle(QString);
        void openFolder(QString);
        bool hasImages();

        void nextSlice(int);
        void previousSlice(int);

        void clearAll();

        void createCoronal(int);
        void createSaggital(int);

    private:
        std::vector<DCMHeader*> images;
        std::vector<DCMHeader*> structures;
        std::vector<DCMHeader*> plans;
        std::vector<DCMHeader*> doses;
        int currentSlice;
        int maxSlices;
        int currentCorSlice;
        int maxCorSlices;
        int currentSagSlice;
        int maxSagSlices;
        float sliceWidth;
        float pixelSpacing;

        std::vector<int> slices;

        void buildIndex();
        void setupOrthogonal();
        DCMHeader* getSlice(int);
        QImage* sagImage;
        QImage* corImage;

    signals:
        void updateCoronalView();
        void updateSaggitalView();
};


#endif // DCMSCAN_H
