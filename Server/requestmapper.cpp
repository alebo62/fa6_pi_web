#include "requestmapper.h"
#include "helloworldcontroller.h"
#include "listdatacontroller.h"
#include "logincontroller.h"
#include <QSettings>



extern bool pass_ok;
RequestMapper::RequestMapper(QObject* parent)
    : HttpRequestHandler(parent) {
    // empty
}

void RequestMapper::service(HttpRequest& request, HttpResponse& response) {
    QByteArray path=request.getPath();
    //qDebug("RequestMapper: path=%s",path.data());



    if (path=="/" ){//|| path=="/hello") {
        loginController.service(request, response);
        //helloWorldController.service(request, response);
    }
    else if (path=="/list") {
        listDataController.service(request, response);

    }
    else if (path=="/login") {
 //           loginController.service(request, response);
//            if(pass_ok)
//                 listDataController.service(request, response);

        }
    else {
        response.setStatus(404,"Not found");
        response.write("The URL is wrong, no such document.",true);
    }


   // qDebug("RequestMapper: finished request");
}
