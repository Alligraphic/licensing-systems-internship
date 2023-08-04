#include <iostream>

class date {
public:
    int day, month, year;

    void print_date() {
        std::cout << day << "." << month << "." << year << "\n";
    }

    bool operator==(const date& other) {
        return day == other.day && month == other.month && year == other.year;
    }

    bool operator!=(const date& other) {
        return !(*this == other);
    }

    bool operator<(const date& other) {
        if (year < other.year) {
            return true;
        }
        else if (year == other.year) {
            if (month < other.month) {
                return true;
            }
            else if (month == other.month) {
                if (day < other.day) {
                    return true;
                }
            }
        }
        return false;
    }

    bool operator>(const date& other) {
        return !(*this < other || *this == other);
    }

    bool operator<=(const date& other) {
        return *this < other || *this == other;
    }

    bool operator>=(const date& other) {
        return *this > other || *this == other;
    }
};


char* xor_string(std::string str, const char* key) {
    int str_len = str.length();
    char* result = new char[str_len + 1];
    for (int i = 0; i < str_len; i++) {
        result[i] = str[i] ^ key[i];
    }
    result[str_len] = '\0';
    return result;
}

int main() {
    char key2[32];
    for (int i = 0; i < 32; i++) {
        key2[i] = (i % 2) + 1;
    }

    std::string str;
    std::cout << "Enter string:\n";
    std::getline(std::cin, str);

    char* result = xor_string(str, key2);
    std::string result_str(result);

    // the last 8 characters of the result are the date
    date exp;
    exp.year = std::stoi(result_str.substr(result_str.length() - 2, 2));
    exp.month = std::stoi(result_str.substr(result_str.length() - 5, 2));
    exp.day = std::stoi(result_str.substr(result_str.length() - 8, 2));

    exp.print_date();

    // get today date
    time_t now = time(0);
    tm* ltm = localtime(&now);

    date today;
    today.year = ltm->tm_year - 100;
    today.month = 1 + ltm->tm_mon;
    today.day = ltm->tm_mday;

    if (exp < today) {
        std::cout << "Expired\n";
    }
    else {
        system("cd ../../application/ && dragdroprobot.exe");
    }

    return 0;
}
