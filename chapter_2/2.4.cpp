#include <list>
#include <iostream>
#include <random>

////////////////////////////////////////
void fillList(std::list<int>& lst, int len)
{
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 10);
    for (int i = 0; i < len; ++i) {
        lst.push_front(dist(rd));
    }
}

////////////////////////////////////////
void printList(const std::list<int>& lst)
{
    for (auto it{ lst.begin() }; it != lst.end(); ++it) {
        std::cout << *it;
        if (std::next(it) != lst.end()) {
            std::cout << " -> ";
        }
    }
    if (lst.size() > 0) {
        std::cout << '\n';
    }
}

////////////////////////////////////////
void partitionList(std::list<int>::iterator begin, std::list<int>::iterator end, int x)
{
    std::size_t size{};
    for (auto it{ begin }; it != end; ++it) {
        ++size;
    }
    if (size > 1) {
        auto newBegin{ begin };
        for (std::size_t i = 0; i < size / 2; ++i) {
            ++newBegin;
        }
        partitionList(begin, newBegin, x);
        partitionList(newBegin, end, x);

        auto prevIt{ begin };
        while (begin != end) {
            if (*begin < x) {
                std::swap(*begin, *prevIt);
                ++prevIt;
            }
            ++begin;
        }
    }
}

////////////////////////////////////////
void partitionList(std::list<int>& lst, int x)
{
    partitionList(lst.begin(), lst.end(), x);
}

////////////////////////////////////////
int main(int argc, char** argv)
{
    if (argc > 2) {
        int x{ std::atoi(argv[1]) };
        int len{ std::atoi(argv[2]) };

        std::list<int> lst;
        fillList(lst, len);
        std::cout << "Original list:\n";
        printList(lst);

        partitionList(lst, x);
        std::cout << "Paritioned list:\n";
        printList(lst);
    }
    else {
        std::cout << "Usage: " << argv[0] << " <x> <list length>\n";
    }
}
