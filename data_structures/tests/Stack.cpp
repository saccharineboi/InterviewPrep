#include "Common.hpp"
#include "../Stack.hpp"
#include <iostream>
#include <random>

int main()
{
    std::random_device rd;
    std::uniform_int_distribution<int> dist;

    {
        constexpr int size{ 5 };
        Stack<int, size> myStack;
        for (int i{}; i < size; ++i) {
            myStack.Push(dist(rd));
        }
        TEST(myStack.Size() == size, "Stack size #0");

        myStack.Push(99);
        TEST(myStack.Size() == size, "Stack size #1");

        myStack.Pop();
        TEST(myStack.Size() == size - 1, "Stack size #2");
        
        myStack.Clear();
        TEST(myStack.Size() == 0, "Stack size #3");
    }

    {
        constexpr int size{ 10 };
        Stack<int, size> stackA, stackB;
        Stack<int, size> stackC, stackD;

        for (int i{}; i < size; ++i) {
            stackA.Push(dist(rd));
        }

        for (int i{}; i < size; ++i) {
            stackB.Push(dist(rd));
        }

        TEST(stackA != stackB, "Stack != #0");

        for (int i{}; i < size; ++i) {
            stackC.Push(i * 10);
        }

        for (int i{}; i < size - 1; ++i) {
            stackD.Push(i * 10);
        }

        TEST(stackC != stackD, "Stack != #1");

        stackD.Clear();
        TEST(stackC != stackD, "Stack != #2");
    }

    {
        constexpr int size{ 20 };
        Stack<int, size> stackA, stackB;
        TEST(stackA == stackB, "Stack == #0");

        for (int i{}; i < size; ++i) {
            stackA.Push(i + 10);
            stackB.Push(i + 10);
        }
        TEST(stackA == stackB, "Stack == #1");

        stackA.Pop();
        TEST(!(stackA == stackB), "Stack == #2");

        stackB.Pop();
        TEST(stackA == stackB, "Stack == #3");

        stackA.Clear();
        TEST(!(stackA == stackB), "Stack == #4");
    }

    {
        constexpr int size{ 20 };
        Stack<int, size> myStack;

        myStack.Push(200);
        myStack.Push(300);
        myStack.Push(400);

        int firstValue{ myStack.Pop() };
        int secondValue{ myStack.Pop() };
        int thirdValue{ myStack.Pop() };
        int fourthValue{ myStack.Pop() };

        TEST(firstValue == 400 && secondValue == 300 && thirdValue == 200 && fourthValue == 0, "Stack Push & Pop");
    }

    {
        constexpr int size{ 20 };
        Stack<int, size> myStack;

        for (int i{}; i < size; ++i) {
            myStack.Push(dist(rd));
        }
        myStack.Clear();
        TEST(myStack.Size() == 0, "Stack clear");
    }

    {
        constexpr int size{ 10 };
        Stack<int, size> stackA, stackB;

        for (int i{}; i < size; ++i) {
            stackA.Push(dist(rd));
        }
        stackB = stackA;
        TEST(stackA == stackB, "Stack copy constructor");
    }

    {
        constexpr int size{ 10 };
        Stack<int, size> stackA, stackB;

        for (int i{}; i < size; ++i) {
            stackA.Push(dist(rd));
        }

        for (int i{}; i < size / 2; ++i) {
            stackB.Push(dist(rd));
        }

        stackA = stackB;
        TEST(stackA == stackB, "Stack copy assignment");
    }

    {
        constexpr int size{ 20 };
        Stack<int, size> stackA;

        for (int i{}; i < size / 2; ++i) {
            stackA.Push(dist(rd));
        }
        std::size_t oldSize{ stackA.Size() };

        Stack<int, size> stackB(std::move(stackA));
        TEST(stackB.Size() == oldSize && stackA.Size() == 0, "Stack move constructor");
    }

    {
        constexpr int size{ 20 };
        Stack<int, size> stackA, stackB;

        for (int i{}; i < size; ++i) {
            stackA.Push(dist(rd));
        }

        for (int i{}; i < size / 2; ++i) {
            stackB.Push(dist(rd));
        }
        std::size_t stackBSize{ stackB.Size() };

        stackA = std::move(stackB);
        TEST(stackA.Size() == stackBSize && stackB.Size() == 0, "Stack move assignment");
    }
}
