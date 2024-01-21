#include "Common.hpp"
#include "../LinkedList.hpp"

#include <iostream>
#include <random>

////////////////////////////////////////
int main()
{
    std::random_device rd;
    std::uniform_int_distribution<int> dist(1, 9);

    {
        LinkedList ll;
        for (int i = 0; i < 10; ++i) {
            ll.push_front(dist(rd));
        }
        TEST(ll.size() == 10, "LinkedList size");
    }

    {
        LinkedList ll;
        ll.push_front(10);
        ll.push_front(20);
        Node* twenty{ ll.pop_front() };
        Node* ten{ ll.pop_front() };
        TEST(ll.size() == 0 && twenty && twenty->value == 20 && ten && ten->value == 10, "LinkedList push_front");
    }

    {
        LinkedList ll;
        ll.push_back(10);
        ll.push_back(20);
        Node* twenty{ ll.pop_back() };
        Node* ten{ ll.pop_back() };
        TEST(ll.size() == 0 && twenty && twenty->value == 20 && ten && ten->value == 10, "LinkedList push_back");
    }

    {
        LinkedList ll;
        for (int i = 0; i < 5; ++i) {
            ll.push_back(dist(rd));
        }
        ll.print();
        TEST(ll.size() == 5, "LinkedList print");
    }
}
