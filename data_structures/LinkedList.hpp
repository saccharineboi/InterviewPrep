#pragma once

#include <cstdint>
#include <cstdio>
#include <memory>
#include <iostream>

////////////////////////////////////////
template <typename T>
struct Node
{
    T value;
    Node* next;
};

////////////////////////////////////////
template <typename T>
struct LinkedList
{
private:
    Node<T>* mHead;
    std::size_t mSize;

public:
    ////////////////////////////////////////
    LinkedList() : mHead{}, mSize{} {}

    ////////////////////////////////////////
    std::size_t size() const { return mSize; }

    ////////////////////////////////////////
    ~LinkedList()
    {
        Node<T>* node{ mHead };
        while (node) {
            Node<T>* next{ node->next };
            delete node;
            node = next;
        }
        mHead = nullptr;
        mSize = 0;
    }

    ////////////////////////////////////////
    LinkedList(const LinkedList& other)
        : mHead{}, mSize{other.mSize}
    {
        if (mSize > 0) {
            mHead = new Node<T>{ .value{ other.mHead->value },
                                 .next{ other.mHead->next } };
            mSize = 1;

            Node<T>* node{ mHead };
            while (node->next) {
                Node<T>* nextNode{ node->next };
                Node<T>* newNode{ new Node<T>{ .value{ nextNode->value },
                                               .next{ nextNode->next }  } };
                node->next = newNode;
                node = nextNode;
                ++mSize;
            }
        }
    }

    ////////////////////////////////////////
    LinkedList& operator=(const LinkedList& other)
    {
        if (this != &other) {
            Node<T>* node{ mHead };
            while (node) {
                Node<T>* nextNode{ node->next };
                delete node;
                node = nextNode;
            }
            mHead = nullptr;

            mSize = other.mSize;
            if (mSize > 0) {
                mHead = new Node<T>{ .value{ other.mHead->value },
                                     .next{ other.mHead->next } };
                mSize = 1;

                Node<T>* node{ mHead };
                while (node->next) {
                    Node<T>* nextNode{ node->next };
                    Node<T>* newNode{ new Node<T>{ .value{ nextNode->value },
                                                   .next{ nextNode->next } } };
                    node->next = newNode;
                    node = nextNode;
                    ++mSize;
                }
            }
        }
        return *this;
    }

    ////////////////////////////////////////
    LinkedList(LinkedList&& other)
        : mHead{other.mHead}, mSize{other.mSize}
    {
        other.mHead = nullptr;
        other.mSize = 0;
    }

    ////////////////////////////////////////
    LinkedList& operator=(LinkedList&& other)
    {
        if (this != &other) {
            Node<T>* node{ mHead };
            while (node) {
                Node<T>* nextNode{ node->next };
                delete node;
                node = nextNode;
            }
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
            mHead = new Node<T>{ .value{ value },
                                 .next{ nullptr } };
        }
        else {
            Node<T>* newNode{ new Node<T> };
            newNode->value = value;
            newNode->next = mHead;
            mHead = newNode;
        }
        ++mSize;
    }

    ////////////////////////////////////////
    void push_front(T&& value)
    {
        if (!mHead) {
            mHead = new Node<T>{ .value{ std::move(value) },
                                 .next{ nullptr } };
        }
        else {
            Node<T>* newNode{ new Node<T> };
            newNode->value = std::move(value);
            newNode->next = mHead;
            mHead = newNode;
        }
        ++mSize;
    }

    ////////////////////////////////////////
    void push_back(const T& value)
    {
        if (!mHead) {
            mHead = new Node<T>{ .value{ value },
                                 .next{ nullptr } };
        }
        else {
            Node<T>* node{ mHead };
            while (node->next) {
                node = node->next;
            }
            node->next = new Node<T>{ .value{ value },
                                      .next{ nullptr } };
        }
        ++mSize;
    }

    ////////////////////////////////////////
    void push_back(T&& value)
    {
        if (!mHead) {
            mHead = new Node<T>{ .value{ std::move(value) },
                                 .next{ nullptr } };
        }
        else {
            Node<T>* node{ mHead };
            while (node->next) {
                node = node->next;
            }
            node->next = new Node<T>{ .value{ std::move(value) },
                                      .next{ nullptr } };
        }
        ++mSize;
    }

    ////////////////////////////////////////
    Node<T>* pop_front()
    {
        if (!mHead) {
            return nullptr;
        }
        Node<T>* node{ mHead };
        mHead = mHead->next;
        --mSize;
        if (!mSize) {
            mHead = nullptr;
        }
        return node;
    }

    ////////////////////////////////////////
    Node<T>* pop_back()
    {
        if (!mHead) {
            return nullptr;
        }
        Node<T>* node{ mHead };
        Node<T>* prevNode{ mHead };
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
            std::cout << "LinkedList is empty\n";
        }
        for (Node<T>* node{ mHead }; node; node = node->next) {
            std::cout << (node->value) << " -> " << node->next << "\n";
        }
    }

    ////////////////////////////////////////
    bool operator==(const LinkedList& other)
    {
        if (mSize != other.mSize) {
            return false;
        }
        Node<T>* ourNode{ mHead };
        Node<T>* otherNode{ other.mHead };
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
    bool operator!=(const LinkedList& other)
    {
        return !(*this == other);
    }
};
