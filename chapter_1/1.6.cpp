#include <string>
#include <iostream>

////////////////////////////////////////
std::string compress(const std::string& str)
{
    // Time: O(n)
    // Space: O(n), can be turned into O(1) if compression is done in-place
    std::string compressed;
    if (str.size() > 0) {
        char currentChar{ str[0] };
        std::size_t currentCharCount{ 1 };
        for (std::size_t i = 1; i < str.size(); ++i) {
            if (str[i] == currentChar) {
                ++currentCharCount;
            }
            else {
                compressed.push_back(currentChar);
                compressed.append(std::to_string(currentCharCount));
                currentChar = str[i];
                currentCharCount = 1;
            }
        }
        compressed.push_back(currentChar);
        compressed.append(std::to_string(currentCharCount));
    }
    return compressed;
}

////////////////////////////////////////
int main(int argc, char** argv)
{
    if (argc > 1) {
        std::string input{ argv[1] };
        std::cout << compress(input) << '\n';
    }
    else {
        std::cout << "Usage: " << argv[0] << " <string>\n";
    }
}
