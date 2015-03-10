#include <QDebug>
#include "DCMFile.h"
#include "string"
#include <sstream>

DCMFile::DCMFile(){
    filename = "";
}

bool DCMFile::openFile(QString fName){
    filename = fName;
    fid = fopen(filename.toStdString().c_str(), "rb");

    if (fid == NULL){
        qDebug() << "Error opening file";
        filename = "";
        return false;
    } else {
        //qDebug() << "File " << filename << "opened successfully.";
        return true;
    }
}

void DCMFile::closeFile(){
    if(filename != ""){
        fclose (fid);
        filename = "";
    } else {
        qDebug() << "File close requested, but no file was open.";
    }
}

DCMFile::~DCMFile(){
    closeFile();
}



int DCMFile::readInt2(int byteOrder){
    unsigned char bytes[2];

    if (!fread(bytes, 1, 2, fid)){
        qDebug() << "Error: Could not read file." << endl;
        return false; // End of file
    }

    int us0, us1;

    switch(byteOrder){
        case 1:
            us1 = (int) bytes[0];
            us0 = (int) bytes[1];
            break;
        case 0:
        default:
            us1 = (int) bytes[1];
            us0 = (int) bytes[0];
            break;
    }

    return ((us1 << 8) | (us0));
}

int DCMFile::readInt4(int byteOrder){
    unsigned char bytes[4];

    if (!fread(bytes, 1, 4, fid)){
        qDebug() << "Error: Could not read file." << endl;
        return false; // End of file
    }

    int ul0, ul1, ul2, ul3;

    switch(byteOrder){
        case 1:
            ul3 = (int) bytes[0];
            ul2 = (int) bytes[1];
            ul1 = (int) bytes[2];
            ul0 = (int) bytes[3];
            return ((ul3 << 24) | (ul2 << 16) | (ul1 << 8) | (ul0));
            break;
        case 0:
        default:
            ul3 = (int) bytes[3];
            ul2 = (int) bytes[2];
            ul1 = (int) bytes[1];
            ul0 = (int) bytes[0];
            return ((ul3 << 24) | (ul2 << 16) | (ul1 << 8) | (ul0));
    }
}

void DCMFile::byte_to_2nibbles(const unsigned char byte, unsigned char * hiNib, unsigned char * loNib){
    (* hiNib) = byte;
    (* loNib) = byte;

    (* hiNib) >>= 4; // Hi Nibble - shift byte four bits to the right.

    (* hiNib) = ((* hiNib) & 15);
    (* loNib) = ((* loNib) & 15); // Low Nibble - mask out lower four bits.
}

QString DCMFile::readStr(int vL){
    std::stringstream ss;
    if (vL){ // VL can be zero
        /*unsigned char bytes[64];
        if (!fread(bytes, 1, vL, fid)){
            qDebug() << "Error: Could not read file." << endl;
            return ""; // End of file
        }

        for (int i = 0; i<vL; i++){
            ss << bytes[i];
        }*/

        QByteArray bytes = QByteArray(vL, '\0');
                if (!fread(bytes.data(), 1, vL, fid)){
                    qDebug() << "File Error";
                    return "";
                }

                QList<QByteArray> list = bytes.split('\\');

                foreach(QByteArray byteArr, list) {
                    //if (!(o->pCheckVLCharacterRepertoire)( o, byteArr)) ERR_MSG_RTN_FLS;
                    ss << std::string(byteArr);
                }
    }

    QString value = QString::fromStdString(ss.str());

    return value;
}
