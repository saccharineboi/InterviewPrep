#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <optional>
#include <vector>
#include <algorithm>

////////////////////////////////////////
template <typename T, typename S>
std::optional<std::size_t> binsearch(const T& container, S&& value)
{
    std::size_t left{};
    std::size_t right{ container.size() - 1 };

    while (left <= right && left < container.size() && right < container.size()) {
        std::size_t mid{ (left + right) / 2 };
        if (container[mid] == value) {
            return mid;
        }
        else if (container[mid] < value) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return {};
}

////////////////////////////////////////
int main(int argc, char** argv)
{
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <sorted list of numbers> <number to search>\n";
        std::exit(EXIT_FAILURE);
    }
    std::vector<int> digits;
    digits.reserve(argc - 2);
    for (int i{ 1 }; i < argc - 1; ++i) {
        digits.push_back(std::atoi(argv[i]));
    }
    std::ranges::sort(digits);
    int numToSearch{ std::atoi(argv[argc - 1]) };

    auto result{ binsearch(digits, numToSearch) };
    if (result.has_value()) {
        std::cout << numToSearch << " is located at " << result.value() << '\n';
    }
    else {
        std::cout << "Couldn't find " << numToSearch << '\n';
    }
}
