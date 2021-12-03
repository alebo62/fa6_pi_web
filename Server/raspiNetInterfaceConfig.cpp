#include <QFile>
#include <QStringList>
#include <QDebug>

extern QString ip_adress_o;
extern QString ip_adress_g;

void write_net_conf_rasp()
{
    char ch;
    QFile file("/etc/dhcpcd.conf");
    QStringList strList;
    /*Считываем исходный файл в контейнер*/
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

    if(strList.size() >= 44)
    {
        if(strList[40].contains("interface eth0"))
        {
            if(strList[40].at(0) == '#' && ip_adress_o !=  "")
            {
                strList[40].remove(0,1);
            }
            else if(strList[40].at(0) != '#' && ip_adress_o ==  "")
            {
                strList[40].insert(0,'#');
            }
        }

        if(strList[41].contains("static ip_address"))
        {
            if(strList[41].at(0) == '#' && ip_adress_o !=  "")
            {
                strList[41].remove(0,1);
                int i = strList[40].indexOf('=');
                strList[41].remove(i + 1, strList[41].length() - i - 2);
                strList[41].insert(i + 1, ip_adress_o);
                //add ip
            }
            else if(strList[41].at(0) != '#' && ip_adress_o ==  "")
            {
                strList[41].insert(0,'#');
            }
        }

        if(strList[43].contains("static routers"))
        {
            if(strList[43].at(0) == '#' && ip_adress_o !=  "" && ip_adress_g !=  "")
            {
                strList[43].remove(0,1);
                int i = strList[40].indexOf('=');
                strList[43].remove(i + 1, strList[43].length() - i - 2);
                strList[43].insert(i + 1, ip_adress_o);
            }
            else if(strList[43].at(0) != '#' && ip_adress_o ==  "")
            {
                strList[43].insert(0,'#');
            }
        }
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
