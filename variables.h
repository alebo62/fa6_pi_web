#include <QSettings>
#include <QNetworkInterface>
#include <QProcess>
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QTimer>

extern QTimer timer;

enum {NANO, RASP};
const quint32 waitTime = 10000;
QSettings settings("/home/pi/Settings/NWCSC/FerrAgentpi.conf", QSettings::NativeFormat);

QProcess proc;
QStringList sl;
QString radio_if;
int onegaType;
