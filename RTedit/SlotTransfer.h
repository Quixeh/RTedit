#ifndef SLOTTRANSFER_H
#define SLOTTRANSFER_H

#include <QObject>
#include <QString>

class SlotTransfer : public QObject {
    Q_OBJECT
    public:
        SlotTransfer();
        ~SlotTransfer();

    private:
        void elements(QString, QString, int, QString, QString);

    signals:
        void elementsSig(QString, QString, int, QString, QString);
        void clearSig();
        void updateTransverseViewsSig();

    public slots:
        void addElementToTableSlot(QString, QString, int, QString, QString);
        void clearTableSlot();
        void updateTransverseViewsSlot();
};

#endif // SLOTTRANSFER_H
