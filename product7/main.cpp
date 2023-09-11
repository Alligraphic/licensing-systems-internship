#include <iostream>

std::string run_cmd(std::string cmd)
{
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

std::string get_device_list()
{
    std::string list = run_cmd("pnputil /enum-devices /connected /class USB");
    return list;
}

int main() {
    std::string result = get_device_list();

    if (result.find("04Z3EF2214RUND6A") != std::string::npos)
    {
        system("cd ../../application && dragdroprobot.exe");
    } else{
        std::cout << "please insert the USB drive" << std::endl;
    }
    return 0;
}
