#ifndef DCMELEMENT_H
#define DCMELEMENT_H

#include <qstring.h>

class DCMElement {
    public:
        DCMElement();
        ~DCMElement();
        bool readIn();

        void setTag(QString);
        QString getTag();
        void setVR(QString);
        QString getVR();
        void setVL(int);
        int getVL();
        void setValue(QString);
        QString getValue();

        bool updateFromDictionary();
        void clear();
        void printToDebug();

    private:
        QString tag;
        QString vr;
        int vl;
        QString value;
        QString description;
};

#endif // DCMELEMENT_H
