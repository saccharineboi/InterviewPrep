#include <iostream>
#include <memory>
#include <functional>
#include <cstring>
#include <cstdlib>
#include <algorithm>

////////////////////////////////////////
template <typename T, typename Comp>
void insertionsort(T& container, Comp comp = std::less<>{})
{
    for (std::size_t i{ 1 }; i < container.size(); ++i) {
        auto value{ std::move(container[i]) };
        while (i > 0 && comp(container[i - 1], value)) {
            container[i] = std::move(container[i - 1]);
            --i;
        }
        container[i] = std::move(value);
    }
}

////////////////////////////////////////
int main(int argc, char** argv)
{
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " lt|gt <list of integers>\n";
        std::exit(EXIT_FAILURE);
    }
    std::function<bool(int, int)> comp;
    if (!std::strncmp(argv[1], "lt", 2)) {
        comp = std::less{};
    }
    else if(!std::strncmp(argv[1], "gt", 2)) {
        comp = std::greater{};
    }
    else {
        std::cerr << argv[0] << ": " << argv[1] << " is invalid\n";
        std::exit(EXIT_FAILURE);
    }
    std::vector<int> digits;
    digits.reserve(argc - 2);
    for (int i{2}; i < argc; ++i) {
        digits.push_back(std::atoi(argv[i]));
    }
    insertionsort(digits, comp);
    std::cout << argv[0] << ": sorted: ";
    std::ranges::for_each(digits, [](auto&& x){ std::cout << x << ' '; });
    std::cout << '\n';
}
