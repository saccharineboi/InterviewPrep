#include <iostream>
#include <cstdio>
#include <unordered_set>

////////////////////////////////////////
struct Node
{
    int value;
    Node* next;
};

////////////////////////////////////////
struct SinglyLinkedList
{
    Node* head;

    SinglyLinkedList() : head{} {}

    Node* insert_value(int value)
    {
        Node* newNode{ new Node{ .value{ value }, .next{ head } } };
        head = newNode;
        return newNode;
    }

    void insert_node(Node* node)
    {
        node->next = head;
        head = node;
    }

    void print() const
    {
        Node* node{ head };
        if (!node) {
            std::printf("[empty]\n");
        }
        while (node) {
            std::printf("[%p]: %d -> %p\n", node, node->value, node->next);
            node = node->next;
        }
    }
};

////////////////////////////////////////
Node* find_intersection(const SinglyLinkedList& lstA,
                        const SinglyLinkedList& lstB)
{
    Node* aNode{ lstA.head };
    Node* bNode{ lstB.head };

    std::unordered_set<Node*> bucket;
    while (aNode) {
        bucket.insert(aNode);
        aNode = aNode->next;
    }

    while (bNode) {
        if (bucket.find(bNode) != bucket.end()) {
            return bNode;
        }
        bNode = bNode->next;
    }
    return nullptr;
}

////////////////////////////////////////
Node* find_intersection_wo_bucket(const SinglyLinkedList& lstA,
                                  const SinglyLinkedList& lstB)
{
    Node* aNode{ lstA.head };
    Node* bNode{ lstB.head };
    Node* current{ aNode };

    while (current) {
        if (aNode && bNode && aNode == bNode) {
            return aNode;
        }
        if (current == aNode) {
            current = bNode;        
            aNode = aNode->next;
        }
        else if (current == bNode) {
            current = aNode;
            bNode = bNode->next;
        }
    }
    return nullptr;
}

////////////////////////////////////////
int main()
{
    {
        SinglyLinkedList lstA, lstB;

        Node* firstNode{ lstA.insert_value(10) };
        lstA.insert_value(20);
        lstA.insert_value(30);
        Node* middleNode{ lstA.insert_value(40) };
        Node* lastNode{ lstA.insert_value(50) };

        std::printf("List A:\n");
        lstA.print();

        lstB.insert_node(firstNode);
        lstB.insert_value(20);
        lstB.insert_value(30);
        lstB.insert_node(middleNode);
        lstB.insert_node(lastNode);

        std::printf("List B:\n");
        lstB.print();

        std::printf("Intersecting node is %p\n", find_intersection(lstA, lstB));
        std::printf("[wo bucket] Intersecting node is %p\n\n", find_intersection_wo_bucket(lstA, lstB));
    }

    {
        SinglyLinkedList lstA, lstB;

        lstA.insert_value(10);
        lstA.insert_value(20);
        lstA.insert_value(30);
        lstA.insert_value(40);
        lstA.insert_value(50);

        std::printf("List A:\n");
        lstA.print();

        lstB.insert_value(10);
        lstB.insert_value(20);
        lstB.insert_value(30);
        lstB.insert_value(40);
        lstB.insert_value(50);

        std::printf("List B:\n");
        lstB.print();

        std::printf("Intersecting node is %p\n", find_intersection(lstA, lstB));
        std::printf("[wo bucket] Intersecting node is %p\n\n", find_intersection_wo_bucket(lstA, lstB));
    }

    {
        SinglyLinkedList lstA, lstB;

        lstA.insert_value(10);
        lstA.insert_value(20);
        lstA.insert_value(30);
        Node* middleNode{ lstA.insert_value(40) };
        Node* lastNode{ lstA.insert_value(50) };

        std::printf("List A:\n");
        lstA.print();

        lstB.insert_value(10);
        lstB.insert_value(20);
        lstB.insert_value(30);
        lstB.insert_node(middleNode);
        lstB.insert_node(lastNode);

        std::printf("List B:\n");
        lstB.print();

        std::printf("Intersecting node is %p\n", find_intersection(lstA, lstB));
        std::printf("[wo bucket] Intersecting node is %p\n\n", find_intersection_wo_bucket(lstA, lstB));
    }

    {
        SinglyLinkedList lstA, lstB;

        lstA.insert_value(10);
        lstA.insert_value(20);
        lstA.insert_value(30);
        lstA.insert_value(40);
        Node* lastNode{ lstA.insert_value(50) };

        std::printf("List A:\n");
        lstA.print();

        lstB.insert_value(10);
        lstB.insert_value(20);
        lstB.insert_value(30);
        lstB.insert_value(40);
        lstB.insert_node(lastNode);

        std::printf("List B:\n");
        lstB.print();

        std::printf("Intersecting node is %p\n", find_intersection(lstA, lstB));
        std::printf("[wo bucket] Intersecting node is %p\n\n", find_intersection_wo_bucket(lstA, lstB));
    }

    {
        SinglyLinkedList lstA, lstB;

        lstA.insert_value(10);
        lstA.insert_value(20);
        lstA.insert_value(30);
        Node* middleNode{ lstA.insert_value(40) };
        lstA.insert_value(50);

        std::printf("List A:\n");
        lstA.print();

        lstB.insert_value(10);
        lstB.insert_value(20);
        lstB.insert_value(30);
        lstB.insert_node(middleNode);
        lstB.insert_value(50);

        std::printf("List B:\n");
        lstB.print();

        std::printf("Intersecting node is %p\n", find_intersection(lstA, lstB));
        std::printf("[wo bucket] Intersecting node is %p\n\n", find_intersection_wo_bucket(lstA, lstB));
    }
}
