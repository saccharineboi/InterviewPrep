#include <string>
#include <iostream>
#include <unordered_map>
#include <cctype>

////////////////////////////////////////
bool isPermOfPalindrome(const std::string& str)
{
    // Time: O(n)
    // Space: O(n)
    std::string cpy{ str };
    std::unordered_map<char, int> bucket;

    for (char& c : cpy) {
        if (std::isupper(c)) {
            c = std::tolower(c);
        }
        if (c != ' ') {
            auto it = bucket.find(c);
            if (it == bucket.end()) {
                bucket.insert({ c, 1 });
            }
            else {
                ++it->second;
            }
        }
    }
    std::size_t oddCount{};
    for (auto [key, value] : bucket) {
        if (value % 2 != 0)
            ++oddCount;
    }
    return oddCount <= 1;
}

////////////////////////////////////////
int main(int argc, char** argv)
{
    if (argc > 1) {
        std::string str{ argv[1] };
        std::cout << (isPermOfPalindrome(str) ? "True" : "False") << '\n';
    }
    else {
        std::cout << "Usage: " << argv[0] << " <string>\n";
    }
}
