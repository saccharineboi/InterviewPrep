#pragma once

#include <cstdint>

////////////////////////////////////////
struct Node
{
    int value;
    Node* next;
};

////////////////////////////////////////
struct LinkedList
{
private:
    Node* mHead;
    std::size_t mSize;

public:
    ////////////////////////////////////////
    LinkedList() : mHead{}, mSize{} {}

    ////////////////////////////////////////
    std::size_t size() const { return mSize; }

    ////////////////////////////////////////
    ~LinkedList()
    {
        Node* node{ mHead };
        while (node) {
            Node* next{ node->next };
            delete node;
            node = next;
        }
        mHead = nullptr;
        mSize = 0;
    }

    ////////////////////////////////////////
    LinkedList(const LinkedList& other);
    LinkedList& operator=(const LinkedList& other);

    LinkedList(LinkedList&& other);
    LinkedList& operator=(LinkedList&& other);

    ////////////////////////////////////////
    void push_front(int value)
    {
        if (!mHead) {
            mHead = new Node{ .value = value,
                              .next = nullptr };
        }
        else {
            Node* newNode{ new Node };
            newNode->value = value;
            newNode->next = mHead;
            mHead = newNode;
        }
        ++mSize;
    }

    ////////////////////////////////////////
    void push_back(int value)
    {
        if (!mHead) {
            mHead = new Node{ .value = value,
                              .next = nullptr };
        }
        else {
            Node* node{ mHead };
            while (node->next) {
                node = node->next;
            }
            node->next = new Node{ .value = value,
                                   .next = nullptr };
        }
        ++mSize;
    }

    ////////////////////////////////////////
    Node* pop_front()
    {
        if (!mHead) {
            return nullptr;
        }
        Node* node{ mHead };
        mHead = mHead->next;
        --mSize;
        return node;
    }

    ////////////////////////////////////////
    Node* pop_back()
    {
        if (!mHead) {
            return nullptr;
        }
        Node* node{ mHead };
        while (node) {
            node = node->next;
        }
    }
};
