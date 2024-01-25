#pragma once

#include <cstdint>
#include <cstdio>
#include <memory>
#include <iostream>

////////////////////////////////////////
template <typename T>
struct DoublyNode
{
    T value;
    DoublyNode* next;
    DoublyNode* prev;
};

////////////////////////////////////////
template <typename T>
struct DoublyLinkedList
{
private:
    DoublyNode<T>* mHead;
    std::size_t mSize;

public:
    ////////////////////////////////////////
    DoublyLinkedList() : mHead{}, mSize{} {}

    ////////////////////////////////////////
    std::size_t size() const { return mSize; }

    ////////////////////////////////////////
    void clear()
    {
        DoublyNode<T>* node{ mHead };
        while (node) {
            DoublyNode<T>* next{ node->next };
            delete node;
            node = next;
        }
        mHead = nullptr;
        mSize = 0;
    }

    ////////////////////////////////////////
    ~DoublyLinkedList()
    {
        clear();
    }

    ////////////////////////////////////////
    DoublyLinkedList(const DoublyLinkedList& other)
        : mHead{}, mSize{}
    {
        if (other.mSize > 0) {
            mHead = new DoublyNode<T>{ .value{ other.mHead->value },
                                       .next{ other.mHead->next },
                                       .prev{ other.mHead->prev } };
            mSize = 1;

            DoublyNode<T>* node{ mHead };
            DoublyNode<T>* prev{ mHead->prev };

            while (mSize < other.mSize && node->next) {
                DoublyNode<T>* nextNode{ node->next };
                DoublyNode<T>* newNode{ new DoublyNode<T>{ .value{ nextNode->value },
                                                           .next{ nextNode->next },
                                                           .prev{ prev } } };
                node->next = newNode;
                node->prev = prev;
                prev = node;
                node = nextNode;
                ++mSize;
            }
        }
    }

    ////////////////////////////////////////
    DoublyLinkedList& operator=(const DoublyLinkedList& other)
    {
        if (this != &other) {
            clear();

            if (other.mSize > 0) {
                mHead = new DoublyNode<T>{ .value{ other.mHead->value },
                                           .next{ other.mHead->next },
                                           .prev{ other.mHead->prev } };
                mSize = 1;

                DoublyNode<T>* node{ mHead };
                DoublyNode<T>* prev{ mHead->prev };
                while (mSize < other.mSize && node->next) {
                    DoublyNode<T>* nextNode{ node->next };
                    DoublyNode<T>* newNode{ new DoublyNode<T>{ .value{ nextNode->value },
                                                               .next{ nextNode->next },
                                                               .prev{ nextNode->prev } } };
                    node->next = newNode;
                    node->prev = prev;
                    prev = node;
                    node = nextNode;
                    ++mSize;
                }
            }
        }
        return *this;
    }

    ////////////////////////////////////////
    DoublyLinkedList(DoublyLinkedList&& other)
        : mHead{other.mHead}, mSize{other.mSize}
    {
        other.mHead = nullptr;
        other.mSize = 0;
    }

    ////////////////////////////////////////
    DoublyLinkedList& operator=(DoublyLinkedList&& other)
    {
        if (this != &other) {
            clear();
            mHead = other.mHead;
            mSize = other.mSize;
            other.mHead = nullptr;
            other.mSize = 0;
        }
        return *this;
    }

    ////////////////////////////////////////
    void push_front(const T& value)
    {
        if (!mHead) {
            mHead = new DoublyNode<T>{ .value{ value },
                                       .next{ nullptr },
                                       .prev{ nullptr } };
        }
        else {
            DoublyNode<T>* newNode{ new DoublyNode<T>{ .value{value},
                                                       .next{ mHead },
                                                       .prev{ nullptr } } };
            mHead = newNode;
        }
        ++mSize;
    }

    ////////////////////////////////////////
    void push_front(T&& value)
    {
        if (!mHead) {
            mHead = new DoublyNode<T>{ .value{ std::move(value) },
                                       .next{ nullptr },
                                       .prev{ nullptr } };
        }
        else {
            DoublyNode<T>* newNode{ new DoublyNode<T>{ .value{ std::move(value) },
                                                       .next{ mHead },
                                                       .prev{ nullptr } } };
            mHead = newNode;
        }
        ++mSize;
    }

