#include <string>
#include <iostream>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////////////////////
bool isUnique(const std::string& s)
{
    // assume that there are 256 characters in the character set
    std::vector<bool> chars(256);
    for (char c : s) {
        if (chars[c]) {
            return false;
        }
        chars[c] = true;
    }
    return true;
}

////////////////////////////////////////
int main(int argc, char** argv)
{
    if (argc > 1) {
        std::cout << "You entered: " << argv[1] << '\n';
        std::cout << "Is Unique: " << isUnique(argv[1]) << '\n';
    }
    else {
        std::cout << "Usage: " << argv[0] << " <string>\n";
    }
}
