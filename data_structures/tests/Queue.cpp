#include "../Queue.hpp"
#include "Common.hpp"

#include <iostream>
#include <random>

int main()
{
    std::random_device rd;
    std::uniform_int_distribution<int> dist;

    {
        constexpr int size{ 5 };
        Queue<int, size> myQueue;
        for (int i{}; i < size; ++i) {
            myQueue.Enqueue(dist(rd));
        }
        TEST(myQueue.Size() == size, "Queue size #0");

        myQueue.Enqueue(99);
        TEST(myQueue.Size() == size, "Queue size #1");

        myQueue.Dequeue();
        TEST(myQueue.Size() == size - 1, "Queue size #2");
        
        myQueue.Clear();
        TEST(myQueue.Size() == 0, "Queue size #3");
    }

    {
        constexpr int size{ 10 };
        Queue<int, size> queueA, queueB;
        Queue<int, size> queueC, queueD;

        for (int i{}; i < size; ++i) {
            queueA.Enqueue(dist(rd));
        }

        for (int i{}; i < size; ++i) {
            queueB.Enqueue(dist(rd));
        }

        TEST(queueA != queueB, "Queue != #0");

        for (int i{}; i < size; ++i) {
            queueC.Enqueue(i * 10);
        }

        for (int i{}; i < size - 1; ++i) {
            queueD.Enqueue(i * 10);
        }

        TEST(queueC != queueD, "Queue != #1");

        queueD.Clear();
        TEST(queueC != queueD, "Queue != #2");
    }

    {
        constexpr int size{ 20 };
        Queue<int, size> queueA, queueB;
        TEST(queueA == queueB, "Queue == #0");

        for (int i{}; i < size; ++i) {
            queueA.Enqueue(i + 10);
            queueB.Enqueue(i + 10);
        }
        TEST(queueA == queueB, "Queue == #1");

        queueA.Dequeue();
        TEST(!(queueA == queueB), "Queue == #2");

        queueB.Dequeue();
        TEST(queueA == queueB, "Queue == #3");

        queueA.Clear();
        TEST(!(queueA == queueB), "Queue == #4");
    }

    {
        constexpr int size{ 20 };
        Queue<int, size> myQueue;

        myQueue.Enqueue(200);
        myQueue.Enqueue(300);
        myQueue.Enqueue(400);

        int firstValue{ myQueue.Dequeue() };
        int secondValue{ myQueue.Dequeue() };
        int thirdValue{ myQueue.Dequeue() };
        int fourthValue{ myQueue.Dequeue() };

        TEST(firstValue == 200 && secondValue == 300 && thirdValue == 400 && fourthValue == 0, "Queue Enqueue & Dequeue");
    }

    {
        constexpr int size{ 20 };
        Queue<int, size> myQueue;

        for (int i{}; i < size; ++i) {
            myQueue.Enqueue(dist(rd));
        }
        myQueue.Clear();
        TEST(myQueue.Size() == 0, "Queue clear");
    }

    {
        constexpr int size{ 10 };
        Queue<int, size> queueA;

        for (int i{}; i < size; ++i) {
            queueA.Enqueue(dist(rd));
        }
        Queue<int, size> queueB{ queueA };
        TEST(queueA == queueB, "Queue copy constructor");
    }

    {
        constexpr int size{ 10 };
        Queue<int, size> queueA, queueB;

        for (int i{}; i < size; ++i) {
            queueA.Enqueue(dist(rd));
        }

        for (int i{}; i < size / 2; ++i) {
            queueB.Enqueue(dist(rd));
        }

        queueA = queueB;
        TEST(queueA == queueB, "Queue copy assignment");
    }

    {
        constexpr int size{ 20 };
        Queue<int, size> queueA;

        for (int i{}; i < size / 2; ++i) {
            queueA.Enqueue(dist(rd));
        }
        std::size_t oldSize{ queueA.Size() };

        Queue<int, size> queueB(std::move(queueA));
        TEST(queueB.Size() == oldSize && queueA.Size() == 0, "Queue move constructor");
    }

    {
        constexpr int size{ 20 };
        Queue<int, size> queueA, queueB;

        for (int i{}; i < size; ++i) {
            queueA.Enqueue(dist(rd));
        }

        for (int i{}; i < size / 2; ++i) {
            queueB.Enqueue(dist(rd));
        }
        std::size_t stackBSize{ queueB.Size() };

        queueA = std::move(queueB);
        TEST(queueA.Size() == stackBSize && queueB.Size() == 0, "Queue move assignment");
    }
}
