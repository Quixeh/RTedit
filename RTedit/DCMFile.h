#ifndef DCMFILE_H
#define DCMFILE_H

#include <qstring.h>

class DCMFile {
    public:
        DCMFile();
        ~DCMFile();
        bool openFile(QString);
        void closeFile();

    private:
        QString filename;

    protected:
        FILE* fid;
        int readInt2(int = 0);
        int readInt4(int = 0);
        void byte_to_2nibbles(const unsigned char, unsigned char*, unsigned char*);
        QString readStr(int);

};

#endif // DCMFILE_H
