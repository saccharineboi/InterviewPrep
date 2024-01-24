#include <iostream>
#include <random>
#include <cstdint>
#include <cstdio>

////////////////////////////////////////
#define SIZE 5

////////////////////////////////////////
struct Node
{
    int value;
    Node* next;
    Node* prev;
};

////////////////////////////////////////
struct DoublyLinkedList
{
    Node* head;
    std::size_t size;

    DoublyLinkedList(bool makeCircular) : head{}, size{SIZE}
    {
        std::random_device rd;
        std::uniform_int_distribution<int> dist(1, 9);

        head = new Node{ .value{ dist(rd) },
                         .next{},
                         .prev{} };
        Node* prevNode{ head };
        for (std::size_t cnt{1}; cnt < size; ++cnt) {
            Node* newNode{ new Node{ .value{ dist(rd) },
                                     .next{},
                                     .prev{ prevNode } } };
            prevNode->next = newNode;
            prevNode = newNode;
        }
        if (makeCircular) {
            prevNode->next = head;
        }
    }

    ~DoublyLinkedList()
    {
        Node* node{ head };
        for (std::size_t i{}; node && i < size; ++i) {
            Node* next{ node->next };
            delete node;
            node = next;
        }
    }

    void print() const
    {
        Node* node{ head };
        if (!node) {
            std::cout << "[empty]\n";
        }
        for (std::size_t i{}; i < size && node; ++i) {
            std::printf("[%p]: %d -> [%p]\n", node, node->value, node->next);
            node = node->next;
        }
    }
};

////////////////////////////////////////
Node* isCircular(const DoublyLinkedList& lst)
{
    Node* hare{ lst.head };
    if (!hare) {
        return nullptr;
    }
    else if (hare->next == hare) {
        return nullptr;
    }

    Node* tortoise{ lst.head };
    while (hare && tortoise) {
        tortoise = tortoise->next;
        if (!hare->next) {
            return nullptr;
        }
        hare = hare->next->next;
        if (tortoise == hare) {
            return tortoise;
        }
    }
    return nullptr;
}

////////////////////////////////////////
int main()
{
    DoublyLinkedList listA(false);
    std::printf("LIST A:\n");
    listA.print();
    std::putchar('\n');

    DoublyLinkedList listB(true);
    std::printf("LIST B:\n");
    listB.print();
    std::putchar('\n');

    std::printf("LIST A CIRCLES AT %p\n", isCircular(listA));
    std::printf("LIST B CIRCLES AT %p\n", isCircular(listB));
}
