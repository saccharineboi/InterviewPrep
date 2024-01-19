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

    {
        DynamicArray<std::int32_t> da;
        if (da.Size() == 0 && da.Capacity() == 8)
            std::cout << "[OK]";
        else
            std::cout << "[ERROR]";
        std::cout << " Empty DynamicArray\n";
    }

    {
        DynamicArray<std::int32_t> da(10);
        if (da.Size() == 10 && da.Capacity() == 16)
            std::cout << "[OK]";
        else
            std::cout << "[ERROR]";
        std::cout << " DynamicArray with size\n";
    }

    {
        bool errored{};

        DynamicArray<std::int32_t> da(3, 5);
        for (int x : da) {
            if (x != 5) {
                std::cout << "[ERROR]";
                errored = true;
                break;
            }
        }
        if (!errored) {
            if (da.Size() == 3 && da.Capacity() == 8)
                std::cout << "[OK]";
            else
                std::cout << "[ERROR]";
        }
        std::cout << " DynamicArray with size initialized\n";
    }

    return 0;
}
