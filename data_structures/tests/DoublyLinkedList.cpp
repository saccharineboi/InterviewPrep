#include "Common.hpp"
#include "../DoublyLinkedList.hpp"

#include <iostream>
#include <random>
#include <string>

////////////////////////////////////////
int main()
{
    std::random_device rd;
    std::uniform_int_distribution<int> dist(1, 9);

    {
        DoublyLinkedList<int> ll;
        for (int i = 0; i < 10; ++i) {
            ll.push_front(dist(rd));
        }
        TEST(ll.size() == 10, "DoublyLinkedList size");
    }

    {
        DoublyLinkedList<int> ll;
        ll.push_front(10);
        ll.push_front(20);
        DoublyNode<int>* twenty{ ll.pop_front() };
        DoublyNode<int>* ten{ ll.pop_front() };
        TEST(ll.size() == 0 && twenty && twenty->value == 20 && ten && ten->value == 10, "DoublyLinkedList push_front");
    }

    {
        DoublyLinkedList<int> ll;
        ll.push_back(10);
        ll.push_back(20);
        DoublyNode<int>* twenty{ ll.pop_back() };
        DoublyNode<int>* ten{ ll.pop_back() };
        TEST(ll.size() == 0 && twenty && twenty->value == 20 && ten && ten->value == 10, "DoublyLinkedList push_back");
    }

    {
        DoublyLinkedList<std::string> a;
        DoublyLinkedList<std::string> b;

        a.push_back("Audi");
        a.push_back("Toyota");
        a.push_back("Mercedes");

        b.push_front("Mercedes");
        b.push_front("Toyota");
        b.push_front("Audi");

        TEST(a == b, "DoublyLinkedList ==");
    }

    {
        DoublyLinkedList<std::string> a;
        DoublyLinkedList<std::string> b;

        a.push_back("Audi");
        a.push_back("Toyota");
        a.push_back("Mercedes");

        b.push_front("Mercedes");
        b.push_front("Toyota");
        b.push_front("Lada");

        TEST(a != b, "DoublyLinkedList !=");
    }

    {
        DoublyLinkedList<std::string> a;
        a.push_back("New York");
        a.push_back("Los Angeles");
        a.push_back("San Francisco");

        DoublyLinkedList<std::string> b{ a };
        TEST(a == b, "DoublyLinkedList copy constructor");
    }

    {
        DoublyLinkedList<std::string> a;
        a.push_back("New York");
        a.push_back("Los Angeles");
        a.push_back("San Francisco");

        DoublyLinkedList<std::string> b;
        b.push_back("London");
        b.push_back("Paris");
        b.push_back("Madrid");

        b = a;
        TEST(a == b, "DoublyLinkedList copy assignment");
    }

    {
        DoublyLinkedList<std::string> a;
        a.push_back("New York");
        a.push_back("Los Angeles");
        a.push_back("San Francisco");

        DoublyLinkedList<std::string> b{ std::move(a) };
        TEST(b.size() == 3 && a.size() == 0 && a != b, "DoublyLinkedList move constructor");
    }

    {
        DoublyLinkedList<std::string> a;
        a.push_back("New York");
        a.push_back("Los Angeles");
        a.push_back("San Francisco");

        DoublyLinkedList<std::string> b;
        b.push_back("London");
        b.push_back("Paris");
        b.push_back("Madrid");

        b = std::move(a);
        TEST(b.size() == 3 && a.size() == 0 && a != b, "DoublyLinkedList move assignment");
    }

    {
        DoublyLinkedList<int> a;
        a.push_back(1);
        a.push_back(2);
        a.push_back(3);
        a.reverse();
        bool x{ a.pop_back()->value == 1 };
        bool y{ a.pop_back()->value == 2 };
        bool z{ a.pop_back()->value == 3 };
        TEST(a.size() == 0 && x && y && z, "DoublyLinkedList reverse");
    }

    {
        DoublyLinkedList<std::string> a;
        a.push_back("New York");
        a.push_back("Los Angeles");
        a.push_back("San Francisco");
        TEST(a.find("New York") && a.find("Los Angeles") && a.find("San Francisco") && !a.find("London"), "DoublyLinkedList find");
    }

    {
        DoublyLinkedList<int> nonCircular;
        DoublyLinkedList<int> circular;

        nonCircular.push_front(10);
        nonCircular.push_front(20);
        nonCircular.push_front(30);
        nonCircular.push_front(40);

        circular.push_front(10);
        circular.push_front(20);
        circular.push_front(30);
        circular.push_front(40);

        DoublyNode<int>* end{ circular.find(10) };
        DoublyNode<int>* begin{ circular.find(40) };
        begin->prev = end;
        end->next = begin;

        TEST(!nonCircular.is_circular() && circular.is_circular(), "DoublyLinkedList is_circular");
        end->next = nullptr; // fix circular
        begin->prev = nullptr; // fix circular
    }
}
