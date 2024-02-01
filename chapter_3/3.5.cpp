#include <cstdlib>
#include <iostream>
#include <cstring>
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
        std::memset(mBuffer, 0, N * sizeof(int));
    }

    bool IsEmpty() const { return !mSize; }

    void Push(int value)
    {
        if (mSize < N) {
            mBuffer[mSize] = value;
            ++mSize;
        }
        else {
            std::cerr << "stack " << this << " is full\n";
        }
    }

    int Pop()
    {
        if (mSize) {
            int value{ mBuffer[mSize - 1] };
            --mSize;
            return value;
        }
        std::cerr << "stack " << this << " is empty\n";
        return {};
    }

    int Peek() const
    {
        if (mSize) {
            return mBuffer[mSize - 1];
        }
        std::cerr << "stack " << this << " is empty\n";
        return {};
    }

    void Sort()
    {
        if (!mSize) {
            return;
        }
        Stack<N> tempStack;
        int numElements{}, numTempFilled{};

        // count the elements
        while (!IsEmpty()) {
            tempStack.Push(Pop());
            ++numElements;
        }
        while (!tempStack.IsEmpty()) {
            Push(tempStack.Pop());
        }

        // sort
        while (true) {
            int smallestValue{ Peek() };
            int numSmallestValuesFound{};

            while (!IsEmpty()) {
                int value{ Pop() };
                if (value < smallestValue) {
                    smallestValue = value;
                    numSmallestValuesFound = 1;
                }
                else if (value == smallestValue) {
                    ++numSmallestValuesFound;
                }
                tempStack.Push(value);
            }
            for (int i{}; !tempStack.IsEmpty() && i < numElements - numTempFilled; ++i) {
                int value{ tempStack.Pop() };
                if (value > smallestValue) {
                    Push(value);
                }
            }
            for (int i{}; i < numSmallestValuesFound; ++i) {
                tempStack.Push(smallestValue);
                ++numTempFilled;
            }
            if (IsEmpty()) {
                break;
            }
        }
        // refill stack
        while (!tempStack.IsEmpty()) {
            Push(tempStack.Pop());
        }
    }
};

int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <number of elements>\n";
        std::exit(EXIT_FAILURE);
    }

    constexpr int maxNumElements{ 1000 };
    int numElements{ std::atoi(argv[1]) };
    if (numElements < 0 || numElements > maxNumElements) {
        std::cerr << numElements << " is an invalid number of elements\n";
        std::exit(EXIT_FAILURE);
    }

    Stack<maxNumElements> myStack;
    std::cout << "Pushing ";

    std::random_device rd;
    std::uniform_int_distribution<int> dist(1, 9);
    for (int i{}; i < numElements; ++i) {
        int value{ dist(rd) };
        myStack.Push(value);
        std::cout << value;
        if (i != numElements - 1) {
            std::cout << ", ";
        }
    }
    std::cout << '\n';

    myStack.Sort();
    std::cout << "Popping ";
    while (!myStack.IsEmpty()) {
        std::cout << myStack.Pop();
        if (!myStack.IsEmpty()) {
            std::cout << ", ";
        }
    }
    std::cout << '\n';
}
