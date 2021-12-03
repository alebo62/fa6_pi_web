#include <QTime>
#include <QRegExp>
#include "listdatacontroller.h"
#include "QProcess"
#include "QHostAddress"
#include <QThread>
extern QSettings settings;
extern QString login;
extern QString psw;
void write_net_conf_rasp();
extern void write_net_conf_nano();
class Sleeper : public QThread
{
public:
    static void usleep(unsigned long usecs){QThread::usleep(usecs);}
    static void msleep(unsigned long msecs){QThread::msleep(msecs);}
    static void sleep(unsigned long secs){QThread::sleep(secs);}
};

QString ip_adress_s;
QString ip_adress_o;
QString ip_adress_g;
QString id_adress_h;
QString id_channel;
QString id_group;

quint32 adr;
QProcess prc;
void changeOnegaIp(QStringList & strList);
void changeUbEthIp(QStringList & strList);
void changeH3_OnegaIp(QStringList & strList);

ListDataController::ListDataController(QObject* parent)
    : HttpRequestHandler(parent) {
}

void ListDataController::service(HttpRequest &request, HttpResponse &response)
{
    ip_adress_s=request.getParameter("ip_adress_s");// server
    ip_adress_o = request.getParameter("ip_adress_o");// onega
    ip_adress_g = request.getParameter("ip_adress_g");// gateway
    id_adress_h = request.getParameter("id_adress_h");// radio id
    id_channel  = request.getParameter("chan_num");   // channel id

    QString old_login = request.getParameter("old_login");
    QString new_login = request.getParameter("new_login");
    QString old_psw = request.getParameter("old_psw");
    QString new_psw = request.getParameter("new_psw");
    QString reload = request.getParameter("reload");

    QRegExp rx( "[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}" );
    bool pass = true;
    // Проверяем адрес сервера
    if(ip_adress_s.contains(rx) == true )
    {
        settings.setValue("/Settings/server_adress", ip_adress_s);
    }
    //    else if(ip_adress_s == "")
    //    {

    //    }
    else
    {
        pass = false;
    }

    // Проверяем адрес Онеги
    if(ip_adress_o.contains(rx) == true )
    {
        settings.setValue("/Settings/onega_adress", ip_adress_o);
    }
    else if(ip_adress_o == "")
    {
        settings.setValue("/Settings/onega_adress", "");
    }
    else
    {
        pass = false;
    }
    // Проверяем адрес шлюза
    if(ip_adress_g.contains(rx) == true )
    {
        settings.setValue("/Settings/gw_adress", ip_adress_g);
    }
    else if(ip_adress_g == "")
    {
        settings.setValue("/Settings/gw_adress", "");
    }
    else
    {
        pass = false;
    }

    // Проверяем номер радио
    if(id_adress_h.toUInt() > 0 && id_adress_h.toUInt() < 0xFFFFFF )
    {
        settings.setValue("/Settings/radio_id", id_adress_h);
    }
    else if(ip_adress_g == "")
    {
        settings.setValue("/Settings/radio_id", "");
    }
    else
    {
        pass = false;
    }
    // Проверяем номер канала
    if(id_channel.toUInt() > 0 && id_channel.toUInt() < 100 )
    {
        settings.setValue("/Settings/channel_id", id_channel);
    }
    else if(ip_adress_g == "")
    {

    }
    else
    {
        pass = false;
    }
    // Проверяем номер группы
    if(id_group.toUInt() > 0 && id_group.toUInt() < 0xFFFFFF )
    {
        settings.setValue("/Settings/group_id", id_group);
    }
    else if(id_group == "")
    {

    }
    else
    {
        pass = false;
    }



    if(old_login == login)
    {
        settings.setValue("/Settings/fa_login", new_login);
        login = new_login;
    }
    if(old_psw == psw)
    {
        settings.setValue("/Settings/fa_psw", new_psw);
        psw = new_psw;
    }


    if((reload  == "on"))
    {
        write_net_conf_rasp();
        Sleeper::sleep(1);
        response.setHeader("Content-Type", "text/html; charset=UTF-8");
        response.write("<html><body>");
        response.write(" Перезагрузка <br>");
        response.write("</body></html>",true);
        prc.start("sudo reboot");
        exit(1);
    }

    if(pass == false)
    {
        response.setHeader("Content-Type", "text/html; charset=UTF-8");
        response.write("<html><body>");
        response.write("<form method='POST' action='/list'>");
        response.write("IP адрес  Сервера: <input type='text' name='ip_adress_s'><br>");
        response.write("IP адрес  Онега-У: <input type='text' name='ip_adress_o' ='192'>(если пусто- DHCP)<br>");
        response.write("IP адрес    Шлюза:  <input type='text' name='ip_adress_g'><br>");
        response.write("ID номер  Радиост:  <input type='text' name='id_adress_h'>(по умолч. 65280)<br>");
        response.write("    Номер  канала:  <input type='text' name='chan_num'>(для репитеров)<br>");
        response.write("    Номер  группы:  <input type='text' name='group_num'>(для аналога)<br>");
        response.write("<br>");
        response.write("Старый логин :  <input type='text' name='old_login'><br>");
        response.write(" Новый логин :  <input type='text' name='new_login'><br>");
        response.write("<br>");
        response.write("Старый пароль :  <input type='text' name='old_psw'><br>");
        response.write(" Новый пароль :  <input type='text' name='new_psw'><br>");
        response.write("<br>");
        response.write("Перезагрузить Онега-У:  <input type='checkbox' name='reload'><br>");
        response.write("<input type='submit'>");
        response.write("</form");
        response.write("</body></html>",true);
    }
    else
    {
        Sleeper::sleep(1);
        response.setHeader("Content-Type", "text/html; charset=UTF-8");
        response.write("<html><body>");
        response.write(" Перезагрузка <br>");
        response.write("</body></html>",true);
        prc.start("sudo reboot");
    }
}




