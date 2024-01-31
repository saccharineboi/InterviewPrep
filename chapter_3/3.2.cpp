#include <iostream>
#include <random>
#include <memory>

////////////////////////////////////////
template <int N>
struct Stack
{
private:
    int mBuffer[N];
    int mSize;
    Stack<N>* mMinStack;
    bool mOutputDebug;

public:
    Stack(Stack<N>* minStack = nullptr, bool outputDebug = false)
        : mSize{}, mMinStack{minStack}, mOutputDebug{outputDebug}
    {
        for (int i = 0; i < N; ++i) {
            mBuffer[i] = {};
        }
    }

    int Size() const { return mSize; }

    void Push(int value)
    {
        if (mSize < N) {
            mBuffer[mSize] = value;
            ++mSize;
            if (mMinStack) {
                if (mMinStack->Size() == 0 || mMinStack->Peek() > value) {
                    mMinStack->Push(value);
                }
                else {
                    mMinStack->Push(mMinStack->Peek());
                }
            }
        }
        else {
            if (mOutputDebug) {
                std::cerr << "stack is full\n";
            }
        }
    }

    int Pop()
    {
        if (mSize > 0) {
            int value{ mBuffer[mSize - 1] };
            --mSize;
            if (mMinStack) {
                mMinStack->Pop();
            }
            return value;
        }
        if (mOutputDebug) {
            std::cerr << "stack is empty\n";
        }
        return {};
    }

    int Min() const
    {
        if (mSize > 0 && mMinStack) {
            return mMinStack->Peek();
        }
        return {};
    }

    int Peek() const
    {
        if (mSize > 0) {
            return mBuffer[mSize - 1];
        }
        return {};
    }
};

////////////////////////////////////////
int main()
{
    std::random_device rd;
    std::uniform_int_distribution<int> dist(1, 9);

    constexpr int SIZE{ 10 };
    Stack<SIZE> minStack;;
    Stack<SIZE> myStack(&minStack, true);

    for (int i{}; i < SIZE; ++i) {
        int value{ dist(rd) };
        myStack.Push(value);
        std::printf("Pushed %d into stack, min = %d\n", value, myStack.Min());
    }

    std::cout << "////////////////////////////////////////\n";

    for (int i{}; i < SIZE; ++i) {
        int value{ myStack.Pop() };
        std::printf("Popped %d from stack, min = %d\n", value, myStack.Min());
    }
}
