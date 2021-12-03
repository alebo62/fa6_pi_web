#include <QString>
#include <QStringList>
extern QString ip_adress_o;
extern QString ip_adress_g;

void changeOnegaIp(QStringList & strList)
{
    if(strList[4].contains("auto eth0"))
    {
        if(strList[4].at(0) == '#' && ip_adress_o !=  "")
        {
            strList[4].remove(0,1);
        }
        else if(strList[4].at(0) != '#' && ip_adress_o ==  "")
        {
            strList[4].insert(0,'#');
        }

        if(strList[5].at(0) == '#' && ip_adress_o !=  "")
        {
            strList[5].remove(0,1);
        }
        else if(strList[5].at(0) != '#' && ip_adress_o ==  "")
        {
            strList[5].insert(0,'#');
        }

        if(strList[7].at(0) == '#' && ip_adress_o !=  "")
        {
            strList[7].remove(0,1);
        }
        else if(strList[7].at(0) != '#' && ip_adress_o ==  "")
        {
            strList[7].insert(0,'#');
        }
    }

    if(strList[6].contains("address"))
    {
        if(strList[6].at(0) == '#' && ip_adress_o !=  "")
        {
            strList[6].remove(0,1);
            int i = strList[6].indexOf(' ');
            strList[6].remove(i + 1, strList[6].length() - i - 2);
            strList[6].insert(i + 1, ip_adress_o);
            //add ip
        }
        else if(strList[6].at(0) != '#' && ip_adress_o ==  "")
        {
            strList[6].insert(0,'#');
        }
    }

    if(strList[8].contains("gateway"))
    {
        if(strList[8].at(0) == '#' && ip_adress_o !=  "" && ip_adress_g !=  "")
        {
            strList[8].remove(0,1);
            int i = strList[8].indexOf(' ');
            strList[8].remove(i + 1, strList[8].length() - i - 2);
            strList[8].insert(i + 1, ip_adress_o);
        }
        else if(strList[8].at(0) != '#' && ip_adress_o ==  "")
        {
            strList[8].insert(0,'#');
        }
    }
}
