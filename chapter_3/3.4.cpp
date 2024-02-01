#include <iostream>
#include <cstdlib>
#include <random>

////////////////////////////////////////
template <int N>
struct Stack
{
private:
    int mBuffer[N];
    int mSize;

public:
    Stack(): mSize{}
    {
        for (int i{}; i < N; ++i) {
            mBuffer[i] = {};
        }
    }

    void Push(int value)
    {
        if (mSize < N) {
            mBuffer[mSize] = value;
            ++mSize;
        }
        else {
            std::cerr << "stack is full\n";
        }
    }

    int Pop()
    {
        if (mSize > 0) {
            int value{ mBuffer[mSize - 1] };
            --mSize;
            return value;
        }
        std::cerr << "stack is empty\n";
        return {};
    }

    int Peek() const
    {
        if (mSize > 0) {
            return mBuffer[mSize - 1];
        }
        std::cerr << "stack is empty\n";
        return {};
    }

    int Size() const { return mSize; }
    bool IsEmpty() const { return mSize == 0; }
    bool IsFull() const { return mSize == N; }
};

////////////////////////////////////////
template <int N>
struct MyQueue
{
private:
    Stack<N> mFirstStack;
    Stack<N> mSecondStack;

public:
    void Enqueue(int value)
    {
        mFirstStack.Push(value);
    }

    int Dequeue()
    {
        while (!mFirstStack.IsEmpty()) {
            mSecondStack.Push(mFirstStack.Pop());
        } 
        return mSecondStack.Pop();
    }

    int Size() const { return mFirstStack.Size() + mSecondStack.Size(); }
};

////////////////////////////////////////
int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <number of elements>\n";
        std::exit(EXIT_FAILURE);
    }

    constexpr int maxNumElements{ 1000 };
    int numElements{ std::atoi(argv[1]) };
    if (numElements <= 0 || numElements > maxNumElements) {
        std::cerr << numElements << " is an invalid number of elements\n";
        std::exit(EXIT_FAILURE);
    }

    std::random_device rd;
    std::uniform_int_distribution<int> dist(1, 9);

    std::cout << "Enqueueing: ";
    MyQueue<maxNumElements> myQueue;
    for (int i{}; i < numElements; ++i) {
        int value{ dist(rd) };
        std::cout << value;
        myQueue.Enqueue(value);

        if (i != numElements - 1) {
            std::cout << ", ";
        }
        else {
            std::cout << '\n';
        }
    }

    std::cout << "Dequeueing: ";
    while (myQueue.Size() > 0) {
        int value{ myQueue.Dequeue() };
        std::cout << value;

        if (!myQueue.Size()) {
            std::cout << '\n';
        }
        else {
            std::cout << ", ";
        }
    }
}
