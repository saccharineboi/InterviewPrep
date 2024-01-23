#include <list>
#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <cstring>

////////////////////////////////////////
void removeDupsWithBucket(std::list<std::string>& lst)
{
    // Time: O(n)
    // Space: O(n)
    std::unordered_set<std::string> bucket;
    for (auto it{ lst.begin() }; it != lst.end();) {
        if (bucket.find(it->data()) == bucket.end()) {
            bucket.insert(it->data());
            ++it;
        }
        else {
            auto nextIt{ std::next(it) };
            lst.erase(it);
            it = nextIt;
        }
    }
}

////////////////////////////////////////
void removeDupsWithoutBucket(std::list<std::string>& lst)
{
    // Time: O(n * log n)
    // Space: O(1)
    lst.sort();
    for (auto it{ lst.begin() }; it != lst.end();) {
        auto nextIt{ std::next(it) };
        if (nextIt != lst.end() && !std::strcmp(nextIt->data(), it->data())) {
            lst.erase(it);
            it = nextIt;
        }
        else {
            ++it;
        }
    }
}

////////////////////////////////////////
void printList(const std::list<std::string>& lst)
{
    for (const std::string& str : lst) {
        std::cout << str << "\n";
    }
}

////////////////////////////////////////
int main(int argc, char** argv)
{
    if (argc > 1) {
        std::list<std::string> lstA;
        std::list<std::string> lstB;
        for (int i = 1; i < argc; ++i) {
            lstA.push_back(argv[i]);
            lstB.push_back(argv[i]);
        }
        std::cout << "List A:\n";
        printList(lstA);
        std::cout << "\nList B:\n";
        printList(lstB);

        removeDupsWithBucket(lstA);
        std::cout << "\nList A Dups Removed:\n";
        printList(lstA);

        removeDupsWithoutBucket(lstB);
        std::cout << "\nList B Dups Removed:\n";
        printList(lstB);
    }
    else {
        std::cout << "Usage: " << argv[0] << " <string> #n times\n";
    }
}
