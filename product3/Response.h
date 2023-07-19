#include <iostream>

#ifndef PRODUCT1_RESPONSE_H
#define PRODUCT1_RESPONSE_H


class Response {
private:
    std::string data;
    std::string header;
    int statusCode{};

public:
    Response();

    void setData(std::string inData);
    void setHeader(std::string inHeader);
    void setStatusCode(int inStatusCode);

    std::string getData() const;
    std::string getHeader() const;
    int getStatusCode() const;

    void parseResponse(std::string response);
};


#endif //PRODUCT1_RESPONSE_H
