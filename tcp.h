#ifndef TCP_H
#define TCP_H

#include <QObject>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QTimer>
#include <QTime>
#include <QCoreApplication>


//#include <QLoggingCategory>
#include <QFileInfo>
#include <QNetworkAccessManager>

#define SHFT 0 // for analog mode
#define X102 // new version txt
#define DBG
#define DBG_BA
#define PING
#define NANOPI
#define TWO_STATIONS
//#define DBG_TO_FILE

#define TS_DELTA 160
#define MU_LAW
#define RTP
#define RTP_HDR_LEN 12
#define HYTRA


class TCP : public QObject
{
    Q_OBJECT
public:
   // QTimer timer;
    explicit TCP(QObject *parent = nullptr  );
    bool ready_if_file();
    void fill_if_file();
    int defOnegaType();
signals:
    
public slots:
    void timer_slot();
};



#endif // TCP_H
