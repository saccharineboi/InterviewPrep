#include "../DynamicArray.hpp"

#include <cstdio>
#include <cstdint>
#include <cmath>
#include <random>
#include <iostream>
#include <memory>

////////////////////////////////////////
#define TEST(EXPR, MESSAGE) \
    if (EXPR) \
        std::cout << "[OK] "; \
    else \
        std::cout << "[ERROR] "; \
    std::cout << MESSAGE << '\n'

////////////////////////////////////////
int main()
{
    {
        DynamicArray<std::int32_t> da;
        TEST(da.Size() == 0 && da.Capacity() == 8, "Empty DynamicArray");
    }

    {
        DynamicArray<std::int32_t> da(10);
        TEST(da.Size() == 10 && da.Capacity() == 16, "DynamicArray with size");
    }

    {
        DynamicArray<std::int32_t> da(3, 5);
        TEST(da.Size() == 3 && da.Capacity() == 8 && da[0] == 5 && da[1] == 5 && da[2] == 5, "DynamicArray with size initialized");
    }

    {
        DynamicArray<std::int32_t> a(2, 3);
        DynamicArray<std::int32_t> b(a);
        TEST(b.Size() == a.Size() && b.Capacity() == a.Capacity() && a[0] == 3 && a[1] == 3 && b[0] == 3 && b[1] == 3, "DynamicArray copy constructor");
    }

    {
        DynamicArray<std::int32_t> a(2, 3);
        DynamicArray<std::int32_t> b(std::move(a));
        TEST(a.Size() == 0 && a.Capacity() == 0 && b.Size() == 2 && b.Capacity() == 8 && b[0] == 3 && b[1] == 3, "DynamicArray move constructor");
    }

    {
        DynamicArray<std::int32_t> a(2, 3);
        DynamicArray<std::int32_t> b(5, 5);
        b = a;
        TEST(a.Size() == b.Size() && a.Capacity() == b.Capacity() && a[0] == 3 && a[1] == 3 && b[0] == 3 && b[1] == 3, "DynamicArray copy assignment");
    }

    {
        DynamicArray<std::int32_t> a(3, 3);
        DynamicArray<std::int32_t> b(4, 4);
        a = std::move(b);
        TEST(a.Size() == 4 && a.Capacity() == 8 && b.Size() == 0 && b.Capacity() == 0 && a[0] == 4 && a[1] == 4 && a[2] == 4 && a[3] == 4, "DynamicArray move assignment");
    }

    {
        DynamicArray<std::int32_t> a(10, 99);
        DynamicArray<std::int32_t> b(10, -99);
        DynamicArray<std::int32_t> c(20, 99);
        DynamicArray<std::int32_t> d(10, 99);
        TEST(a != b && a != c && a == d && b != c && b != d && c != d, "DynamicArray value comparison");
    }

    {
        DynamicArray<std::int32_t> da;
        da.push_back(10);
        da.push_back(20);
        da.push_back(30);
        TEST(da.Size() == 3 && da.Capacity() == 8 && da[0] == 10 && da[1] == 20 && da[2] == 30, "DynamicArray push_back");
    }

    {
        DynamicArray<std::int32_t> da;
        for (std::int32_t i = 0; i < 100; ++i) {
            da.push_back(i);
        }
        TEST(da.Size() == 100 && da.Capacity() == 128, "DynamicArray large push_back");
    }

    {
        DynamicArray<std::int32_t> da;
        da.push_front(10);
        da.push_front(20);
        da.push_front(30);
        TEST(da.Size() == 3 && da.Capacity() == 8 && da[0] == 30 && da[1] == 20 && da[2] == 10, "DynamicArray push_front");
    }

    {
        DynamicArray<std::int32_t> da;
        da.push_back(199);
        da.push_back(299);
        std::int32_t x = da.pop_back();
        std::int32_t y = da.pop_back();
        TEST(da.Size() == 0 && da.Capacity() == 8 && x == 299 && y == 199, "DynamicArray pop_back");
    }

    {
        DynamicArray<std::int32_t> da;
        da.push_back(199);
        da.push_back(299);
        std::int32_t x = da.pop_front();
        std::int32_t y = da.pop_front();
        TEST(da.Size() == 0 && da.Capacity() == 8 && x == 199 && y == 299, "DynamicArray pop_front");
    }

    {
        DynamicArray<std::int32_t> da;
        for (std::int32_t i = 0; i < 100; ++i)
            da.push_back(i);
        while (da.Size() > 0)
            da.pop_back();
        TEST(da.Size() == 0 && da.Capacity() == 128, "DynamicArray pop_back large");
    }

    {
        DynamicArray<std::int32_t> da;
        for (std::int32_t i = 0; i < 100; ++i)
            da.push_back(i);
        while (da.Size() > 0)
            da.pop_front();
        TEST(da.Size() == 0 && da.Capacity() == 128, "DynamicArray pop_front large");
    }
}
