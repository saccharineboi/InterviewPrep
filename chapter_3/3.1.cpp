#include <iostream>
#include <random>
#include <cassert>

////////////////////////////////////////
template <int N>
struct TripleStack
{
private:
    int mArray[N];

    int mFirstStackBegin, mFirstStackSize;
    int mSecondStackBegin, mSecondStackSize;
    int mThirdStackBegin, mThirdStackSize;

    int mEmptySlotsLeft;

    void shiftThirdStackRight()
    {
        int prevElement{ mArray[mThirdStackBegin] };
        for (int i = mThirdStackBegin + 1; i <= mThirdStackBegin + mThirdStackSize; ++i) {
            int currentElement{ mArray[i] };
            mArray[i] = prevElement;
            prevElement = currentElement;
        }
        ++mThirdStackBegin;
    }

    void shiftThirdStackLeft()
    {
        int nextElement{ mArray[mThirdStackBegin + mThirdStackSize - 1] };
        for (int i = mThirdStackBegin + mThirdStackSize - 2; i >= mThirdStackBegin - 1; --i) {
            int currentElement{ mArray[i] };
            mArray[i] = nextElement;
            nextElement = currentElement;
        }
        --mThirdStackBegin;
    }

    void shiftSecondStackRight()
    {
        int prevElement{ mArray[mSecondStackBegin] };
        for (int i = mSecondStackBegin + 1; i <= mSecondStackBegin + mSecondStackSize; ++i) {
            int currentElement{ mArray[i] };
            mArray[i] = prevElement;
            prevElement = currentElement;
        }
        ++mSecondStackBegin;
    }

    void shiftSecondStackLeft()
    {
        int nextElement{ mArray[mSecondStackBegin + mSecondStackSize - 1] };
        for (int i = mSecondStackBegin + mSecondStackSize - 2; i >= mSecondStackBegin - 1; --i) {
            int currentElement{ mArray[i] };
            mArray[i] = nextElement;
            nextElement = currentElement;
        }
        --mSecondStackBegin;
    }

public:
    TripleStack(): mFirstStackBegin{}, mFirstStackSize{},
                   mSecondStackBegin{}, mSecondStackSize{},
                   mThirdStackBegin{}, mThirdStackSize{},
                   mEmptySlotsLeft{N}
    {
        for (int i = 0; i < N; ++i) {
            mArray[i] = {};
        }
    }

    int size(int stackID) const
    {
        assert(stackID >= 0 && stackID < 3);
        if (stackID == 0) {
            return mFirstStackSize;
        }
        else if (stackID == 1) {
            return mSecondStackSize;
        }
        else {
            return mThirdStackSize;
        }
    }

    void push(int stackID, int value)
    {
        assert(stackID >= 0 && stackID < 3);
        if (mEmptySlotsLeft > 0) {
            if (stackID == 2) {
                mArray[mThirdStackBegin + mThirdStackSize] = value;
                ++mThirdStackSize;
            }
            else if (stackID == 1) {
                shiftThirdStackRight();
                mArray[mSecondStackBegin + mSecondStackSize] = value;
                ++mSecondStackSize;
            }
            else {
                shiftThirdStackRight();
                shiftSecondStackRight();
                mArray[mFirstStackBegin + mFirstStackSize] = value;
                ++mFirstStackSize;
            }
            --mEmptySlotsLeft;
        }
        else {
            std::fprintf(stderr, "no empty space left\n");
        }
    }

    int pop(int stackID)
    {
        assert(stackID >= 0 && stackID < 3);
        if (mEmptySlotsLeft != N) {
            if (stackID == 0) {
                if (mFirstStackSize == 0) {
                    std::fprintf(stderr, "first stack is empty\n");
                    return {};
                }
                int value{ mArray[mFirstStackBegin + mFirstStackSize - 1] };
                shiftSecondStackLeft();
                shiftThirdStackLeft();
                --mFirstStackSize;
                return value;
            }
            else if (stackID == 1) {
                if (mSecondStackSize == 0) {
                    std::fprintf(stderr, "second stack is empty\n");
                    return {};
                }
                int value{ mArray[mSecondStackBegin + mSecondStackSize - 1] };
                shiftThirdStackLeft();
                --mSecondStackSize;
                return value;
            }
            else {
                if (mThirdStackSize == 0) {
                    std::fprintf(stderr, "third stack is empty\n");
                    return {};
                }
                int value{ mArray[mThirdStackBegin + mThirdStackSize - 1] };
                --mThirdStackSize;
                return value;
            }
            ++mEmptySlotsLeft;
        }
        std::fprintf(stderr, "array is empty\n");
        return {};
    }

