#include "SlotTransfer.h"

SlotTransfer::SlotTransfer(){

}

SlotTransfer::~SlotTransfer(){

}

void SlotTransfer::addElementToTableSlot(QString tag, QString vr, int vl, QString description, QString value){
    emit elementsSig(tag, vr, vl, description, value);
}
