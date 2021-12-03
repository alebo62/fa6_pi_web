#include "requestmapper.h"
#include "logincontroller.h"
#include "listdatacontroller.h"
#include <QDebug>
#include <QThread>
#include <QTimer>
extern QTimer timer;

class Sleeper : public QThread
{
public:
    static void usleep(unsigned long usecs){QThread::usleep(usecs);}
    static void msleep(unsigned long msecs){QThread::msleep(msecs);}
    static void sleep(unsigned long secs){QThread::sleep(secs);}
};
extern QSettings settings;

QString login;
QString psw;

bool pass_ok = false;
using namespace stefanfrings;
extern ListDataController listDataController;


LoginController::LoginController(QObject* parent):HttpRequestHandler(parent)
{
    // empty
}

void LoginController::service(HttpRequest &request, HttpResponse &response) {
    QString username=request.getParameter("username");
    QString password=request.getParameter("password");

    //qDebug("username=%s",username.constData());
    //qDebug("password=%s",password.constData());

    login = settings.value("/Settings/fa_login").toString();
    psw = settings.value("/Settings/fa_psw").toString();
    Sleeper::msleep(1000);
    qDebug() << "login" << login << " " << psw;

    response.setHeader("Content-Type", "text/html; charset=UTF-8");
    response.write("<html><body>");

    if ((username == login) and (password == psw))
    {
        timer.stop();
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
        pass_ok = true;
    }
    else
    {
        pass_ok = false;
        response.write("<form method='POST' action='/'>");
        if (!username.isEmpty()) {
            response.write("No, that was wrong!<br><br>");
        }
        response.write("Please log in:<br>");
        response.write("Login:  <input type='text' name='username'><br>");
        response.write("Password: <input type='password' name='password'><br>");
        response.write("<input type='submit'>");
        response.write("</form");
    }

    response.write("</body></html>",true);
}