    int peek(int stackID) const
    {
        assert(stackID >= 0 && stackID < 3);
        if (mEmptySlotsLeft != N) {
            if (stackID == 0) {
                return mArray[mFirstStackBegin + mFirstStackSize - 1];
            }
            else if (stackID == 1) {
                return mArray[mSecondStackBegin + mSecondStackSize - 1];
            }
            else {
                return mArray[mThirdStackBegin + mThirdStackSize - 1];
            }
        }
        std::fprintf(stderr, "array is empty\n");
        return {};
    }

    void print() const
    {
        for (int i = 0; i < N; ++i) {
            std::printf("[DEBUG] %d -> %d\n", i, mArray[i]);
        }
    }
};

////////////////////////////////////////
int main()
{
    enum { FIRST_STACK, SECOND_STACK, THIRD_STACK };

    {
        std::printf("////////////////////////////////////////\n");

        constexpr int stackSize{ 5 };
        TripleStack<stackSize> myStack;

        myStack.push(FIRST_STACK, 1);
        myStack.push(FIRST_STACK, 2);
        myStack.push(FIRST_STACK, 3);
        myStack.push(FIRST_STACK, 4);
        myStack.push(FIRST_STACK, 5);

        std::printf("First stack size: %d\n", myStack.size(FIRST_STACK));
        std::printf("Second stack size: %d\n", myStack.size(SECOND_STACK));
        std::printf("Third stack size: %d\n", myStack.size(THIRD_STACK));

        myStack.print();
        while (myStack.size(FIRST_STACK) > 0) {
            std::printf("Popped %d\n", myStack.pop(FIRST_STACK));
        }
    }

    {
        std::printf("////////////////////////////////////////\n");

        constexpr int stackSize{ 5 };
        TripleStack<stackSize> myStack;

        myStack.push(SECOND_STACK, 1);
        myStack.push(SECOND_STACK, 2);
        myStack.push(SECOND_STACK, 3);
        myStack.push(SECOND_STACK, 4);
        myStack.push(SECOND_STACK, 5);

        std::printf("First stack size: %d\n", myStack.size(FIRST_STACK));
        std::printf("Second stack size: %d\n", myStack.size(SECOND_STACK));
        std::printf("Third stack size: %d\n", myStack.size(THIRD_STACK));

        myStack.print();
        while (myStack.size(SECOND_STACK) > 0) {
            std::printf("Popped %d\n", myStack.pop(SECOND_STACK));
        }
    }

    {
        std::printf("////////////////////////////////////////\n");

        constexpr int stackSize{ 5 };
        TripleStack<stackSize> myStack;

        myStack.push(THIRD_STACK, 1);
        myStack.push(THIRD_STACK, 2);
        myStack.push(THIRD_STACK, 3);
        myStack.push(THIRD_STACK, 4);
        myStack.push(THIRD_STACK, 5);

        std::printf("First stack size: %d\n", myStack.size(FIRST_STACK));
        std::printf("Second stack size: %d\n", myStack.size(SECOND_STACK));
        std::printf("Third stack size: %d\n", myStack.size(THIRD_STACK));

        myStack.print();
        while (myStack.size(THIRD_STACK) > 0) {
            std::printf("Popped %d\n", myStack.pop(THIRD_STACK));
        }
    }

    {
        std::printf("////////////////////////////////////////\n");

        constexpr int stackSize{ 5 };
        TripleStack<stackSize> myStack;

        myStack.push(FIRST_STACK, 1);
        myStack.push(SECOND_STACK, 1);
        myStack.push(THIRD_STACK, 1);
        myStack.push(THIRD_STACK, 2);
        myStack.push(THIRD_STACK, 3);

        myStack.push(FIRST_STACK, 100);
        myStack.push(SECOND_STACK, 200);
        myStack.push(THIRD_STACK, 300);

        std::printf("First stack size: %d\n", myStack.size(FIRST_STACK));
        std::printf("Second stack size: %d\n", myStack.size(SECOND_STACK));
        std::printf("Third stack size: %d\n", myStack.size(THIRD_STACK));

        myStack.print();
        while (myStack.size(FIRST_STACK) > 0) {
            std::printf("Popped %d\n", myStack.pop(FIRST_STACK));
        }
        while (myStack.size(SECOND_STACK) > 0) {
            std::printf("Popped %d\n", myStack.pop(SECOND_STACK));
        }
        while (myStack.size(THIRD_STACK) > 0) {
            std::printf("Popped %d\n", myStack.pop(THIRD_STACK));
        }
    }
}
