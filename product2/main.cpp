#include <iostream>
#include "HttpClient.h"

void checkSubscription(const std::string& username, const std::string& password) {
    HttpClient client;
    client.setUrl("http://127.0.0.1:8001/sub-licensing/check/");

    std::string request = R"("{\"username\":\"")" + username + R"("\",\"password\":\")" + password + R"("\"})";
    client.setRequest(request);

    client.post();

    if (client.getResponse().getData().find("true") != std::string::npos) {
        std::cout << "Valid subscription" << std::endl;
        system("cd ../../application && dragdroprobot.exe");
    } else {
        if (client.getResponse().getData().find("expired") != std::string::npos) {
            std::cout << "Subscription expired" << std::endl;
            std::cout << "renew in: http://127.0.0.1:8001/sub-licensing/subscriptions/" << std::endl;
        } else if (client.getResponse().getData().find("no subscription") != std::string::npos) {
            std::cout << "No subscription" << std::endl;
            std::cout << "get a plan in: http://127.0.0.1:8001/sub-licensing/subscriptions/" << std::endl;
        } else {
            std::cout << client.getResponse().getData() << std::endl;
            std::cout << "renew in: http://127.0.0.1:8001/auth/users/" << std::endl;
        }
    }
}

int main() {
    std::string username;
    std::string password;

    std::cout << "Enter username:\n";
    std::cin >> username;

    std::cout << "Enter password:\n";
    std::cin >> password;

    checkSubscription(username, password);

    return 0;
}
