#include <iostream>
#include <cstring>
#include <cctype>

////////////////////////////////////////
char* urlify(char* str, int length)
{
    if (!length) {
        return str;
    }
    int readInd{ length - 1 };
    int writeInd{ length - 1 };
    while (readInd >= 0 && std::isspace(str[readInd])) {
        --readInd;
    }
    int spaceCnt{};
    while (readInd >= 0 && writeInd >= 0) {
        if (std::isspace(str[readInd])) {
            ++spaceCnt;
        }
        else {
            while (spaceCnt > 0) {
                str[writeInd--] = '0';
                str[writeInd--] = '2';
                str[writeInd--] = '%';
                --spaceCnt;
            }
            str[writeInd--] = str[readInd];
        }
        --readInd;
    }
    ++readInd;
    ++writeInd;
    std::swap(readInd, writeInd);
    while (readInd < length && writeInd < length) {
        str[writeInd++] = str[readInd++];
    }
    str[writeInd] = '\0';
    return str;
}

////////////////////////////////////////
int main(int argc, char** argv)
{
    if (argc > 1) {
        std::cout << "You entered: '" << argv[1] << "'\n";
        std::cout << "URLified: '" << urlify(argv[1], std::strlen(argv[1])) << "'\n";
    }
    else {
        std::cout << "Usage: " << argv[0] << " <string>\n";
    }
}
