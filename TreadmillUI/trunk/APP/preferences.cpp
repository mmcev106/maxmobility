#include "preferences.h"
//#include "qextserialenumerator.h"

const QString Preferences::FILENAME = "Preferences.txt";

bool Preferences::gender = MALE;
bool Preferences::measurementSystem = STANDARD;


/*void Preferences::initializeSerialPort(){

    QString portName = QextSerialEnumerator::getPorts().at(0).portName;

    QextSerialPort* port = new QextSerialPort(portName, QextSerialPort::EventDriven);
    port->setBaudRate(BAUD56000);
    port->setFlowControl(FLOW_OFF);
    port->setParity(PAR_NONE);
    port->setDataBits(DATA_8);
    port->setStopBits(STOP_2);

    _serialPort = port;
}


QextSerialPort* Preferences::serialPort(){
    return _serialPort;
}
*/
