#include <string>
#include <iostream>
#include <unordered_set>
#include <cstdlib>
#include <cmath>

////////////////////////////////////////
bool isOneAway(const std::string& s0, const std::string& s1)
{
    std::size_t minValue{ std::min(s0.size(), s1.size()) };
    std::size_t maxValue{ std::max(s0.size(), s1.size()) };
    if (maxValue - minValue > 1) {
        return false;
    }
    std::unordered_set<char> bucket;
    for (char c : s0)
        bucket.insert(c);

    std::size_t oldSize{ bucket.size() };
    for (char c : s1)
        bucket.insert(c);

    minValue = std::min(oldSize, bucket.size());
    maxValue = std::max(oldSize, bucket.size());
    return (maxValue - minValue) <= 1;
}

////////////////////////////////////////
int main(int argc, char** argv)
{
    if (argc > 2) {
        std::string s0{ argv[1] }; 
        std::string s1{ argv[2] };
        std::cout << isOneAway(s0, s1) << '\n';
    }
    else {
        std::cout << "Usage: " << argv[0] << " <string> <string>\n";
    }
}
