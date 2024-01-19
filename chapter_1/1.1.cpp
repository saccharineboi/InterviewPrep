#include <string>
#include <iostream>
#include <unordered_set>
#include <algorithm>

////////////////////////////////////////
bool isUniqueWithDS(const std::string& str)
{
    // Time: O(N)
    // Space: O(N)
    std::unordered_set<char> chars;
    for (char c : str)
        chars.insert(c);
    return str.size() == chars.size();
}

////////////////////////////////////////
bool isUniqueWithoutDS(const std::string& str)
{
    // Time O(N * log N)
    // Space: O(N), can be turned into O(1) if sorting is done in-place
    std::string cpy{ str };
    std::sort(cpy.begin(), cpy.end());
    for (std::size_t i = 1; i < str.size(); ++i)
        if (str[i] == str[i - 1])
            return false;
    return true;
}

////////////////////////////////////////
int main(int argc, char** argv)
{
    if (argc > 1) {
        std::string str(argv[1]);
        std::cout << "You entered: " << str << '\n';
        std::cout << "Is Unique (With DS): " << isUniqueWithDS(str) << '\n';
        std::cout << "Is Unique (Without DS): " << isUniqueWithoutDS(str) << '\n';
    }
    else {
        std::cout << "Usage: " << argv[0] << " <string>\n";
    }
}
