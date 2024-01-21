#include <iostream>
#include <string>

////////////////////////////////////////
bool isSubstring(const std::string& s1, const std::string& s2)
{
    std::size_t cnt{};
    for (char c : s2) {
        if (s1.find(c) != std::string::npos) {
            ++cnt;
            if (cnt == s1.size()) {
                break;
            }
        }
        else {
            cnt = 0;
        }
    }
    return cnt == s1.size();
}

////////////////////////////////////////
bool isRotationOf(const std::string& s1, const std::string& s2)
{
    return s1.size() == s2.size() && isSubstring(s1, s2 + s2);
}

////////////////////////////////////////
int main(int argc, char** argv)
{
    if (argc > 2) {
        std::string s1{ argv[1] };
        std::string s2{ argv[2] };
        if (isRotationOf(s1, s2)) {
            std::cout << s1 << " is a rotation of " << s2 << '\n';
        }
        else {
            std::cout << s1 << " is NOT a rotation of " << s2 << '\n';
        }
    } 
    else {
        std::cout << "Usage: " << argv[0] << " <string> <string>\n";
    }
}
