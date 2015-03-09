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

    private:
        std::vector<DCMHeader*> items;
};

#endif // DCMSCAN_H
