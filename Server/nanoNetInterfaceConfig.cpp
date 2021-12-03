#include <QFile>
#include <QStringList>
#include <QDebug>

/*

#iface eth0 inet static
#address
#netmask 255.255.255.0
#gateway
#dns-nameservers 8.8.8.8
#auto eth0

*/
extern void changeOnegaIp(QStringList &);

void write_net_conf_nano()
{
    char ch;
    QFile file("/etc/network/interfaces");
    QStringList strList;
    /*Считываем исходный файл в контейнер*/changeOnegaIp(strList);
    if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
    {
        while(!file.atEnd())
        {
            strList << file.readLine();
        }
        file.close();
    }
    else
        qDebug() << "err1";

    file.close();

    if(strList.size() >= 4)
    {
        changeOnegaIp(strList);
        //changeUsbEthIp(strList);
    }
    else
        qDebug() << strList.size();

    /*сохраняем содержимое контейнера в тот же файл*/
    if ((file.exists())&&(file.open(QIODevice::WriteOnly)))
    {
        QTextStream stream(&file);
        foreach(QString s, strList)
        {
            //qDebug() << s;
            stream << s;
        }
    }
    else
        qDebug() << "err2";
    file.close();
}
