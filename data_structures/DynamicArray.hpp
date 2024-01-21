#pragma once

#include <cstdint>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <memory>

////////////////////////////////////////
template <typename T>
struct DynamicArray
{
private:
    T* mData;
    std::size_t mSize;
    std::size_t mCapacity;

    ////////////////////////////////////////
    std::size_t findNextPowerOfTwo(std::size_t n)
    {
        return n < 8 ? 8 : std::pow(2, std::floor(std::log2(n) + 1));
    }

public:
    ////////////////////////////////////////
    std::size_t size() const { return mSize; }
    std::size_t capacity() const { return mCapacity; }

    ////////////////////////////////////////
    T* begin() { return &mData[0]; }
    const T* cbegin() const { return &mData[0]; }

    ////////////////////////////////////////
    T* end() { return &mData[mSize]; }
    const T* cend() const { return &mData[mSize]; }

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
    bool operator!=(const DynamicArray& other) const
    {
        return !(*this == other);
    }

    ////////////////////////////////////////
    DynamicArray& push_back(const T& value)
    {
        if (mSize < mCapacity) {
            mData[mSize] = value;
            ++mSize;
        }
        else {
            std::size_t newCapacity{ findNextPowerOfTwo(mCapacity) };

            T* newData = new T[newCapacity];
            for (std::size_t i = 0; i < mSize; ++i) {
                newData[i] = std::move(mData[i]);
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
    DynamicArray& push_back(T&& value)
    {
        if (mSize < mCapacity) {
            mData[mSize] = std::move(value);
            ++mSize;
        }
        else {
            std::size_t newCapacity{ findNextPowerOfTwo(mCapacity) };

            T* newData = new T[newCapacity];
            for (std::size_t i = 0; i < mSize; ++i) {
                newData[i] = std::move(mData[i]);
            }
            newData[mSize] = std::move(value);
            ++mSize;
            mCapacity = newCapacity;
            delete[] mData;
            mData = newData;
        }
        return *this;
    }

    ////////////////////////////////////////
    T pop_back()
    {
        if (mSize > 0) {
            T value = std::move(mData[mSize - 1]);
            --mSize;
            return value;
        }
        return {};
    }

    ////////////////////////////////////////
    DynamicArray& push_front(const T& value)
    {
        if (mSize < mCapacity) {
            for (std::size_t i = mSize; i > 0; --i) {
                mData[i] = std::move(mData[i - 1]);
            }
            mData[0] = value;
            ++mSize;
        }
        else {
            std::size_t newCapacity{ findNextPowerOfTwo(mCapacity) };

            T* newData = new T[newCapacity];
            newData[0] = value;
            for (std::size_t i = 0; i < mSize; ++i) {
                newData[i + 1] = std::move(mData[i]);
            }
            ++mSize;
            mCapacity = newCapacity;
            delete[] mData;
            mData = newData;
        }
        return *this;
    }

    ////////////////////////////////////////
    DynamicArray& push_front(T&& value)
    {
        if (mSize < mCapacity) {
            for (std::size_t i = mSize; i > 0; --i) {
                mData[i] = std::move(mData[i - 1]);
            }
            mData[0] = std::move(value);
            ++mSize;
        }
        else {
            std::size_t newCapacity{ findNextPowerOfTwo(mCapacity) };

            T* newData = new T[newCapacity];
            newData[0] = std::move(value);
            for (std::size_t i = 0; i < mSize; ++i) {
                newData[i + 1] = std::move(mData[i]);
            }
            ++mSize;
            mCapacity = newCapacity;
            delete[] mData;
            mData = newData;
        }
        return *this;
    }

    ////////////////////////////////////////
    T pop_front()
    {
        if (mSize > 0) {
            T value = std::move(mData[0]);
            for (std::size_t i = 1; i < mSize; ++i) {
                mData[i - 1] = std::move(mData[i]);
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
        mData = new T[mCapacity];
    }

    ////////////////////////////////////////
    explicit DynamicArray(std::size_t size)
        : mData{}, mSize{size}, mCapacity{findNextPowerOfTwo(size)}
    {
        mData = new T[mCapacity];
        for (std::size_t i = 0; i < mSize; ++i) {
            mData[i] = {};
        }
    }

    ////////////////////////////////////////
    DynamicArray(std::size_t size, const T& value)
        : mData{}, mSize{size}, mCapacity{findNextPowerOfTwo(size)}
    {
        mData = new T[mCapacity];
        for (std::size_t i = 0; i < mSize; ++i) {
            mData[i] = value;
        }
    }

    ////////////////////////////////////////
    DynamicArray(std::size_t size, T&& value)
        : mData{}, mSize{size}, mCapacity{findNextPowerOfTwo(size)}
    {
        mData = new T[mCapacity];
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
        mData = new T[mCapacity];
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

            mData = new T[mCapacity];

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
