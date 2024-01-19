// dynamic array

#pragma once

#include <cstdint>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>

////////////////////////////////////////
struct DynamicArray
{
private:
    int* mData;
    std::size_t mSize;
    std::size_t mCapacity;

    ////////////////////////////////////////
    std::size_t findNextPowerOfTwo(std::size_t n)
    {
        return n < 8 ? 8 : std::pow(2, std::floor(std::log2(n) + 1));
    }

public:
    ////////////////////////////////////////
    std::size_t Size() const { return mSize; }
    std::size_t Capacity() const { return mCapacity; }

    ////////////////////////////////////////
    int* begin() { return &mData[0]; }
    const int* cbegin() const { return &mData[0]; }

    ////////////////////////////////////////
    int* end() { return &mData[mSize]; }
    const int* cend() const { return &mData[mSize]; }

    ////////////////////////////////////////
    int operator[](std::size_t i) const { return mData[i]; }

    ////////////////////////////////////////
    bool operator==(const DynamicArray& other) const
    {
        if (mSize != other.mSize)
            return false;
        for (std::size_t i = 0; i < mSize; ++i)
            if (mData[i] != other.mData[i])
                return false;
        return true;
    }

    ////////////////////////////////////////
    DynamicArray& push_back(int value)
    {
        if (mSize < mCapacity) {
            mData[mSize] = value;
            ++mSize;
        }
        else {
            std::size_t newCapacity{ findNextPowerOfTwo(mCapacity) };

            int* newData = new int[newCapacity];
            for (std::size_t i = 0; i < mSize; ++i) {
                newData[i] = mData[i];
            }
            newData[mSize] = value;
            ++mSize;
            mCapacity = newCapacity;
            delete[] mData;
            mData = newData;
        }
        return *this;
    }

    ////////////////////////////////////////
    int pop_back()
    {
        if (mSize > 0) {
            int value = mData[mSize - 1];
            --mSize;
            return value;
        }
        return {};
    }

    ////////////////////////////////////////
    DynamicArray& push_front(int value)
    {
        if (mSize < mCapacity) {
            for (std::size_t i = mSize; i > 0; --i) {
                mData[i] = mData[i - 1];
            }
            mData[0] = value;
            ++mSize;
        }
        else {
            std::size_t newCapacity{ findNextPowerOfTwo(mCapacity) };

            int* newData = new int[newCapacity];
            newData[0] = value;
            for (std::size_t i = 0; i < mSize; ++i) {
                newData[i + 1] = mData[i];
            }
            ++mSize;
            mCapacity = newCapacity;
            delete[] mData;
            mData = newData;
        }
        return *this;
    }

    ////////////////////////////////////////
    int pop_front()
    {
        if (mSize > 0) {
            int value = mData[0];
            for (std::size_t i = 1; i < mSize; ++i) {
                mData[i - 1] = mData[i];
            }
            --mSize;
            return value;
        }
        return {};
    }

    ////////////////////////////////////////
    DynamicArray()
        : mData{}, mSize{}, mCapacity{findNextPowerOfTwo(0)}
    {
        mData = new int[mCapacity];
    }

    ////////////////////////////////////////
    explicit DynamicArray(std::size_t size)
        : mData{}, mSize{size}, mCapacity{findNextPowerOfTwo(size)}
    {
        mData = new int[mCapacity];
        for (std::size_t i = 0; i < mSize; ++i) {
            mData[i] = {};
        }
    }

    ////////////////////////////////////////
    DynamicArray(std::size_t size, int value)
        : mData{}, mSize{size}, mCapacity{findNextPowerOfTwo(size)}
    {
        mData = new int[mCapacity];
        for (std::size_t i = 0; i < mSize; ++i) {
            mData[i] = value;
        }
    }

    ////////////////////////////////////////
    ~DynamicArray()
    {
        delete[] mData;
        mCapacity = mSize = 0;
    }

    ////////////////////////////////////////
    DynamicArray(const DynamicArray& other)
        : mData{}, mSize{other.mSize}, mCapacity{other.mCapacity}
    {
        mData = new int[mCapacity];
        for (std::size_t i = 0; i < mSize; ++i) {
            mData[i] = other.mData[i];
        }
    }

    ////////////////////////////////////////
    DynamicArray& operator=(const DynamicArray& other)
    {
        if (this != &other) {
            delete[] mData;

            mSize = other.mSize;
            mCapacity = other.mCapacity;

            mData = new int[mCapacity];

            for (std::size_t i = 0; i < mSize; ++i) {
                mData[i] = other.mData[i];
            }
        }
        return *this;
    }

    ////////////////////////////////////////
    DynamicArray(DynamicArray&& other)
        : mData{other.mData},
          mSize{other.mSize},
          mCapacity{other.mCapacity}
    {
        other.mData = nullptr;
        other.mSize = other.mCapacity = 0;
    }

    ////////////////////////////////////////
    DynamicArray& operator=(DynamicArray&& other)
    {
        if (this != &other) {
            delete[] mData;

            mData = other.mData;
            mSize = other.mSize;
            mCapacity = other.mCapacity;

            other.mData = nullptr;
            other.mSize = other.mCapacity = 0;
        }
        return *this;
    }
};
