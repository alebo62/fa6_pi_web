#include "tcp.h"
#include "variables.h"

// Вначале , проверяем, существует ли файл с Settings
// Если нет , то создаем его и заполняем по умолчанию
// Запускаем команду ifconfig и смотрим какой интерфейс подключен

TCP::TCP(QObject *parent) :
    QObject(parent)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(timer_slot()));
    timer.start(waitTime);

    onegaType = defOnegaType();

    if(!QDir("/home/pi/Settings").exists())
    {
        settings.setValue("/Settings/fa_login", "admin");
        settings.setValue("/Settings/fa_psw", "1234");
        settings.setValue("/Settings/server_adress","192.168.0.180");
        settings.setValue("/Settings/onega_adress","192.168.100.100");
        settings.setValue("/Settings/gw_adress","");
        settings.setValue("/Settings/radio_id","65280");
        settings.setValue("/Settings/channel_id","1");
        settings.setValue("/Settings/group_id","1");
    }
    //qDebug() << settings.value("/Settings/fa_login").toString();

    if(onegaType == NANO)
    {
        if(!ready_if_file())
            fill_if_file();
    }

    proc.start("ifconfig");
    proc.waitForFinished();
    sl = ((QString)proc.readAllStandardOutput()).split('\n');
    if(sl[0].contains("enx"))
        radio_if = sl[0].mid(0, 15);
    else if (sl[0].contains("usb0"))
        radio_if = "usb0";

    //qDebug() << radio_if;

}

// Определяем тип Онеги : (распберри или нанопай)
int TCP::defOnegaType()
{
    proc.start("cat /proc/cpuinfo");
    proc.waitForFinished();
    sl = ((QString)proc.readAllStandardOutput()).split('\n');

    //qDebug() << sl[sl.size() - 2];

    if(sl[sl.size() - 2].contains("Model"))
        return RASP;
    if (sl[sl.size() - 2].contains("Serial"))
        return NANO;
}

// Заполнен ли уже файл сет. интерфейсов /etc/network/interfaces
bool TCP::ready_if_file()
{
    QStringList sl;
    QFile file("/etc/network/interfaces");
    file.open(QFile::ReadOnly);
    while (!file.atEnd())
    {
        sl << file.readLine();
    }
    file.close();
    if(sl.size() <= 3)
        return false;
    else
        return true;
}

// Заполняем файл /etc/network/interfaces по умолчанию
void TCP::fill_if_file()
{
    QStringList sl;
    QFile file("/etc/network/interfaces");
    file.open(QFile::WriteOnly);

    sl.append("auto lo\n");  //0
    sl.append("iface lo inet loopback\n");
    sl.append("\n");
    sl.append("#auto eth0\n");
    sl.append("#iface eth0 inet static\n"); // static WAN  4
    sl.append("#address 192.168.100.100\n");
    sl.append("#netmask 255.255.255.0\n");
    sl.append("#gateway 192.168.100.1\n");
    sl.append("\n");
    sl.append("#auto enx7cc2c6144fc1\n");  //  usb-ETH adapter(for repeater)  9
    sl.append("#allow-hotplug enx7cc2c6144fc1\n");
    sl.append("#iface enx7cc2c6144fc1 inet static\n");
    sl.append("#address 192.168.10.2\n");
    sl.append("#netmask 255.255.255.0\n");
    sl.append("#gateway 192.168.10.254\n");
    sl.append("\n");
    sl.append("#auto usb0\n");  //  for radio if usb0 interface  16
    sl.append("#allow-hotplug usb0\n");
    sl.append("#iface usb0 inet dhcp\n");
    sl.append("#address 192.168.10.2\n");
    sl.append("#netmask 255.255.255.0\n");
    sl.append("#gateway 192.168.10.1\n");
    sl.append("\n");
    sl.append("auto enx00000a00ff01\n");  // for radio if enx... interface   23
    sl.append("allow-hotplug enx00000a00ff01\n");
    sl.append("iface enx00000a00ff01 inet dhcp\n");
    sl.append("address 192.168.10.2\n");
    sl.append("netmask 255.255.255.0\n");
    sl.append("#gateway 192.168.10.1\n");
    QTextStream stream(&file);
    foreach(QString s, sl)
    {
        //qDebug() << s;
        stream << s;
    }
    file.close();
}

//  Конец работы сервера если никто не подключился за 30 сек
void TCP::timer_slot()
{
    qDebug() << "timer slot";
    QCoreApplication::quit();
    //exit(0);
}









