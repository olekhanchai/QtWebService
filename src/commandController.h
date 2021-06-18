#ifndef COMMANDCONTROLLER_H
#define COMMANDCONTROLLER_H

#include "httprequesthandler.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

using namespace stefanfrings;

class CommandController : public HttpRequestHandler {
    Q_OBJECT
public:
    CommandController(QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);

    void openSerialPort();
    void closeSerialPort();
    static void writeData(const QByteArray &data);
    static void readData();
    static void handleError(QSerialPort::SerialPortError error);
    static QSerialPort *m_serial;
    static bool opened;
    static QString result;
};

#endif // COMMANDCONTROLLER_H
