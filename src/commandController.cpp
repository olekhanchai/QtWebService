#include "commandController.h"

QSerialPort *CommandController::m_serial = nullptr;
bool CommandController::opened = false;
QString CommandController::result = "";

CommandController::CommandController(QObject* parent)
    : HttpRequestHandler(parent) {
    connect(m_serial, &QSerialPort::errorOccurred, this, handleError);
    connect(m_serial, &QSerialPort::readyRead, this, readData);
    m_serial = new QSerialPort();
}

void CommandController::service(HttpRequest &request, HttpResponse &response) {


    QString inputData = request.getParameter("data");
    if (!opened) {
        openSerialPort();
    }
    if (inputData.length() > 0) {
        m_serial->write(QString().toLatin1().fromBase64(inputData.toLatin1())+"\r\n");
    }
    response.write(result.toLatin1(),true);
}

void CommandController::openSerialPort()
{
    m_serial->setPortName("/dev/ttyACM0");
    m_serial->setBaudRate(115200);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);
    if (m_serial->open(QIODevice::ReadWrite)) {
        // open success
        qDebug() << "connected";
        opened = true;
    } else {
        // open fail
        qDebug() << "failed";
        opened = false;
    }
}

void CommandController::closeSerialPort()
{
    if (m_serial->isOpen())
        m_serial->close();
}

void CommandController::writeData(const QByteArray &data)
{
    m_serial->write(data);
}

void CommandController::readData()
{
    result = m_serial->readAll();
}

void CommandController::handleError(QSerialPort::SerialPortError error)
{

}
