#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <iostream>
#include "tcp.h"

#include "httplistener.h"
#include "httprequesthandler.h"
#include "Server/helloworldcontroller.h"
#include "Server/listdatacontroller.h"
#include "Server/requestmapper.h"
#include <QProcess>

#ifdef DBG_TO_FILE
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#include <QLoggingCategory>
void messageHandler(QtMsgType type,    const QMessageLogContext &, const QString &msg);
#else
void messageHandler(QtMsgType type,    const char *msg);
#endif
#endif

QScopedPointer<QFile>   m_logFile;
QString binDir=QCoreApplication::applicationDirPath();
QString appName="fa6_pi";//QCoreApplication::applicationName();
QFile file;
QFileInfo file_info(file);
QTimer timer;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString binDir=QCoreApplication::applicationDirPath();
    file.setFileName("/home/pi/etc/webapp1.ini");
    QString configFileName = QDir(file.fileName()).canonicalPath();
    QSettings* listenerSettings = new QSettings(configFileName, QSettings::IniFormat, &a);
    listenerSettings->beginGroup("listener");
    new HttpListener(listenerSettings, new RequestMapper(&a), &a);

    TCP kupol;
    return a.exec();
}


