#include <iostream>
#include "HttpClient.h"

int main() {
    HttpClient client;
    client.setUrl("http://localhost:8001/licensing/check/");

    std::string serial_number;
    std::cin >> serial_number;

    client.setRequest("{\\\"serial_number\\\":" + serial_number + "}");
    client.post();

    if (client.getResponse().getStatusCode() == 200) {
        system("cd .. && dragdroprobot.exe");
    } else {
        std::cout << "Invalid serial number" << std::endl;
    }


    return 0;
}
