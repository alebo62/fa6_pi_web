#ifndef REQUESTMAPPER_H
#define REQUESTMAPPER_H


#include "httprequesthandler.h"
#include "helloworldcontroller.h"
#include "listdatacontroller.h"
#include "logincontroller.h"

using namespace stefanfrings;

class RequestMapper : public HttpRequestHandler {
    Q_OBJECT
public:
    RequestMapper(QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);
public:
    HelloWorldController helloWorldController;
    ListDataController listDataController;
    LoginController loginController;
};

#endif // REQUESTMAPPER_H
