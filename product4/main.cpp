#include <iostream>
#include <fstream>
#include "HttpClient.h"

void deleteFile(const std::string& path) {
    std::remove(path.c_str());
}

void copyFile(const std::string& src, const std::string& dest) {
    std::ifstream srcFile(src, std::ios::binary);
    std::ofstream destFile(dest, std::ios::binary);

    destFile << srcFile.rdbuf();

    srcFile.close();
    destFile.close();
}

void enc_or_dec(const std::string& from, const std::string& to, const std::string& key) {
    // open the file in read mode
    FILE *fp = fopen(from.c_str(), "r");

    // read the first 32 bytes of the file
    char buf[33];
    fread(buf, 1, 32, fp);
    fclose(fp);

    buf[32] = '\0';

    // xor the key with the first 32 bytes of the file
    for (int i = 0; i < 32; i++) {
        buf[i] ^= char(key[i]);
    }

    // copy the file to the destination
    copyFile(from, to);

    // replace the first 32 bytes of the destination with the xor'd bytes
    std::ofstream destFile(to, std::ios::binary | std::ios::in);
    destFile.seekp(0);
    destFile.write(buf, 32);
    destFile.close();
}

// extract the key from the jason string
std::string extract_key(const std::string& json) {
    std::string key;
    int i = json.find("key") + 6;
    while (json[i] != '"') {
        key += json[i];
        i++;
    }
    return key;
}

void use_key(const std::string& username, const std::string& password) {
    HttpClient client;
    client.setUrl("http://127.0.0.1:8001/key/get_key/");

    std::string request = R"("{\"username\":\"")" + username + R"("\",\"password\":\")" + password + R"("\"})";
    client.setRequest(request);

    client.post();

    if (client.getResponse().getData().find("true") != std::string::npos) {
        std::cout << "Valid Key" << std::endl;
        std::string key = extract_key(client.getResponse().getData());

        enc_or_dec("../" + username + ".enf", "../" + username + ".exe", key);

        std::string path = "../../application/" + username + ".exe";
        copyFile("../" + username + ".exe", path);
        deleteFile("../" + username + ".exe");

        system(("cd ../../application && " + username + ".exe").c_str());

        deleteFile(path);
    } else {
        if (client.getResponse().getData().find("false") != std::string::npos) {
            std::cout << "Invalid Key" << std::endl;
        } else {
            std::cout << client.getResponse().getData() << std::endl;
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

    use_key(username, password);

    return 0;
}
