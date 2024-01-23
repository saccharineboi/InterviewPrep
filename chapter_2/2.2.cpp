#include <forward_list>
#include <iostream>

////////////////////////////////////////
std::string kth_to_last(const std::forward_list<std::string>& lst, int k)
{
    // Time: O(n + m) where m = length of longest string
    // Space: O(m)
    int size{};
    for (auto it{ lst.begin() }; it != lst.end(); ++it) {
        ++size;
    }
    int i{};
    for (auto it{ lst.begin() }; it != lst.end(); ++it) {
        if (size - i == k) {
            return std::string{ it->data() };
        }
        ++i;
    }
    return std::string{};
}

////////////////////////////////////////
int main(int argc, char** argv)
{
    if (argc > 2) {
        int k{ std::atoi(argv[1]) };
        std::forward_list<std::string> lst;
        for (int i = 2; i < argc; ++i) {
            lst.push_front(argv[i]);
        }
        lst.reverse();
        std::cout << kth_to_last(lst, k) << '\n';
    }
    else {
        std::cout << "Usage: " << argv[0] << " <k> <list of strings>\n";
    }
}
