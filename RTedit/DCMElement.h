#ifndef DCMELEMENT_H
#define DCMELEMENT_H

#include <QObject>
#include <qstring.h>

class DCMElement : QObject{
    Q_OBJECT
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
        void addToTable();

    private:
        QString tag;
        QString vr;
        int vl;
        QString value;
        QString description;

    signals:
        void addToTableSig(QString, QString, int, QString, QString);
};

#endif // DCMELEMENT_H