    ////////////////////////////////////////
    void push_back(const T& value)
    {
        if (!mHead) {
            mHead = new DoublyNode<T>{ .value{ value },
                                       .next{ nullptr },
                                       .prev{ nullptr } };
        }
        else {
            DoublyNode<T>* node{ mHead };
            DoublyNode<T>* prev{};
            while (node->next) {
                prev = node;
                node = node->next;
            }
            node->next = new DoublyNode<T>{ .value{ value },
                                            .next{ nullptr },
                                            .prev{ prev } };
        }
        ++mSize;
    }

    ////////////////////////////////////////
    void push_back(T&& value)
    {
        if (!mHead) {
            mHead = new DoublyNode<T>{ .value{ std::move(value) },
                                       .next{ nullptr },
                                       .prev{ nullptr } };
        }
        else {
            DoublyNode<T>* node{ mHead };
            DoublyNode<T>* prev{};
            while (node->next) {
                prev = node;
                node = node->next;
            }
            node->next = new DoublyNode<T>{ .value{ std::move(value) },
                                            .next{ nullptr },
                                            .prev{ prev } };
        }
        ++mSize;
    }

    ////////////////////////////////////////
    DoublyNode<T>* pop_front()
    {
        if (!mHead) {
            return nullptr;
        }
        DoublyNode<T>* node{ mHead };
        mHead->prev = nullptr;
        mHead = mHead->next;
        --mSize;
        if (!mSize) {
            mHead = nullptr;
        }
        return node;
    }

    ////////////////////////////////////////
    DoublyNode<T>* pop_back()
    {
        if (!mHead) {
            return nullptr;
        }
        DoublyNode<T>* node{ mHead };
        DoublyNode<T>* prevNode{ mHead };
        while (node->next) {
            prevNode = node;
            node = node->next;
        }
        --mSize;
        if (prevNode == node) {
            mHead = nullptr;
            return prevNode;
        }
        prevNode->next = nullptr;
        return node;
    }

    ////////////////////////////////////////
    void print() const
    {
        if (!mSize) {
            std::cout << "DoublyLinkedList is empty\n";
        }
        for (DoublyNode<T>* node{ mHead }; node; node = node->next) {
            std::cout << node->prev << " <- " << (node->value) << " -> " << node->next << "\n";
        }
    }

    ////////////////////////////////////////
    bool operator==(const DoublyLinkedList& other)
    {
        if (mSize != other.mSize) {
            return false;
        }
        DoublyNode<T>* ourNode{ mHead };
        DoublyNode<T>* otherNode{ other.mHead };
        while (ourNode) {
            if (ourNode->value != otherNode->value) {
                return false;
            }
            ourNode = ourNode->next;
            otherNode = otherNode->next;
        }
        return true;
    }

    ////////////////////////////////////////
    bool operator!=(const DoublyLinkedList& other)
    {
        return !(*this == other);
    }

    ////////////////////////////////////////
    void reverse()
    {
        DoublyNode<T>* prev{};
        DoublyNode<T>* node{ mHead };
        while (node) {
            DoublyNode<T>* next{ node->next };
            node->next = prev;
            node->prev = next;
            prev = node;
            node = next;
        }
        mHead = prev;
    }

    ////////////////////////////////////////
    bool is_circular() const
    {
        DoublyNode<T>* tortoise{ mHead };
        DoublyNode<T>* hare{ mHead };

        while (tortoise && hare) {
            tortoise = tortoise->next;
            if (!(hare->next)) {
                return false;
            }
            hare = hare->next->next;
            if (tortoise == hare) {
                return true;
            }
        }
        return false;
    }

    ////////////////////////////////////////
    DoublyNode<T>* find(const T& value)
    {
        for (DoublyNode<T>* node{ mHead }; node; node = node->next) {
            if (node->value == value) {
                return node;
            }
        }
        return nullptr;
    }
};
