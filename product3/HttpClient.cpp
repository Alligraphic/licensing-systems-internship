//
// Created by user on 7/15/2023.
//

#include "HttpClient.h"

HttpClient::HttpClient() {
    this->url = "";
    this->request = "";
}

void HttpClient::setUrl(std::string inUrl) {
    this->url = inUrl;
}

void HttpClient::setRequest(std::string inRequest) {
    this->request = inRequest;
}

std::string HttpClient::getUrl() const {
    return this->url;
}

std::string HttpClient::getRequest() const {
    return this->request;
}

void HttpClient::post() {
    this->response.parseResponse(this->sendRequest("POST"));
}

std::string HttpClient::sendRequest(std::string method) {
    std::string cmd = "curl -sid " + this->request + " -H \"Content-Type: application/json\""
            + " -X " + method + " " + this->url;

    FILE *fp = popen(cmd.c_str(), "r");
    if (fp == NULL) {
        std::cout << "Failed to run curl command" << std::endl;
        exit(1);
    }

    char buffer[1024];
    std::string result = "";
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        result += buffer;
    }
    pclose(fp);
    return result;
}

Response HttpClient::getResponse() const {
    return this->response;
}
