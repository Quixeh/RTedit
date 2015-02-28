#include "DCMHeader.h"
#include "DCMElement.h"
#include <QDebug>
#include <sstream>

DCMHeader::DCMHeader(){
    curElement = new DCMElement();
    byteOrder = 0;
    implicit = false;
}

DCMHeader::~DCMHeader(){

}

bool DCMHeader::readTag(int byteOrder){
    unsigned char bytes[4];

    if (!fread(bytes, 1, 4, fid)){ // Read the four bytes, and put them into 'byts' - if we can't do that we've reached the end of the file.
        qDebug() << "Error: Could not read file." << endl;
        return false; // End of file
    }

    unsigned char nib0, nib1, nib2, nib3, nib4, nib5, nib6, nib7;

    switch (byteOrder){
        case 1: // Big Endian
            // Process 1st unsigned long - Group Number
            byte_to_2nibbles(bytes[0], &nib0, &nib1);
            byte_to_2nibbles(bytes[1], &nib2, &nib3);

            // Process 2nd unsigned long - Element Number
            byte_to_2nibbles(bytes[2], &nib4, &nib5);
            byte_to_2nibbles(bytes[3], &nib6, &nib7);

            break;
        case 0: // Little Endian
        default: // Default to LE.

            // Process 1st unsigned long - Group Number
            byte_to_2nibbles(bytes[1], &nib0, &nib1);
            byte_to_2nibbles(bytes[0], &nib2, &nib3);

            // Process 2nd unsigned long - Element Number
            byte_to_2nibbles(bytes[3], &nib4, &nib5);
            byte_to_2nibbles(bytes[2], &nib6, &nib7);
            break;
    }

    char tagStr[11];
    sprintf(tagStr, "(%X%X%X%X,%X%X%X%X)", nib0, nib1, nib2, nib3, nib4, nib5, nib6, nib7);

    curElement->setTag(tagStr);
    return true;
}

bool DCMHeader::readTagReturn(int byteOrder){
    bool returnVal = readTag(byteOrder);
    fseek(fid, -4, SEEK_CUR);
    return returnVal;
}

bool DCMHeader::readVR(){
    char bytes[2];

    if (!fread(bytes, 1, 2, fid)){
        qDebug() << "Error: Could not read file." << endl;
        return false; // End of file
    }

    curElement->setVR(bytes);
    return true;
}

bool DCMHeader::readVL(int byteOrder, bool implicit){
    int valueLen = 0;
    std::string valueRep = curElement->getVR().toStdString();

    if (implicit){
        valueLen = DCMFile::readInt4(byteOrder);
    } else {
        if ((!strncmp(valueRep.c_str(), "OB", 2)) || (!strncmp(valueRep.c_str(), "OW", 2)) || (!strncmp(valueRep.c_str(), "OF", 2)) |
            (!strncmp(valueRep.c_str(), "SQ", 2)) || (!strncmp(valueRep.c_str(), "UT", 2)) || (!strncmp(valueRep.c_str(), "UN", 2)) ){
            valueLen = DCMFile::readInt4(byteOrder);
        } else {
            valueLen = DCMFile::readInt2(byteOrder);
        }
    }

    curElement->setVL(valueLen);
    return true;
}

bool DCMHeader::readValue(int byteOrder, bool){

    std::stringstream ss;

    if ((!strncmp(curElement->getVR().toStdString().c_str(), "UL", 2)) ||
        (!strncmp(curElement->getVR().toStdString().c_str(), "OB", 2)) ){

        ss << readInt4(byteOrder);
        curElement->setValue(QString::fromStdString(ss.str()));
        return true;

    } else if ((!strncmp(curElement->getVR().toStdString().c_str(), "OW", 2)) ||
               (!strncmp(curElement->getVR().toStdString().c_str(), "SS", 2)) ||
               (!strncmp(curElement->getVR().toStdString().c_str(), "US", 2)) ){// 2 Bit Integers

        ss << readInt2(byteOrder);
        curElement->setValue(QString::fromStdString(ss.str()));
        return true;
    } else if ((!strncmp(curElement->getVR().toStdString().c_str(), "AE", 2)) || // Strings
               (!strncmp(curElement->getVR().toStdString().c_str(), "CA", 2)) ||
               (!strncmp(curElement->getVR().toStdString().c_str(), "CS", 2)) ||
               (!strncmp(curElement->getVR().toStdString().c_str(), "DA", 2)) ||
               (!strncmp(curElement->getVR().toStdString().c_str(), "DS", 2)) ||
               (!strncmp(curElement->getVR().toStdString().c_str(), "IS", 2)) ||
               (!strncmp(curElement->getVR().toStdString().c_str(), "LO", 2)) ||
               (!strncmp(curElement->getVR().toStdString().c_str(), "PN", 2)) ||
               (!strncmp(curElement->getVR().toStdString().c_str(), "SH", 2)) ||
               (!strncmp(curElement->getVR().toStdString().c_str(), "ST", 2)) ||
               (!strncmp(curElement->getVR().toStdString().c_str(), "TM", 2)) ||
               (!strncmp(curElement->getVR().toStdString().c_str(), "UI", 2)) ||
               (!strncmp(curElement->getVR().toStdString().c_str(), "UN", 2)) ){

        curElement->setValue(readStr(curElement->getVL()));
        return true;
    } else {
        qDebug() << "I'm not sure how to read " << curElement->getVR();
        fseek(fid, curElement->getVL(), SEEK_CUR);
        return false;
    }
}

