#include <string>
#include <iostream>
#include <unordered_set>

////////////////////////////////////////
bool checkPerm(const std::string& a, const std::string& b)
{
    // Time: O(a)
    // Space: O(a)
    if (a.size() != b.size())
        return false;

    std::unordered_set<char> bucketForA;
    for (char c : a)
        bucketForA.insert(c);
    if (bucketForA.size() != a.size())
        return false;

    std::unordered_set<char> bucketForB;
    for (char c : b)
        bucketForB.insert(c);
    if (bucketForB.size() != b.size())
        return false;

    if (bucketForA.size() == bucketForB.size()) {
        for (char c : bucketForA) {
            if (bucketForB.find(c) == bucketForB.end())
                return false;
        }
        return true;
    }
    return false;
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
