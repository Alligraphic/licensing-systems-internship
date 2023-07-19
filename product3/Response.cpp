//
// Created by user on 7/15/2023.
//

#include "Response.h"

#include <utility>

Response::Response() {
    this->data = "empty!";
    this->statusCode = 0;
};


void Response::setData(std::string inData) {
    this->data = std::move(inData);
};

void Response::setHeader(std::string inHeader) {
    this->header = std::move(inHeader);
};

void Response::setStatusCode(int inStatusCode) {
    this->statusCode = inStatusCode;
};


std::string Response::getData() const {
    return this->data;
}

std::string Response::getHeader() const {
    return this->header;
};

int Response::getStatusCode() const {
    return this->statusCode;
}

void Response::parseResponse(std::string response) {
    std::string delimiter = "\n\n";
    size_t pos = response.find(delimiter);
    std::string token;
    token = response.substr(0, pos);
    this->header = token;

    response.erase(0, pos + delimiter.length());

    this->statusCode = std::stoi(this->header.substr(9, 3));

    this->data = response;
};