void DCMHeader::import(){
    // NEW Dicom files start with a Premable (128 bytes) and Header (4 bytes - the string DICM).
    // OLD File might not! - Could skip straight to the data elements. We can check by looking for a tag in the first 4 bytes.

    readTagReturn();
    qDebug() << curElement->getTag() << endl;

    // Check to see if tag is in dictionary (implement this...)

    // otherwise... read the Preable...

    if (fseek(fid, 128, SEEK_SET)){ // Skip the Preamble
        qDebug() << "Error: Couldn't Read Preamble" << endl;
    }

    char DICM[5] = {'\0'};
    if (!fread(DICM, 1, 4, fid)){
        qDebug() << "Error: Couldn't Read DICM" << endl;
    };

    if (strncmp(DICM, "DICM", 4)){
            // Next 4 bytes should be "DICM
            qDebug() << "Error: DICM Identifier not present..." << endl;
    } else {
            qDebug() << "File identified as DICOM\n" << endl;
    }

    bool finished = false;
    byteOrder = 0; // Set LE for Meta
    implicit = false; // Set Explicit for Meta

    while(!finished){ // Read the File Meta Infromation (GN = 0002)
        curElement->clear();
        readTag();
        curElement->updateFromDictionary();

        if (!strncmp(curElement->getTag().toStdString().c_str()+1, "0002", 4)) {

            readVR(); // Use Explicit VR
            readVL(); // Use Exlpicit VL
            readValue();

            curElement->printToDebug();

            if (!strncmp(curElement->getTag().toStdString().c_str(), "(0002,0010)", 11)) {
                if (!strncmp(curElement->getValue().toStdString().c_str(), "1.2.840.10008.1.2.1.99", 21)){
                    qDebug() << "Deflated Explicit VR Little Endian\n" << endl;
                } else if (!strncmp(curElement->getValue().toStdString().c_str(), "1.2.840.10008.1.2.2", 19)){
                    //qDebug() << "Big Endian Explicit\n" << endl;
                    byteOrder = 1;
                } else if (!strncmp(curElement->getValue().toStdString().c_str(), "1.2.840.10008.1.2.1", 19)){
                    //qDebug() << "Little Endian Explicit\n" << endl;
                } else {
                    //qDebug() << "Little Endian Implicit\n" << endl;
                    implicit = true;
                }
            }

            elements.push_back(curElement);
        } else {
            finished = true;
            fseek(fid, -4, SEEK_CUR);   // Seek back to the start of the tag.
        }
    }

    finished = false;
    int count = 0;

    while(!finished){ // Read the DICOM Header...
        curElement->clear();
        count++;
        if (readTag(byteOrder)){
            if (!strncmp(curElement->getTag().toStdString().c_str(), "(7FE0,0010)", 11)){
                curElement->updateFromDictionary();
                readVL(byteOrder, implicit);
                curElement->printToDebug();

                finished = true;
            } else {
                curElement->updateFromDictionary();
                if (!implicit) readVR();
                readVL(byteOrder, implicit);
                readValue(byteOrder, implicit);
                curElement->printToDebug();
                elements.push_back(curElement);
            }
        } else {
            finished = true;
        }
    }

    qDebug() << "Reached end of DICOM File.";
}
