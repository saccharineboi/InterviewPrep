#pragma once

#include <cstdint>
#include <cstring>
#include <memory>

////////////////////////////////////////
template <typename T, int N>
struct DoubleEndedQueue
{
private:
    T mBuffer[N];
    std::size_t mSize;
    std::size_t mBegin;

public:
    DoubleEndedQueue(): mSize{}, mBegin{}
    {
        for (int i{}; i < N; ++i) {
            mBuffer[i] = {};
        }
    }

    DoubleEndedQueue(const DoubleEndedQueue& other)
        : mSize{other.mSize}, mBegin{other.mBegin}
    {
        for (int i{}; i < N; ++i) {
            mBuffer[i] = other.mBuffer[i];
        }
    }

    DoubleEndedQueue& operator=(const DoubleEndedQueue& other)
    {
        if (this != &other) {
            mSize = other.mSize;
            mBegin = other.mBegin;
            for (int i{}; i < N; ++i) {
                mBuffer[i] = other.mBuffer[i];
            }
        }
        return *this;
    }

    DoubleEndedQueue(DoubleEndedQueue&& other)
        : mSize{other.mSize}, mBegin{other.mBegin}
    {
        for (int i{}; i < N; ++i) {
            mBuffer[i] = other.mBuffer[i];
        }
        other.mSize = 0;
        other.mBegin = 0;
    }

    DoubleEndedQueue& operator=(DoubleEndedQueue&& other)
    {
        if (this != &other) {
            for (int i{}; i < N; ++i) {
                mBuffer[i] = other.mBuffer[i];
            }
            mSize = other.mSize;
            mBegin = other.mBegin;

            other.mSize = 0;
            other.mBegin = 0;
        }
        return *this;
    }

    std::size_t Size() const { return mSize; }

    void EnqueueBack(const T& value)
    {
        if (mSize < N) {
            mBuffer[(mBegin + mSize) % N] = value;
            ++mSize;
        }
        else {
            // std::cerr << "queue is full\n";
        }
    }

    void EnqueueBack(T&& value)
    {
        if (mSize < N) {
            mBuffer[(mBegin + mSize) % N] = std::move(value);
            ++mSize;
        }
        else {
            // std::cerr << "queue is full\n";
        }
    }

    void EnqueueFront(const T& value)
    {
        if (mSize < N) {
            std::size_t begin{ (mBegin + 1) % N };
            T prevElement{ std::move(mBuffer[mBegin]) };
            for (std::size_t i{}; i < mSize; ++i) {
                T currentElement{ std::move(mBuffer[begin]) };
                mBuffer[begin] = std::move(prevElement);
                prevElement = std::move(currentElement);
                begin = (begin + 1) % N;
            }
            mBuffer[mBegin] = value;
            ++mSize;
        }
        else {
            // std::cerr << "queue is full\n";
        }
    }

    void EnqueueFront(T&& value)
    {
        if (mSize < N) {
            std::size_t begin{ (mBegin + 1) % N };
            T prevElement{ std::move(mBuffer[mBegin]) };
            for (std::size_t i{}; i < mSize; ++i) {
                T currentElement{ std::move(mBuffer[begin]) };
                mBuffer[begin] = std::move(prevElement);
                prevElement = std::move(currentElement);
                begin = (begin + 1) % N;
            }
            mBuffer[mBegin] = std::move(value);
            ++mSize;
        }
        else {
            // std::cerr << "queue is full\n";
        }
    }

    T DequeueFront()
    {
        if (mSize > 0) {
            T value{ std::move(mBuffer[mBegin]) };
            mBegin = (mBegin + 1) % N;
            --mSize;
            return value;
        }
        // std::cerr << "queue is empty\n";
        return {};
    }

    T DequeueBack()
    {
        if (mSize > 0) {
            T value{ std::move(mBuffer[(mBegin + mSize - 1) % N]) };
            --mSize;
            return value;
        }
        // std::cerr << "queue is empty\n";
        return {};
    }

    void Clear()
    {
        mBegin = 0;
        mSize = 0;
    }

    bool operator==(const DoubleEndedQueue& other)
    {
        if (mSize != other.mSize || mBegin != other.mBegin) {
            return false;
        }
        for (int i{}; i < N; ++i) {
            if (mBuffer[i] != other.mBuffer[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const DoubleEndedQueue& other)
    {
        return !(*this == other);
    }
};
