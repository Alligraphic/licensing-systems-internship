#include <iostream>
#include <fstream>

int mod_by_26(std::string large_num){
    int result = 0;
    for (int i = 0 ; i < large_num.length() ; i++){
        result = (result * 10 + (large_num[i] - '0')) % 26;
    }
    return result;
}

int mod_by_10(std::string large_num){
    int len = large_num.length();
    int result = large_num[len - 1] - '0';
    return result;
}

std::string divide_by_2(std::string large_num) {
    std::string result = "";
    int carry = 0;
    for (int i = 0; i < large_num.length(); i++) {
        int currentDigit = (large_num[i] - '0') + carry * 10;
        result += (currentDigit / 2) + '0';
        carry = currentDigit % 2;
    }
    if (result[0] == '0' && result.length() > 1) {
        result.erase(0, 1);
    }
    return result;
}

std::string key_gen(std::string seed){
    std::string lower_alpha = "abcdefghijklmnopqrstuvwxyz";
    std::string upper_alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string numbers = "0123456789";

    char key[33];
    for (int i = 0 ; i < 32 ; i++){
        if (i % 3 == 0){
            key[i] = upper_alpha[mod_by_26(seed)];
        }
        else if (i % 3 == 1){
            key[i] = lower_alpha[mod_by_26(seed)];
        }
        else{
            key[i] = numbers[mod_by_10(seed)];
        }
        seed = divide_by_2(seed);
    }
    key[32] = '\0';

    return key;
}

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

bool validateFile(std::string address){
    // check if the files firs 2 characters are "MZ"
    std::ifstream file(address, std::ios::binary);
    char buf[2];
    file.read(buf, 2);
    file.close();
    return buf[0] == 'M' && buf[1] == 'Z';
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

void use_key(const std::string& key) {
        enc_or_dec("../offline.enf", "../offline.exe", key);

        std::string path = "../../application/offline.exe";
        copyFile("../offline.exe", path);
        deleteFile("../offline.exe");

        if (validateFile(path))
            system("cd ../../application && offline.exe");
        else {
            std::cout << "Invalid Key" << std::endl;
        }

        deleteFile(path);
}

int main() {
    std::string seed;
    std::cout << "Enter seed:\n";
    std::cin >> seed;

    std::string key = key_gen(seed);
    use_key(key);

    return 0;
}
