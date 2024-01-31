#include <cstdlib>
#include <iostream>
#include <vector>
#include <random>

////////////////////////////////////////
template <int N>
struct Stack
{
private:
    int mArray[N];
    int mSize;

public:
    Stack() : mSize{}
    {
        for (int i{}; i < N; ++i) {
            mArray[i] = {};
        }
    }

    int Size() const { return mSize; }

    void Push(int value)
    {
        if (mSize < N) {
            mArray[mSize] = value;
            ++mSize;
        }
    }

    int Pop()
    {
        if (mSize > 0) {
            int value{ mArray[mSize - 1] };
            --mSize;
            return value;
        }
        std::cerr << "stack is empty\n";
        return {};
    }

    int Peek() const
    {
        if (mSize > 0) {
            return mArray[mSize - 1];
        }
        std::cerr << "stack is empty\n";
        return {};
    }

    bool IsFull() const
    {
        return mSize == N;
    }

    bool IsEmpty() const
    {
        return mSize == 0;
    }
};

////////////////////////////////////////
template <int N>
struct StackOfPlates
{
private:
    std::vector<Stack<N>> mStacks;

public:
    void Push(int value)
    {
        if (!mStacks.size() || mStacks.back().IsFull()) {
            Stack<N> newStack;
            newStack.Push(value);
            mStacks.push_back(newStack);
        }
        else {
            mStacks.back().Push(value);
        }
    }

    int Pop()
    {
        while (mStacks.size() > 0 && mStacks.back().IsEmpty()) {
            mStacks.pop_back();
        }
        if (!mStacks.size()) {
            std::cerr << "no plates\n";
            return {};
        }
        int value{ mStacks.back().Pop() };
        if (mStacks.back().Size() == 0) {
            mStacks.pop_back();
        }
        return value;
    }

    int PopAt(int i)
    {
        if (i < 0 || i >= mStacks.size()) {
            std::cerr << "index " << i << " is invalid\n";
            return {};
        }
        if (mStacks[i].IsEmpty()) {
            std::cerr << "mStacks[" << i << "] is empty\n";
        }
        return mStacks[i].Pop();
    }

    int NumberOfStacks() const { return static_cast<int>(mStacks.size()); }
    int NumberOfPlatesInStack(int i) const { return mStacks[i].Size(); }

    int TotalNumberOfPlates() const
    {
        int cnt{};
        for (const Stack<N>& st : mStacks) {
            cnt += st.Size();
        }
        return cnt;
    }
};

////////////////////////////////////////
int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <number of plates>\n";
        std::exit(EXIT_FAILURE);
    }
    int numPlates{ std::atoi(argv[1]) };
    if (numPlates <= 0) {
        std::cout << "number of plates must be >0\n";
        std::exit(EXIT_FAILURE);
    }

    std::random_device rd;
    std::uniform_int_distribution<int> dist(1, 9);

    constexpr int stackSize{ 3 };
    StackOfPlates<stackSize> stackOfPlates;

    std::cout << "Pushing: ";
    for (int i{}; i < numPlates; ++i) {
        int value{ dist(rd) };
        stackOfPlates.Push(value);
        std::cout << value;
        if (i != numPlates - 1) {
            std::cout << ", ";
        }
    }
    std::cout << '\n';

    std::cout << "Size of each stack: " << stackSize << '\n';
    std::cout << "Total num plates: " << stackOfPlates.TotalNumberOfPlates() << '\n';
    std::cout << "Num stacks: " << stackOfPlates.NumberOfStacks() << '\n';

    std::cout << "Popping: ";
    while (stackOfPlates.TotalNumberOfPlates() > 0) {
        int value{ stackOfPlates.Pop() };
        std::cout << value;
        if (stackOfPlates.TotalNumberOfPlates() != 0) {
            std::cout << ", ";
        }
    }
    std::cout << '\n';

    std::cout << "Size of each stack: " << stackSize << '\n';
    std::cout << "Total num plates: " << stackOfPlates.TotalNumberOfPlates() << '\n';
    std::cout << "Num stacks: " << stackOfPlates.NumberOfStacks() << '\n';
}
