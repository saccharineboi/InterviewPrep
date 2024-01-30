#pragma once

#include <cstdint>
#include <cstring>
#include <algorithm>

template <typename T, int N>
struct Stack
{
private:
    T mBuffer[N];
    std::size_t mSize;

public:
    Stack(): mSize{}
    {
        std::memset(mBuffer, {}, sizeof(T) * N);
    }

    Stack(const Stack& other)
        : mSize{other.mSize}
    {
        std::copy(&other.mBuffer[0], &other.mBuffer[mSize], &mBuffer[0]);
    }

    Stack& operator=(const Stack& other)
    {
        if (this != &other) {
            mSize = other.mSize;
            std::copy(&other.mBuffer[0], &other.mBuffer[mSize], &mBuffer[0]);
        }
        return *this;
    }

    Stack(Stack&& other)
        : mSize{other.mSize}
    {
        for (std::size_t i{}; i < mSize; ++i) {
            mBuffer[i] = std::move(other.mBuffer[i]);
        }
        other.mSize = 0;
    }

    Stack& operator=(Stack&& other)
    {
        if (this != &other) {
            mSize = other.mSize;
            for (std::size_t i{}; i < mSize; ++i) {
                mBuffer[i] = std::move(other.mBuffer[i]);
            }
            other.mSize = 0;
        }
        return *this;
    }

    std::size_t Size() const { return mSize; }

    void Push(const T& value)
    {
        if (mSize < N) {
            mBuffer[mSize] = value;
            ++mSize;
        }
    }

    void Push(T&& value)
    {
        if (mSize < N) {
            mBuffer[mSize] = std::move(value);
            ++mSize;
        }
    }

    T Pop()
    {
        if (mSize > 0) {
            T value{ std::move(mBuffer[mSize - 1]) };
            --mSize;
            return value;
        }
        return {};
    }

    T Peek() const
    {
        return mBuffer[mSize - 1];
    }

    void Clear()
    {
        mSize = 0;
    }

    bool operator==(const Stack& other) const
    {
        if (mSize != other.mSize) {
            return false;
        }
        for (std::size_t i{}; i < mSize; ++i) {
            if (mBuffer[i] != other.mBuffer[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Stack& other) const
    {
        return !(*this == other);
    }
};
