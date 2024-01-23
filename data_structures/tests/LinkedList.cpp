#include "Common.hpp"
#include "../LinkedList.hpp"

#include <iostream>
#include <random>
#include <string>

////////////////////////////////////////
int main()
{
    std::random_device rd;
    std::uniform_int_distribution<int> dist(1, 9);

    {
        LinkedList<int> ll;
        for (int i = 0; i < 10; ++i) {
            ll.push_front(dist(rd));
        }
        TEST(ll.size() == 10, "LinkedList size");
    }

    {
        LinkedList<int> ll;
        ll.push_front(10);
        ll.push_front(20);
        Node<int>* twenty{ ll.pop_front() };
        Node<int>* ten{ ll.pop_front() };
        TEST(ll.size() == 0 && twenty && twenty->value == 20 && ten && ten->value == 10, "LinkedList push_front");
    }

    {
        LinkedList<int> ll;
        ll.push_back(10);
        ll.push_back(20);
        Node<int>* twenty{ ll.pop_back() };
        Node<int>* ten{ ll.pop_back() };
        TEST(ll.size() == 0 && twenty && twenty->value == 20 && ten && ten->value == 10, "LinkedList push_back");
    }

    {
        LinkedList<std::string> a;
        LinkedList<std::string> b;

        a.push_back("Audi");
        a.push_back("Toyota");
        a.push_back("Mercedes");

        b.push_front("Mercedes");
        b.push_front("Toyota");
        b.push_front("Audi");

        TEST(a == b, "LinkedList ==");
    }

    {
        LinkedList<std::string> a;
        LinkedList<std::string> b;

        a.push_back("Audi");
        a.push_back("Toyota");
        a.push_back("Mercedes");

        b.push_front("Mercedes");
        b.push_front("Toyota");
        b.push_front("Lada");

        TEST(a != b, "LinkedList !=");
    }

    {
        LinkedList<std::string> a;
        a.push_back("New York");
        a.push_back("Los Angeles");
        a.push_back("San Francisco");

        LinkedList<std::string> b{ a };
        TEST(a == b, "LinkedList copy constructor");
    }

    {
        LinkedList<std::string> a;
        a.push_back("New York");
        a.push_back("Los Angeles");
        a.push_back("San Francisco");

        LinkedList<std::string> b;
        b.push_back("London");
        b.push_back("Paris");
        b.push_back("Madrid");

        b = a;
        TEST(a == b, "LinkedList copy assignment");
    }

    {
        LinkedList<std::string> a;
        a.push_back("New York");
        a.push_back("Los Angeles");
        a.push_back("San Francisco");

        LinkedList<std::string> b{ std::move(a) };
        TEST(b.size() == 3 && a.size() == 0 && a != b, "LinkedList move constructor");
    }

    {
        LinkedList<std::string> a;
        a.push_back("New York");
        a.push_back("Los Angeles");
        a.push_back("San Francisco");

        LinkedList<std::string> b;
        b.push_back("London");
        b.push_back("Paris");
        b.push_back("Madrid");

        b = std::move(a);
        TEST(b.size() == 3 && a.size() == 0 && a != b, "LinkedList move assignment");
    }
}
