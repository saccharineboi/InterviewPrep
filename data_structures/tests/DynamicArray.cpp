#include "../DynamicArray.hpp"
#include "Common.hpp"

#include <cstdio>
#include <cstdint>
#include <cmath>
#include <random>
#include <iostream>
#include <memory>

////////////////////////////////////////
int main()
{
    {
        DynamicArray<std::int32_t> da;
        TEST(da.size() == 0 && da.capacity() == 8, "Empty DynamicArray");
    }

    {
        DynamicArray<std::int32_t> da(10);
        TEST(da.size() == 10 && da.capacity() == 16, "DynamicArray with size");
    }

    {
        DynamicArray<std::int32_t> da(3, 5);
        TEST(da.size() == 3 && da.capacity() == 8 && da[0] == 5 && da[1] == 5 && da[2] == 5, "DynamicArray with size initialized");
    }

    {
        DynamicArray<std::int32_t> a(2, 3);
        DynamicArray<std::int32_t> b(a);
        TEST(b.size() == a.size() && b.capacity() == a.capacity() && a[0] == 3 && a[1] == 3 && b[0] == 3 && b[1] == 3, "DynamicArray copy constructor");
    }

    {
        DynamicArray<std::int32_t> a(2, 3);
        DynamicArray<std::int32_t> b(std::move(a));
        TEST(a.size() == 0 && a.capacity() == 0 && b.size() == 2 && b.capacity() == 8 && b[0] == 3 && b[1] == 3, "DynamicArray move constructor");
    }

    {
        DynamicArray<std::int32_t> a(2, 3);
        DynamicArray<std::int32_t> b(5, 5);
        b = a;
        TEST(a.size() == b.size() && a.capacity() == b.capacity() && a[0] == 3 && a[1] == 3 && b[0] == 3 && b[1] == 3, "DynamicArray copy assignment");
    }

    {
        DynamicArray<std::int32_t> a(3, 3);
        DynamicArray<std::int32_t> b(4, 4);
        a = std::move(b);
        TEST(a.size() == 4 && a.capacity() == 8 && b.size() == 0 && b.capacity() == 0 && a[0] == 4 && a[1] == 4 && a[2] == 4 && a[3] == 4, "DynamicArray move assignment");
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
        TEST(da.size() == 3 && da.capacity() == 8 && da[0] == 10 && da[1] == 20 && da[2] == 30, "DynamicArray push_back");
    }

    {
        DynamicArray<std::int32_t> da;
        for (std::int32_t i = 0; i < 100; ++i) {
            da.push_back(i);
        }
        TEST(da.size() == 100 && da.capacity() == 128, "DynamicArray large push_back");
    }

    {
        DynamicArray<std::int32_t> da;
        da.push_front(10);
        da.push_front(20);
        da.push_front(30);
        TEST(da.size() == 3 && da.capacity() == 8 && da[0] == 30 && da[1] == 20 && da[2] == 10, "DynamicArray push_front");
    }

    {
        DynamicArray<std::int32_t> da;
        da.push_back(199);
        da.push_back(299);
        std::int32_t x = da.pop_back();
        std::int32_t y = da.pop_back();
        TEST(da.size() == 0 && da.capacity() == 8 && x == 299 && y == 199, "DynamicArray pop_back");
    }

    {
        DynamicArray<std::int32_t> da;
        da.push_back(199);
        da.push_back(299);
        std::int32_t x = da.pop_front();
        std::int32_t y = da.pop_front();
        TEST(da.size() == 0 && da.capacity() == 8 && x == 199 && y == 299, "DynamicArray pop_front");
    }

    {
        DynamicArray<std::int32_t> da;
        for (std::int32_t i = 0; i < 100; ++i)
            da.push_back(i);
        while (da.size() > 0)
            da.pop_back();
        TEST(da.size() == 0 && da.capacity() == 128, "DynamicArray pop_back large");
    }

    {
        DynamicArray<std::int32_t> da;
        for (std::int32_t i = 0; i < 100; ++i)
            da.push_back(i);
        while (da.size() > 0)
            da.pop_front();
        TEST(da.size() == 0 && da.capacity() == 128, "DynamicArray pop_front large");
    }
}
