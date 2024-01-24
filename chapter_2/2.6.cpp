#include <list>
#include <iostream>
#include <cstring>

////////////////////////////////////////
bool isPalindrome(const std::list<char>& lst)
{
    auto begin{ lst.begin() };
    auto end{ lst.end() };
    std::size_t lstSize{ lst.size() };

    --end;
    while (lstSize / 2) {
        if (*begin != *end) {
            return false;
        }
        --lstSize;
    }
    return true;
}

////////////////////////////////////////
int main(int argc, char** argv)
{
    if (argc > 1) {
        std::list<char> lst;
        std::size_t len{ std::strlen(argv[1]) };
        for (std::size_t i{}; i < len; ++i) {
            lst.push_front(argv[1][i]);
        }
        std::cout << "Is palindrome: " << isPalindrome(lst) << '\n';
    }
    else {
        std::cout << "Usage: " << argv[0] << " <string>\n";
    }
}
