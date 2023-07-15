#include <iostream>
#include "Response.h"

#ifndef PRODUCT1_HTTPCLIENT_H
#define PRODUCT1_HTTPCLIENT_H


class HttpClient {
private:
    std::string url;
    std::string request;
    Response response;

public:
    HttpClient();

    void setUrl(std::string inUrl);
    void setRequest(std::string inRequest);

    std::string getUrl() const;
    std::string getRequest() const;
    Response getResponse() const;

    void post();
    std::string sendRequest(std::string method);


};


#endif //PRODUCT1_HTTPCLIENT_H
