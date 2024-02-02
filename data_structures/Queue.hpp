#pragma once

#include <cstdint>
#include <cstring>
#include <memory>

////////////////////////////////////////
template <typename T, int N>
struct Queue
{
private:
    T mBuffer[N];
    std::size_t mSize;
    std::size_t mBegin;

public:
    Queue(): mSize{}, mBegin{}
    {
        for (int i{}; i < N; ++i) {
            mBuffer[i] = {};
        }
    }

    Queue(const Queue& other)
        : mSize{other.mSize}, mBegin{other.mBegin}
    {
        for (int i{}; i < N; ++i) {
            mBuffer[i] = other.mBuffer[i];
        }
    }

    Queue& operator=(const Queue& other)
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

    Queue(Queue&& other)
        : mSize{other.mSize}, mBegin{other.mBegin}
    {
        for (int i{}; i < N; ++i) {
            mBuffer[i] = other.mBuffer[i];
        }
        other.mSize = 0;
        other.mBegin = 0;
    }

    Queue& operator=(Queue&& other)
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

    void Enqueue(const T& value)
    {
        if (mSize < N) {
            mBuffer[(mBegin + mSize) % N] = value;
            ++mSize;
        }
        else {
            // std::cerr << "queue is full\n";
        }
    }

    void Enqueue(T&& value)
    {
        if (mSize < N) {
            mBuffer[(mBegin + mSize) % N] = std::move(value);
            ++mSize;
        }
        else {
            // std::cerr << "queue is full\n";
        }
    }

    T Dequeue()
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

    void Clear()
    {
        mBegin = 0;
        mSize = 0;
    }

    bool operator==(const Queue& other)
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

    bool operator!=(const Queue& other)
    {
        return !(*this == other);
    }
};
