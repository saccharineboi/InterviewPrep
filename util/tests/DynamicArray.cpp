#include "../DynamicArray.hpp"

#include <cstdio>
#include <cstdint>
#include <cmath>
#include <random>
#include <iostream>
#include <memory>

int main()
{
    std::random_device rd;
    std::uniform_int_distribution<int> dist(10, 20);

    DynamicArray da;
    for (std::size_t i = 0; i < 20; ++i) {
        da.push_back(dist(rd));
    }

    while (da.Size() > 0) {
        std::cout << da.pop_back() << '\n';
    }
}
