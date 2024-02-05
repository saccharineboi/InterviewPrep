#include "../DoubleEndedQueue.hpp"
#include "Common.hpp"

#include <iostream>
#include <random>

int main()
{
    std::random_device rd;
    std::uniform_int_distribution<int> dist;

    {
        constexpr int size{ 5 };
        DoubleEndedQueue<int, size> myQueue;
        for (int i{}; i < size; ++i) {
            myQueue.EnqueueBack(dist(rd));
        }
        TEST(myQueue.Size() == size, "DoubleEndedQueue size #0");

        myQueue.EnqueueBack(99);
        TEST(myQueue.Size() == size, "DoubleEndedQueue size #1");

        myQueue.DequeueFront();
        TEST(myQueue.Size() == size - 1, "DoubleEndedQueue size #2");
        
        myQueue.Clear();
        TEST(myQueue.Size() == 0, "DoubleEndedQueue size #3");
    }

    {
        constexpr int size{ 5 };
        DoubleEndedQueue<int, size> myQueue;
        for (int i{}; i < size; ++i) {
            myQueue.EnqueueFront(dist(rd));
        }
        TEST(myQueue.Size() == size, "DoubleEndedQueue size #0");

        myQueue.EnqueueFront(99);
        TEST(myQueue.Size() == size, "DoubleEndedQueue size #1");

        myQueue.DequeueBack();
        TEST(myQueue.Size() == size - 1, "DoubleEndedQueue size #2");
        
        myQueue.Clear();
        TEST(myQueue.Size() == 0, "DoubleEndedQueue size #3");
    }

    {
        constexpr int size{ 10 };
        DoubleEndedQueue<int, size> queueA, queueB;
        DoubleEndedQueue<int, size> queueC, queueD;

        for (int i{}; i < size; ++i) {
            queueA.EnqueueBack(dist(rd));
        }

        for (int i{}; i < size; ++i) {
            queueB.EnqueueBack(dist(rd));
        }

        TEST(queueA != queueB, "DoubleEndedQueue != #0");

        for (int i{}; i < size; ++i) {
            queueC.EnqueueBack(i * 10);
        }

        for (int i{}; i < size - 1; ++i) {
            queueD.EnqueueBack(i * 10);
        }

        TEST(queueC != queueD, "DoubleEndedQueue != #1");

        queueD.Clear();
        TEST(queueC != queueD, "DoubleEndedQueue != #2");
    }

    {
        constexpr int size{ 10 };
        DoubleEndedQueue<int, size> queueA, queueB;
        DoubleEndedQueue<int, size> queueC, queueD;

        for (int i{}; i < size; ++i) {
            queueA.EnqueueFront(dist(rd));
        }

        for (int i{}; i < size; ++i) {
            queueB.EnqueueFront(dist(rd));
        }

        TEST(queueA != queueB, "DoubleEndedQueue != #0");

        for (int i{}; i < size; ++i) {
            queueC.EnqueueFront(i * 10);
        }

        for (int i{}; i < size - 1; ++i) {
            queueD.EnqueueFront(i * 10);
        }

        TEST(queueC != queueD, "DoubleEndedQueue != #1");

        queueD.Clear();
        TEST(queueC != queueD, "DoubleEndedQueue != #2");
    }

    {
        constexpr int size{ 20 };
        DoubleEndedQueue<int, size> queueA, queueB;
        TEST(queueA == queueB, "DoubleEndedQueue == #0");

        for (int i{}; i < size; ++i) {
            queueA.EnqueueBack(i + 10);
            queueB.EnqueueBack(i + 10);
        }
        TEST(queueA == queueB, "DoubleEndedQueue == #1");

        queueA.DequeueFront();
        TEST(!(queueA == queueB), "DoubleEndedQueue == #2");

        queueB.DequeueFront();
        TEST(queueA == queueB, "DoubleEndedQueue == #3");

        queueA.Clear();
        TEST(!(queueA == queueB), "DoubleEndedQueue == #4");
    }

    {
        constexpr int size{ 20 };
        DoubleEndedQueue<int, size> queueA, queueB;
        TEST(queueA == queueB, "DoubleEndedQueue == #0");

        for (int i{}; i < size; ++i) {
            queueA.EnqueueFront(i + 10);
            queueB.EnqueueFront(i + 10);
        }
        TEST(queueA == queueB, "DoubleEndedQueue == #1");

        queueA.DequeueFront();
        TEST(!(queueA == queueB), "DoubleEndedQueue == #2");

        queueB.DequeueFront();
        TEST(queueA == queueB, "DoubleEndedQueue == #3");

        queueA.Clear();
        TEST(!(queueA == queueB), "DoubleEndedQueue == #4");
    }

    {
        constexpr int size{ 20 };
        DoubleEndedQueue<int, size> myQueue;

        myQueue.EnqueueBack(200);
        myQueue.EnqueueBack(300);
        myQueue.EnqueueBack(400);

        int firstValue{ myQueue.DequeueFront() };
        int secondValue{ myQueue.DequeueFront() };
        int thirdValue{ myQueue.DequeueFront() };
        int fourthValue{ myQueue.DequeueFront() };

        TEST(firstValue == 200 && secondValue == 300 && thirdValue == 400 && fourthValue == 0, "DoubleEndedQueue EnqueueBack & DequeueFront");
    }

    {
        constexpr int size{ 20 };
        DoubleEndedQueue<int, size> myQueue;

        myQueue.EnqueueFront(200);
        myQueue.EnqueueFront(300);
        myQueue.EnqueueFront(400);

        int firstValue{ myQueue.DequeueBack() };
        int secondValue{ myQueue.DequeueBack() };
        int thirdValue{ myQueue.DequeueBack() };
        int fourthValue{ myQueue.DequeueBack() };

        TEST(firstValue == 200 && secondValue == 300 && thirdValue == 400 && fourthValue == 0, "DoubleEndedQueue EnqueueFront & DequeueBack");
    }

    {
        constexpr int size{ 20 };
        DoubleEndedQueue<int, size> myQueue;

        for (int i{}; i < size; ++i) {
            myQueue.EnqueueBack(dist(rd));
        }
        myQueue.Clear();
        TEST(myQueue.Size() == 0, "DoubleEndedQueue clear");
    }

    {
        constexpr int size{ 10 };
        DoubleEndedQueue<int, size> queueA;

        for (int i{}; i < size; ++i) {
            queueA.EnqueueBack(dist(rd));
        }
        DoubleEndedQueue<int, size> queueB{ queueA };
        TEST(queueA == queueB, "DoubleEndedQueue copy constructor");
    }

    {
        constexpr int size{ 10 };
        DoubleEndedQueue<int, size> queueA, queueB;

        for (int i{}; i < size; ++i) {
            queueA.EnqueueBack(dist(rd));
        }

        for (int i{}; i < size / 2; ++i) {
            queueB.EnqueueBack(dist(rd));
        }

        queueA = queueB;
        TEST(queueA == queueB, "DoubleEndedQueue copy assignment");
    }

    {
        constexpr int size{ 20 };
        DoubleEndedQueue<int, size> queueA;

        for (int i{}; i < size / 2; ++i) {
            queueA.EnqueueBack(dist(rd));
        }
        std::size_t oldSize{ queueA.Size() };

        DoubleEndedQueue<int, size> queueB(std::move(queueA));
        TEST(queueB.Size() == oldSize && queueA.Size() == 0, "DoubleEndedQueue move constructor");
    }

    {
        constexpr int size{ 20 };
        DoubleEndedQueue<int, size> queueA, queueB;

        for (int i{}; i < size; ++i) {
            queueA.EnqueueBack(dist(rd));
        }

        for (int i{}; i < size / 2; ++i) {
            queueB.EnqueueBack(dist(rd));
        }
        std::size_t stackBSize{ queueB.Size() };

        queueA = std::move(queueB);
        TEST(queueA.Size() == stackBSize && queueB.Size() == 0, "DoubleEndedQueue move assignment");
    }
}
