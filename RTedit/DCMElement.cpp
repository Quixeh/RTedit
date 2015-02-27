#include "DCMElement.h"
#include <QDebug>
#include <string>
#include <sstream>
#include <fstream>

DCMElement::DCMElement(){
}

DCMElement::~DCMElement(){
}

QString DCMElement::getTag(){
    return tag;
}

void DCMElement::setTag(QString newTag){
    tag = newTag;
}

QString DCMElement::getVR(){
    return vr;
}

void DCMElement::setVR(QString newVR){
    vr = newVR;
}

int DCMElement::getVL(){
    return vl;
}

void DCMElement::setVL(int newVL){
    vl = newVL;
}

QString DCMElement::getValue(){
    return value;
}

void DCMElement::setValue(QString newVal){
    value = newVal;
}

bool DCMElement::updateFromDictionary(){

    std::ifstream fileInput;
    std::string line;
    std::stringstream ss;

    ss << getTag().toStdString().substr(1,4) << ", " << getTag().toStdString().substr(6,4);

    std::string search = ss.str(); // test variable to search in file
    // open file to search
    fileInput.open("dcmdict.txt");

    unsigned int curLine = 0;
    while(getline(fileInput, line)) {
        curLine++;
        if (line.find(search, 0) != std::string::npos) {
            //cout << "found: " << search << "line: " << curLine << endl;
            qDebug() << QString::fromStdString(line);
            fileInput.close();
            return true;
        }
    }
    return false;
}
