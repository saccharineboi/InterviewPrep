#include <string>
#include <iostream>
#include <vector>

////////////////////////////////////////
bool checkPerm(const std::string& a, const std::string& b)
{
    if (a.size() != b.size()) {
        return false;
    }
    // assume that the character set has 256 characters
    std::vector<int> charCounts(256);
    for (char c : a) {
        ++charCounts[c];
    }
    for (char c : b) {
        --charCounts[c];
        if (charCounts[c] < 0) {
            return false;
        }
    }
    return true;
}

////////////////////////////////////////
int main(int argc, char** argv)
{
    if (argc > 2) {
        std::string a{ argv[1] };
        std::string b{ argv[2] };
        std::cout << a << (checkPerm(a, b) ? " is " : " is NOT ") << "a permutation of " << b << '\n';
    }
    else {
        std::cout << "Usage: " << argv[0] << " <string> <string>\n";
    }
}
