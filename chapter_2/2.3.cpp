#include <forward_list>
#include <string>
#include <iostream>

////////////////////////////////////////
void printList(const std::forward_list<std::string>& lst)
{
    std::size_t cnt{};
    for (auto it{ lst.begin() }; it != lst.end(); ++it) {
        std::cout << *it;
        if (std::next(it) != lst.end()) {
            std::cout << ", ";
        }
        ++cnt;
    }
    if (cnt > 0) {
        std::cout << '\n';
    }
}

////////////////////////////////////////
void delete_middle_node(std::forward_list<std::string>& lst)
{
    // Time: O(n)
    // Space: O(1)
    std::size_t size{};
    for (auto it{ lst.begin()}; it != lst.end(); ++it) {
        ++size;
    }
    std::size_t i{};
    std::forward_list<std::string>::iterator prevIt{ lst.begin() };
    for (auto it{ lst.begin() }; it != lst.end(); ++it, ++i) {
        if (i == size / 2) {
            lst.erase_after(prevIt);
            break;
        }
        prevIt = it;
    }
}

////////////////////////////////////////
int main(int argc, char** argv)
{
    if (argc > 3) {
        std::forward_list<std::string> lst;
        for (int i = 1; i < argc; ++i) {
            lst.push_front(argv[i]);
        }
        lst.reverse();
        delete_middle_node(lst);
        printList(lst);
    }
    else {
        std::cout << "Usage: " << argv[0] << " <list of strings, min length = 3>\n";
    }
}
