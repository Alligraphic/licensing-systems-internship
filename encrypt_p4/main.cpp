#include <iostream>
#include <fstream>

void copyFile(std::string src, std::string dest) {
    std::ifstream srcFile(src, std::ios::binary);
    std::ofstream destFile(dest, std::ios::binary);

    destFile << srcFile.rdbuf();

    srcFile.close();
    destFile.close();
}

void enc_or_dec(std::string const from, std::string const to, std::string const key) {
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


int main() {
    std::string key = "Uk3Ph2Vk5Co3Qv6Fc8Hd4Ux0Zm6Qi2Pu"; //32 chars *user15*

    enc_or_dec("../user15.exe", "../user15.enf", key);

    return 0;
}
